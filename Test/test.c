#include<stdio.h>
#include<stdlib.h>
int i = 0;
int s = 0;
int a[] = {1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 324};

int main() {
    i = 0;
while (i != 10) {
    s += a[i];
    i += 1;
    
}
printf("i: %d, j: %d", i, s);
}