#include <stdio.h>

int count;
void write_extern();

int main(void) {
	count = 5;
	write_extern();
}
