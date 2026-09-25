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
      return 1;
    }

    line[strcspn(line, "\n")] = '\0';

    pid_t pid = fork();

    // child
    if (pid == 0) {
      execlp(line, line, NULL);
      printf("Exec failure");
      exit(1);
    } else if (pid > 0) {
      // parent
      if (waitpid(pid, NULL, 0) == -1) {
        perror("waitpid");
        free(line);
        return 1;
      }
    }
  }
  free(line);
  return 0;
}
