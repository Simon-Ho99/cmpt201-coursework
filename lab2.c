#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *line = NULL;
  size_t size = 0;

  printf("Enter programs to run.\n");

  while (1) {
    printf("> ");
    fflush(stdout);

    if (getline(&line, &size, stdin) == -1) {
      perror("getline");
      free(line);
      exit(EXIT_FAILURE);
    }

    line[strcspn(line, "\n")] = '\0';

    pid_t pid = fork();

    if (pid) {
      int wstatus = 0;
      if (waitpid(pid, &wstatus, 0) == -1) {
        free(line);
        exit(EXIT_FAILURE);
      }
    } else {
      if (execlp(line, line, NULL) == -1) {
        perror("Exec failure");
        exit(EXIT_FAILURE);
      }
    }
  }
  free(line);
  return 0;
}
