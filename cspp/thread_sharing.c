#include "include/csapp.h"

#define N 2

void* thread(void* vargp);

char** ptr;

int main() {
	int i;
	int* id;
	pthread_t tid;

	char* msgs[N] = {
		"Hello from foo",
		"Hello from bar"
	};

	ptr = msgs;

	for (i = 0; i < N; i++) {
		id = (int*)calloc(1, sizeof(int));
		*id = i;
		Pthread_create(&tid, NULL, thread, id);
	}

	Pthread_exit(NULL);
}

void* thread(void* vargp) {
	int myid = *((int*)vargp);
	Free(vargp);
	static int cnt = 0;
	printf("[%d]: %s (cnt = %d)\n", myid, ptr[myid], ++cnt);

	return NULL;
}