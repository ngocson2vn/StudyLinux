#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int fd;
  fd = open("data.txt", O_RDONLY, 0);
  if (fd == -1) {
    perror("Could not open the data file.");
  }

  off_t len;
  len = lseek(fd, 0, SEEK_END);
  
  // mmap
  void *p;
  p = mmap (0, len, PROT_READ, MAP_SHARED, fd, 0);
  if (p == MAP_FAILED) {
    perror ("mmap failed");
  }
  
  printf("Main loop\n");
  while (1) {
    sleep(1);
  }
}
