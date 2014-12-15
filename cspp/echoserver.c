#include "include/csapp.h"

char QUIT[5] = { 'q', 'u', 'i', 't', '\0' };

struct TidMessage {
	pthread_t tid;
	char* message;
	pthread_t* tid_array;
	size_t tid_count
	tid_message* next;
} tid_message;

struct MessageQueue {
	tid_message* tm;
	size_t tid_total;
} message_queue;

void clear_buffer(char* buffer, size_t len);
int echo(int connfd, char* buffer);
void* thread(void* vargp);

int main(int argc, char** argv) {
	int listenfd, *connfdp, port;
	socklen_t clientlen = sizeof(struct sockaddr_in);
	struct sockaddr_in clientaddr;
	pthread_t tid;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <port (above 1024)>\n", argv[0]);
		exit(0);
	}

	port = atoi(argv[1]);
	if (port <= 1024) {
		fprintf(stderr, "usage: %s <port (above 1024)>\n", argv[0]);
		exit(0);
	}

	message_queue mq;
	mq.tm = (tid_message*)calloc(1, sizeof(tid_message));
	mq.tm->tid = 0;
	mq.tm->message = 0;
	mq.tm->tid_array = 0;
	mq.tm->tid_count = 0;
	mq.tm->tid_message = 0;	

	listenfd = Open_listenfd(port);

	while (1) {
		connfdp = Malloc(sizeof(int));
		*connfdp = Accept(listenfd, (SA*)&clientaddr, &clientlen);
		Pthread_create(&tid, NULL, thread, connfdp);
	}
}

// Thread routine
void* thread(void* vargp) {
	int connfd = *(int*)vargp;
	pthread_t tid = pthread_self();
	Pthread_detach(tid);
	Free(vargp);
	char buffer[1024];

	while (1) {

		int i = 0;

		// clear the buffer
		for (i = 0; i < 1024; i++) {
			buffer[i] = '\0';
		}

		int count = echo(connfd, buffer);
		printf("TID:%d count:%d buffer:%s", tid, count, buffer);

		int quited = 1;
		if (count == 6) {
			for (i = 0; i < count - 2; i++) {
				if (buffer[i] != QUIT[i]) {
					quited = 0;
					break;
				}
			}

			if (buffer[count - 2] != '\r' || 
				buffer[count - 1] != '\n') 
			{
				quited = 0;
			}
	 	} else {
	 		quited = 0;
	 	}

	 	if (quited) {
	 		break;
	 	}
	}

	Close(connfd);
	
	return NULL;
}

int echo(int connfd, char* buffer) {
  size_t count = 0;
  count = Read(connfd, buffer, 1024);
  Write(connfd, buffer, count);
}
