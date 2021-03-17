#include<stdio.h>

int i   = -1;
int n   = 5;
int a[] = (int[]) {10, 20, 30, 40, 50};
int b[] = (int[]) {11, 20, 28, 44, 48};
int c   = 0;

int main(){
  for (i = 0; i<n; i++)
  if (a[i] > b[i])
  c += 1;
  printf("i: %d\n", i);
  printf("n: %d\n", n);
  for (int index = 0; index < 5; index++){
    printf("a[%d]: %d\n", index, a[index]);
  }
  for (int index = 0; index < 5; index++){
    printf("b[%d]: %d\n", index, b[index]);
  }
  printf("c: %d\n", c);
}



