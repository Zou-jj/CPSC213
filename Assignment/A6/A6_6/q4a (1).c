int a[10];

void main() {
	foo();
	for (int i = 0; i < 10; i++) {
		printf("%d\n",a[i]);
	}
}

void foo() {
	int var0 = 1;
	int var1 = 2;
	bar(3,4);
	bar(var0,var1);
}

void bar(int arg0, int arg1) {
	a[arg1] = arg0 + a[arg1];
}