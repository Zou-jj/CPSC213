#include<stdio.h>

int a, b;

void math() {
    a = ((((b + 1) + 4) / 2) & b) << 2;
}

int main() {
    a = 1;
    b = 2;
    math();
    printf("%d", a);
}