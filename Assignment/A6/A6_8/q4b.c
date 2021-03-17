int x[8] = {1, 2, 3, -1, -2, 0, 184, 340057058};
int y[8];

void main() {
	
	int r4 = 8;
	while (r4 != 0) {
		r4--;
		y[r4] = f(x[r4]);
	}
	
	for (int i = 0; i < 8; i++) {
		printf("%d\n",x[i]);
	}
	for (int i = 0; i < 8; i++) {
		printf("%d\n",y[i]);
	}
}

int f(int arg) {
	int r0 = 0;
	while (arg != 0) {
		int r3 = 0x80000000 & arg;
		if (r3 != 0) {
			r0++;
		}
		arg = arg << 1;
	}
	return r0;
}