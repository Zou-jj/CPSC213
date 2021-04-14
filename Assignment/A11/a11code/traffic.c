// #include <stdlib.h>
// #include <stdio.h>
// #include <assert.h>
// #include <fcntl.h>
// #include <unistd.h>

// #include <stdint.h>

// #include "uthread.h"
// #include "uthread_mutex_cond.h"

// #ifdef VERBOSE
// #define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__)
// #else
// #define VERBOSE_PRINT(S, ...) ((void) 0) // do nothing
// #endif

// #define MAX_OCCUPANCY  3
// #define NUM_ITERATIONS 1
// #define NUM_CARS       10

// // These times determine the number of times yield is called when in
// // the street, or when waiting before crossing again.
// #define CROSSING_TIME             NUM_CARS
// #define WAIT_TIME_BETWEEN_CROSSES NUM_CARS

// /**
//  * You might find these declarations useful.
//  */
// enum Direction {EAST = 0, WEST = 1};
// const static enum Direction oppositeEnd [] = {WEST, EAST};

// struct Street {
//   // TODO
//   uthread_mutex_t lock;
//   uthread_cond_t cond_cross;
//   int num_cars;
//   int num_before_switch; // number of cars remaining to enter before switching traffic direction once a different side has queued
//   enum Direction dir;
//   enum Direction dirQueue;
// } Street;

// struct Street* street;

// void initializeStreet(void) {
//   // TODO
//   street = malloc(sizeof (struct Street));
//   street->num_cars = 0;
//   street->num_before_switch = 6;
//   street->dir = EAST;
//   street->dirQueue = EAST;
//   street->lock = uthread_mutex_create();
//   street->cond_cross = uthread_cond_create(street->lock);
// }

// #define WAITING_HISTOGRAM_SIZE (NUM_ITERATIONS * NUM_CARS)
// int             entryTicker;                                          // incremented with each entry
// int             waitingHistogram [WAITING_HISTOGRAM_SIZE];
// int             waitingHistogramOverflow;
// uthread_mutex_t waitingHistogramLock;
// int             occupancyHistogram [2] [MAX_OCCUPANCY + 1];

// void switch_direction() {
// 	if (street->dir == WEST) {
// 		  street->dir = EAST;
// 	  } else {
// 		  street->dir = WEST;
// 	  }
// }

// void enterStreet (enum Direction g) {
//   // TODO
//   uthread_mutex_lock(street->lock);
//   printf("entering: ");
//   if (g == EAST){
//     printf("east\n");
//   } else {
//     printf("west\n");
//   }
//   while (street->num_cars >= 3 || (street->num_before_switch == 0) || (g != street->dir)) {
// 	  if (g != street->dir) {
// 		street->dirQueue = g;
// 	  }
// 	  uthread_cond_wait(street->cond_cross);
//   }
//   entryTicker++;
//   street->num_cars++;
//   if (street->dirQueue != street->dir) {
// 	street->num_before_switch--;
//   }
//   printf("entering, now with %d cars\n",street->num_cars);
//   uthread_mutex_unlock(street->lock);
// }

// void leaveStreet(void) {
//   // TODO
//   uthread_mutex_lock(street->lock);
//   street->num_cars--;
//   if (street->num_before_switch == 0 && street->num_cars == 0) {
// 	  // switch_direction();
// 	  // street->num_before_switch = 6;
// 	  if (street->dirQueue != street->dir) {
// 		  switch_direction();
// 		  street->num_before_switch = 6;
// 	  } else {
// 		  street->num_before_switch++;
// 	  }
//   }
//   if (street->num_cars == 0 && street->num_before_switch != 0 && street->dirQueue != street->dir) {
// 	  street->num_before_switch = 6;
// 	  switch_direction();
//   }
//   printf("exiting, now with %d cars, %d to enter before switching\n",street->num_cars, street->num_before_switch);
//   printf("exiting: ");
//   if (street->dir == EAST){
//     printf("east\n");
//   } else {
//     printf("west\n");
//   }
//   uthread_cond_broadcast(street->cond_cross);
//   uthread_mutex_unlock(street->lock);
// }

// void recordWaitingTime (int waitingTime) {
//   uthread_mutex_lock (waitingHistogramLock);
//   if (waitingTime < WAITING_HISTOGRAM_SIZE)
//     waitingHistogram [waitingTime] ++;
//   else
//     waitingHistogramOverflow ++;
//   uthread_mutex_unlock (waitingHistogramLock);
// }

// //
// // TODO
// // You will probably need to create some additional procedures etc.
// //



// void* car_thread(void* arg) {
// 	enum Direction dir = oppositeEnd[(int)arg];
// 	for (unsigned j = 0; j < NUM_ITERATIONS;j++) {
// 		int startTime = entryTicker;
// 		enterStreet(dir);
// 		recordWaitingTime(entryTicker - startTime);
// 		occupancyHistogram[street->dir][street->num_cars]++;
		
// 		for (unsigned i = 0; i < CROSSING_TIME; i++) {
// 			uthread_yield();
// 		}
// 		leaveStreet();
		
// 		for (unsigned i = 0; i < WAIT_TIME_BETWEEN_CROSSES; i++) {
// 			uthread_yield();
// 		}
// 	}
// }

// int main (int argc, char** argv) {

//   uthread_init(1);

//   waitingHistogramLock = uthread_mutex_create();
  
//   initializeStreet();
//   uthread_t pt [NUM_CARS];
//   uintptr_t r;
//   // TODO
//   entryTicker = 0;
//   for (unsigned i = 0; i < NUM_CARS; i++) {
// 	  r = (random() % 2);
// 	  pt[i] = uthread_create(car_thread, r);
//   }
  
//   for (unsigned i = 0; i < NUM_CARS; i++) {
// 	  uthread_join(pt[i], NULL);
//   }
//   printf ("Times with 1 car  going east: %d\n", occupancyHistogram [EAST] [1]);
//   printf ("Times with 2 cars going east: %d\n", occupancyHistogram [EAST] [2]);
//   printf ("Times with 3 cars going east: %d\n", occupancyHistogram [EAST] [3]);
//   printf ("Times with 1 car  going west: %d\n", occupancyHistogram [WEST] [1]);
//   printf ("Times with 2 cars going west: %d\n", occupancyHistogram [WEST] [2]);
//   printf ("Times with 3 cars going west: %d\n", occupancyHistogram [WEST] [3]);
  
//   printf ("Waiting Histogram\n");
//   for (int i=0; i < WAITING_HISTOGRAM_SIZE; i++)
//     if (waitingHistogram [i])
//       printf ("  Cars waited for           %4d car%s to enter: %4d time(s)\n",
// 	      i, i==1 ? " " : "s", waitingHistogram [i]);
//   if (waitingHistogramOverflow)
//     printf ("  Cars waited for more than %4d cars to enter: %4d time(s)\n",
// 	    WAITING_HISTOGRAM_SIZE, waitingHistogramOverflow);
// }

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdint.h>

#include "uthread.h"
#include "uthread_mutex_cond.h"

uthread_mutex_t mx;
uthread_cond_t cond1;
uthread_cond_t cond2;

void* a(){
    lock(mx);
    p();
    signal(cond2);
    wait(cond1);
    n();
    unlock(mx);
}

void* b(){
    lock(mx);
    h();
    wait(cond2);
    k();
    signal(cond1);
    unlock(mx);
}

int main(){
    uthread_init(1);
    mx = uthread_mutex_create();
    cond1 = uthread_cond_create(mx);
    cond2 = uthread_cond_create(mx);
    uthread_join(a, NULL);
    uthread_join(b, NULL);
}