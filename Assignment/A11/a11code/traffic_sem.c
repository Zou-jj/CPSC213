#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>

#include "uthread.h"
#include "uthread_sem.h"

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__)
#else
#define VERBOSE_PRINT(S, ...) ((void) 0) // do nothing
#endif

#define MAX_OCCUPANCY  3
#define NUM_ITERATIONS 10
#define NUM_CARS       20

// These times determine the number of times yield is called when in
// the street, or when waiting before crossing again.
#define CROSSING_TIME             NUM_CARS
#define WAIT_TIME_BETWEEN_CROSSES NUM_CARS

/**
 * You might find these declarations useful.
 */
enum Direction {EAST = 0, WEST = 1};
const static enum Direction oppositeEnd [] = {WEST, EAST};

struct Street {
  // TODO
  uthread_sem_t lock;
  uthread_sem_t occ_lock;
  uthread_sem_t switch_lock;
  int num_cars;
  int num_east_waiting;
  int num_west_waiting;
  enum Direction dir;
} Street;

struct Street* street;

void initializeStreet(void) {
  // TODO
  street = malloc(sizeof (struct Street));
  street->num_cars = 0;
  street->num_east_waiting = 0; // number of cars blocked during switch lock
  street->num_west_waiting = 0; // number of cars blocked during switch lock
  street->dir = EAST;
  street->lock = uthread_sem_create(1);
  street->occ_lock = uthread_sem_create(3); // occupancy lock
  street->switch_lock = uthread_sem_create(0);
}

#define WAITING_HISTOGRAM_SIZE (NUM_ITERATIONS * NUM_CARS)
int             entryTicker;                                          // incremented with each entry
int             waitingHistogram [WAITING_HISTOGRAM_SIZE];
int             waitingHistogramOverflow;
uthread_sem_t   waitingHistogramLock;
int             occupancyHistogram [2] [MAX_OCCUPANCY + 1];

void switch_direction() {
	if (street->dir == WEST) {
		  street->dir = EAST;
	  } else {
		  street->dir = WEST;
	  }
}

void enterStreet (enum Direction g) {
  // TODO

  uthread_sem_wait(street->lock);
  if (g == EAST){
    VERBOSE_PRINT("east in\n");
  } else {
    VERBOSE_PRINT("west in\n");
  }
  while (g != street->dir){
    if (g == EAST){
      street->num_east_waiting++;
      VERBOSE_PRINT("east %d cars waiting ", street->num_east_waiting);
    } else {
      street->num_west_waiting++;
      VERBOSE_PRINT("west %d cars waiting ", street->num_west_waiting);
    }
    uthread_sem_signal(street->lock);
	  uthread_sem_wait(street->switch_lock);
	  uthread_sem_wait(street->lock);
    if (g == EAST){
      street->num_east_waiting--;
    } else {
      street->num_west_waiting--;
    }
  }
  uthread_sem_signal(street->lock);
  uthread_sem_wait(street->occ_lock);
  uthread_sem_wait(street->lock);
  if (g == EAST){
    VERBOSE_PRINT("east enter ");
  } else {
    VERBOSE_PRINT("west enter ");
  }
  entryTicker++;
  street->num_cars++;
  VERBOSE_PRINT("now %d cars in street\n", street->num_cars);
  uthread_sem_signal(street->lock);
}

void leaveStreet(void) {
  // TODO

  uthread_sem_wait(street->lock);
  street->num_cars--;
  VERBOSE_PRINT("now %d cars in street\n", street->num_cars);
  int other_dir_waiting = 0;
  if (street->dir == EAST){
    if (street->num_west_waiting != 0){
      other_dir_waiting = 1;
    }
  } else {
    if (street->num_east_waiting != 0){
      other_dir_waiting = 1;
    }
  }
  if (street->num_cars == 0 && other_dir_waiting == 1) {
    switch_direction();
    if (street->dir == EAST){
      VERBOSE_PRINT("switch to east\n\n");
      for (unsigned i = 0; i < street->num_east_waiting; i++) {
        uthread_sem_signal(street->switch_lock);
      }
    } else {
      VERBOSE_PRINT("switch to west\n\n");
      for (unsigned i = 0; i < street->num_west_waiting; i++) {
        uthread_sem_signal(street->switch_lock);
      }
    }
  } else {
    if (street->dir == EAST){
      VERBOSE_PRINT("west %d cars failed to switch\n", street->num_west_waiting);
    } else {
      VERBOSE_PRINT("east %d cars failed to switch\n", street->num_east_waiting);
    }
  }
  uthread_sem_signal(street->occ_lock);
  uthread_sem_signal(street->lock);
}

void recordWaitingTime (int waitingTime) {
  uthread_sem_wait (waitingHistogramLock);
  if (waitingTime < WAITING_HISTOGRAM_SIZE)
    waitingHistogram [waitingTime] ++;
  else
    waitingHistogramOverflow ++;
  uthread_sem_signal (waitingHistogramLock);
}

//
// TODO
// You will probably need to create some additional procedures etc.
//

void* car_thread(void* arg) {
	enum Direction dir = oppositeEnd[(int)arg];
	for (unsigned j = 0; j < NUM_ITERATIONS;j++) {
		int startTime = entryTicker;
		enterStreet(dir);
		recordWaitingTime(entryTicker - startTime);
		occupancyHistogram[street->dir][street->num_cars]++;
		
		for (unsigned i = 0; i < CROSSING_TIME; i++) {
			uthread_yield();
		}

    if (dir == EAST){
      VERBOSE_PRINT("east exit ");
    } else {
      VERBOSE_PRINT("west exit ");
    }
		leaveStreet();
		
		for (unsigned i = 0; i < WAIT_TIME_BETWEEN_CROSSES; i++) {
			uthread_yield();
		}
	}
}

int main (int argc, char** argv) {
  
  uthread_init(8);

  waitingHistogramLock = uthread_sem_create(1);

  initializeStreet();
  uthread_t pt [NUM_CARS];

  // TODO

  entryTicker = 0;
  for (unsigned i = 0; i < NUM_CARS; i++) {
	  pt[i] = uthread_create(car_thread, (random() % 2));
  }
  
  for (unsigned i = 0; i < NUM_CARS; i++) {
	  uthread_join(pt[i], NULL);
  }
  
  printf ("Times with 1 car  going east: %d\n", occupancyHistogram [EAST] [1]);
  printf ("Times with 2 cars going east: %d\n", occupancyHistogram [EAST] [2]);
  printf ("Times with 3 cars going east: %d\n", occupancyHistogram [EAST] [3]);
  printf ("Times with 1 car  going west: %d\n", occupancyHistogram [WEST] [1]);
  printf ("Times with 2 cars going west: %d\n", occupancyHistogram [WEST] [2]);
  printf ("Times with 3 cars going west: %d\n", occupancyHistogram [WEST] [3]);
  
  printf ("Waiting Histogram\n");
  for (int i=0; i < WAITING_HISTOGRAM_SIZE; i++)
    if (waitingHistogram [i])
      printf ("  Cars waited for           %4d car%s to enter: %4d time(s)\n",
	      i, i==1 ? " " : "s", waitingHistogram [i]);
  if (waitingHistogramOverflow)
    printf ("  Cars waited for more than %4d cars to enter: %4d time(s)\n",
	    WAITING_HISTOGRAM_SIZE, waitingHistogramOverflow);
}
