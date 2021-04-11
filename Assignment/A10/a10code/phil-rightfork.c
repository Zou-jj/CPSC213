#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#define MAX_THINKING_TIME 25000

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__)
#else
#define VERBOSE_PRINT(S, ...) ((void) 0) // do nothing
#endif

typedef struct fork {
  uthread_mutex_t lock;
  uthread_cond_t forfree;
  long free;
} fork_t;

int num_phils, num_meals;    
fork_t *forks;

void deep_thoughts() {
  // usleep(random() % MAX_THINKING_TIME);
}

void initfork(int i) {
  forks[i].lock    = uthread_mutex_create();
  forks[i].forfree = uthread_cond_create(forks[i].lock);
  forks[i].free    = 1;
}

long getfork(long i) {
  /* TO BE IMPLEMENTED BY THE STUDENTS. */
  if (forks[i].free){
    forks[i].free = 0;
    return 1;
  } else {
    return 0;
  }
}

void putfork(long i) {
  /* TO BE IMPLEMENTED BY THE STUDENTS. */
  forks[i].free = 1;
  uthread_cond_signal(forks[i].forfree);
}

int leftfork(long i) {
  return i;
}

int rightfork(long i) {
  return (i + 1) % num_phils;
}

void *phil_thread(void *arg) {
  uintptr_t id = (uintptr_t) arg;
  int meals = 0;
  
  while (meals < num_meals) {
    /* TO BE IMPLEMENTED BY THE STUDENTS. */
    int rightForkNum = (id + 1) % num_phils;
    int leftForkNum = id;

    uthread_mutex_lock(forks[rightForkNum].lock);
    while(!getfork(rightForkNum)){
      uthread_cond_wait(forks[rightForkNum].forfree);
    }
    VERBOSE_PRINT ("phil %ld picks up right fork %d\n", id, rightForkNum);
    deep_thoughts();
    uthread_mutex_unlock(forks[rightForkNum].lock);

    uthread_mutex_lock(forks[leftForkNum].lock);
    while(!getfork(leftForkNum)){
      uthread_cond_wait(forks[leftForkNum].forfree);
    }
    VERBOSE_PRINT ("phil %ld picks up left fork %d\n", id, leftForkNum);
    deep_thoughts();
    uthread_mutex_unlock(forks[leftForkNum].lock);

    deep_thoughts();
    VERBOSE_PRINT ("phil %ld eats\n", id);

    uthread_mutex_lock(forks[rightForkNum].lock);
    putfork(rightForkNum);
    VERBOSE_PRINT ("phil %ld puts down right fork %d\n", id, rightForkNum);
    uthread_mutex_unlock(forks[rightForkNum].lock);

    uthread_mutex_lock(forks[leftForkNum].lock);
    putfork(leftForkNum);
    VERBOSE_PRINT ("phil %ld puts down left fork %d\n", id, leftForkNum);
    uthread_mutex_unlock(forks[leftForkNum].lock);

    deep_thoughts();

    meals++;
  }

  VERBOSE_PRINT ("phil %ld exits\n", id);
  
  return 0;
}

int main(int argc, char **argv) {

  uthread_t *p;
  uintptr_t i;
  
  if (argc != 3) {
    fprintf(stderr, "Usage: %s num_philosophers num_meals\n", argv[0]);
    return 1;
  }

  num_phils = strtol(argv[1], 0, 0);
  num_meals = strtol(argv[2], 0, 0);
  
  forks = malloc(num_phils * sizeof(fork_t));
  p = malloc(num_phils * sizeof(uthread_t));

  uthread_init(num_phils);
  
  srandom(time(0));
  for (i = 0; i < num_phils; ++i) {
    initfork(i);
  }

  /* TODO: Create num_phils threads, all calling phil_thread with a
   * different ID, and join all threads.
   */

  for (i = 0; i < num_phils; ++i) {
    p[i] = uthread_create(phil_thread, i);
  }
  for (i = 0; i < num_phils; ++i) {
    uthread_join (p[i], NULL);
  }
  
  return 0;
}
