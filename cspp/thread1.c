#include "include/csapp.h"

void* thread(void *vargp);

int main() {
	pthread_t tid;

	printf("Create a peer thread\n");
	Pthread_create(&tid, NULL, thread, NULL);

	printf("Waiting for the peer thread exits\n");
	Pthread_join(tid, NULL);

	printf("Exit the main thread\n");
	exit(0);
}

// Thread routine
void* thread(void *vargp) {
	printf("Hello, world! (from peer thread)\n");
	printf("Now the peer thread will sleep 30 seconds\n");
	sleep(30);
	return NULL;
}