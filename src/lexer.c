#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>    // For open()
#include <unistd.h>   // For read(), write(), close()

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: ./nulo <filename>\n", argv[0]);
    return 1;
  }

  char *filename = argv[1];

  int fd = open (filename, O_RDONLY);
  if (fd == -1) {
    perror("Error opening file");
    return 1;
  }

  char buffer[BUFFER_SIZE];
  ssize_t bytes_read;

  while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {

    for (ssize_t i = 0; i < bytes_read; i++) {
      if (buffer[i] == ' ') {
        buffer[i] = '\n';
      }
    }

    ssize_t bytes_written = write(STDOUT_FILENO, buffer, bytes_read);

    if (bytes_written == -1) {
      perror ("Error writing to stdout");
      return 1;
    }
  }

  if (bytes_read == -1) {
    perror("Error reading file");
    close(fd);
    return 1;
  }

  close(fd);
  return 0;
}
