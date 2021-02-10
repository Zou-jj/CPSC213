#include <stdlib.h>
#include <stdio.h>

// YOU: Allocate these global variables, using these names
int  a;
int* p;
int  b[5];

int main (int argv, char** argc) {
  // Ignore this block of code
  if (argv != 6) {
    fprintf (stderr, "usage: a b c d e\n");
    // exit (EXIT_FAILURE);
  }
  b[0] = 1;
  b[1] = 2;
  b[2] = 3;
  b[3] = 4;
  b[4] = 5;

  // YOU: Implement this code
  a = 3;
  p = &a;
  *p = *p - 1;

  p = &b[0];
  p++;
  p[a] = b[a];
  *(p+3) = b[0];

  // Ignore this block of code
  printf ("a=%d *p=%d\n", a, *p);
  printf("%p, %p\n", p, &b[1]);
  for (int k=0; k<5; k++)
    printf("b[%d]=%d, ",k,b[k]);
  printf("\n");
}
