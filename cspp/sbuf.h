#define MIN_THREAD 2

typedef struct {
	int* buf;		// Buffer array
	int n;			// Maximum number of slots
	int tpool;	        // Counts available threads
	int front;		// buf[(front + 1) % n] is the first item
	int rear;		// buf[rear % n] is the last item
	sem_t mutex;	// Protects accesses to buf
	sem_t slots;	// Counts available slots
	sem_t items;	// Counts available items
} sbuf_t;

// Create a empty, bounded, shared FIFO bufer with n slots
void sbuf_init(sbuf_t *sp, int n, int tp);

// Clean up buffer sp
void sbuf_cleanup(sbuf_t *sp);

// Insert item onto the rear of shared buffer sp
void sbuf_insert(sbuf_t* sp, int item);

// Remove and return the first item from buffer sp
int sbuf_remove(sbuf_t* sp);

int sbuf_create_threads(sbuf_t* sp, int num, void* tid, void (*create_thread)(void*));