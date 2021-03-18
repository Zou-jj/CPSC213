#include <stdlib.h>
#include <stdio.h>
#include "int_element.h"
#include "refcount.h"

/* TODO: Implement all public int_element functions, including element interface functions.

You may add your own private functions here too. */
struct int_element {
  int num;
};

struct int_element *int_element_new(int value) {
//   rc_finalizer_t finalizer = NULL;
  struct int_element *e = rc_malloc(sizeof(*e), NULL);
  if(e == NULL) {
    /* out of memory? */
    return NULL;
  }
  e->num = value;
  return e;
}

int int_element_get_value(struct int_element *e) {
    return e->num;
}

int is_int_element(struct element *e) {
    if (sizeof(e) == sizeof(struct int_element)){
        return 1;
    }
    return 0;
}