// static.c
#include <stdio.h>

static int count = 1;
extern int count2;

int main(void) {
	printf("count = [%d]\n", count);
	func();

	printf("count2 = [%d]\n", count2);

	return 0;
}
