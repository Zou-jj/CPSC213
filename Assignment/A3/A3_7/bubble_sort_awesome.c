#include <stdlib.h>
#include <stdio.h>

void sort (int n, int *val) {
  int t;
  for (int i=n-1; i>0; i--)
    for (int j=i-1; j>=0; j--)
      if (*(val + i) < *(val + j)) {
        t = *(val + i);
        *(val + i) = *(val + j);
        *(val + j) = t;
      }
}

int main (int argc, char** argv) {
  char* ep;
  int   n;
  n = argc - 1;
  int *val = malloc(n * sizeof(int));
  for (int i=0; i<n; i++) {
    *(val + i) = strtol (*(argv + i + 1), &ep, 10);
    if (*ep) {
      fprintf (stderr, "Argument %d is not a number\n", i);
      return -1;
    }
  }
  sort (n, val);
  for (int i=0; i<n; i++)
    printf ("%d\n", *(val + i));
  free(val);
  val = NULL;
  return 0;
}