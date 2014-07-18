#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define TIMEOUT 5		// select timeout in seconds
#define BUF_LEN 1024	// read buffer in bytes

int main(void) {
	struct timeval tv;
	fd_set readfds;
	fd_set writefds;
	int ret;
	int n;
	const char* file_path = "/tmp/select26061985.txt";
	
	int fd_w = open(file_path, O_CREAT | O_WRONLY);
	FD_ZERO(&writefds);

	if (fd_w > 0) {
		printf("open fd = %d\n", fd_w);
		FD_SET(fd_w, &writefds);
	} else {
		perror("open");
	}

	n = (fd_w > 0) ? fd_w + 1 : STDIN_FILENO + 1;

	// Wait on stdin for input.
	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);

	// Wait up to five seconds.
	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;

	// All right, now block!
	ret = select(n, &readfds, &writefds, NULL, &tv);

	if (ret == -1) {
		perror("select");
		return 1;
	} else if (!ret) {
		printf("%d seconds elapsed.\n", TIMEOUT);
		return 0;
	}

	printf("remain %d seconds\n", tv.tv_sec);

	/*
	 * Is your file descriptor ready to read?
	 * (It must be, as it was the only fd that
	 * we provided and the call returned
	 * nonzero, but we will humor ourselves.)
	 */
	if (FD_ISSET(STDIN_FILENO, &readfds)) {
		printf("fd %d is ready to read\n", STDIN_FILENO);

		char buf[BUF_LEN + 1];
		int len;

		// guaranteed to not block
		len = read(STDIN_FILENO, buf, BUF_LEN);
		if (len == -1) {
			perror("read");
			return 1;
		}

		if (len) {
			buf[len] = '\0';
			printf("read: %s\n", buf);
		}
	}

	if (FD_ISSET(fd_w, &writefds)) {
		printf("fd %d is ready to write\n", fd_w);

		int ret_w;
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		FILE* stream = fdopen(fd_w, "w");

		ret_w = fprintf(stream, "%d-%d-%d %d:%d:%d My name is Son\n",
				tm.tm_year + 1900,
				tm.tm_mon + 1,
				tm.tm_mday, 
				tm.tm_hour,
				tm.tm_min,
				tm.tm_sec);

		if (ret_w == -1) {
			perror("fprintf");
			fclose(stream);
			close(fd_w);
			return 1;
		}

		fclose(stream);
		close(fd_w);
	}

	return 0;
}
