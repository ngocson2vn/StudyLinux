#include "include/csapp.h"
#include "sbuf.h"

// Create a empty, bounded, shared FIFO bufer with n slots
void sbuf_init(sbuf_t *sp, int n, int tp) {
	sp->buf = Calloc(n, sizeof(int));
	sp->n = n;
	sp->tpool = tp;
	sp->front = sp->rear = 0;
	Sem_init(&sp->mutex, 0, 1);
	Sem_init(&sp->slots, 0, n);
	Sem_init(&sp->items, 0, 0);
}

// Clean up buffer sp
void sbuf_cleanup(sbuf_t *sp) {
	Free(sp->buf);
}

// Insert item onto the rear of shared buffer sp
void sbuf_insert(sbuf_t* sp, int item) {
	P(&sp->slots); // Wait for available slot
	P(&sp->mutex); // Lock the buffer

	// Insert the item
	sp->rear = (sp->rear + 1) % (sp->n);
	sp->buf[sp->rear] = item;

	V(&sp->mutex); // Unlock the buffer
	V(&sp->items); // Announce available item
}

// Remove and return the first item from buffer sp
int sbuf_remove(sbuf_t* sp) {
	int item;
	P(&sp->items); // Wait for available item
	P(&sp->mutex); // Lock the buffer

	// Remove the item
	sp->front = (sp->front + 1) % (sp->n);
	item = sp->buf[sp->front];

	// Decrease thread count
	--sp->tpool;

	V(&sp->mutex); // Unlock the buffer
	V(&sp->slots); // Announce available slot

	return item;
}

int sbuf_create_threads(sbuf_t* sp, int num, void* tid, void (*create_thread)(void*)) {
	int i = 0;
	int tp = 0;
	P(&sp->mutex);

	if (sp->tpool <= MIN_THREAD) {
		for (i = 0; i < num; i++) {
			create_thread(tid);
			++sp->tpool;
		}

		tp = num;
	}

	V(&sp->mutex);

	return tp;
}