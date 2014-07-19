#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define TIMEOUT 10		// select timeout in seconds
#define BUF_LEN 1024	// read buffer in bytes

int main(void) {
	struct timeval tv;
	fd_set readfds;
	int ret;
	int n;

	printf("PID = %d\n", getpid());

	const char* file_path = "/tmp/select26061985.txt";
	
	int fd_r = open(file_path, O_RDONLY);

	if (fd_r > 0) {
		printf("open fd = %d\n", fd_r);
	} else {
		perror("open");
		return 1;
	}

	while (1) {
		FD_ZERO(&readfds);
		
		FD_SET(fd_r, &readfds);

		// Wait on stdin for input.
		FD_SET(STDIN_FILENO, &readfds);
		
		n = fd_r + 1;

		// Wait up to TIMEOUT seconds.
		tv.tv_sec = TIMEOUT;
		tv.tv_usec = 0;

		// All right, now block!
		ret = select(n, &readfds, NULL, NULL, &tv);

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
		int fd = 0;
		for (fd; fd < n; fd++) {
			if (FD_ISSET(fd, &readfds)) {
				char buf[BUF_LEN + 1];
				int len;
				printf("fd %d is ready to read\n", fd);

				// guaranteed to not block
				while ((len = read(fd, buf, BUF_LEN)) > 0) {
					buf[len] = '\0';
					printf("read: %s\n", buf);
					if (fd == STDIN_FILENO) {
						break;
					}
				}

				if (len == 0) {
					printf("fd %d reached EOF\n", fd);
				}

				printf("\n");
			}
		}

		sleep(2);
	}

	return 0;
}
