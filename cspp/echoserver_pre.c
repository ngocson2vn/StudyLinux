#include "include/csapp.h"
#include "sbuf.h"

#define NTHREADS 2
#define SBUFSIZE 1024

void echo_cnt(int connfd);
void create_thread();
void* thread(void* vargp);

// Shared buffer of connected descriptors
sbuf_t sbuf;

int main(int argc, char** argv) {
	int i;
	int listenfd;
	int connfd;
	int port;
	socklen_t clientlen = sizeof(struct sockaddr_in);
	struct sockaddr_in clientaddr;
	pthread_t tid;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}

	port = atoi(argv[1]);
	sbuf_init(&sbuf, SBUFSIZE, NTHREADS);
	listenfd = Open_listenfd(port);

	// Create worker threads
	for (i = 0; i < NTHREADS; i++) {
		Pthread_create(&tid, NULL, thread, NULL);
	}

	while (1) {
		connfd = Accept(listenfd, (SA*)&clientaddr, &clientlen);

		// Insert connfd in buffer
		sbuf_insert(&sbuf, connfd);

		// Create new NTHREADS threads if necessary
		int tpool = sbuf_create_threads(&sbuf, 2 * NTHREADS, &tid, create_thread);
		if (tpool > 0) {
			printf("Create %d more threads\n", tpool);
		}
	}
}

void* thread(void* vargp) {
	Pthread_detach(pthread_self());
	int ret = 0;
	while (1) {

		// Remove connfd from buffer
		int connfd = sbuf_remove(&sbuf);

		// Service client
		echo_cnt(connfd);

		printf("Close client with fd %d\n", connfd);
		Close(connfd);
		Pthread_exit(&ret);
	}
}

void create_thread(void* tid) {
	pthread_t* t = (pthread_t*)tid;
	Pthread_create(t, NULL, thread, NULL);
}