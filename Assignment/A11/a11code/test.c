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