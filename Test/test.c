#include<stdio.h>
#include<stdlib.h>

int main() {
    int a[] = { 8, 9, 10, 11, 12 };
    int* i = &a[0];
    printf("%d\n", &i[0]);
    printf("%d\n", i);
    printf("%d\n", *i);
    printf("%d\n", *(i+4));
}