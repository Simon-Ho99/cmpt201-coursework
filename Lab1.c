#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main() {
  char *lineptr = NULL;
  size_t n = 0;
  ssize_t chars_read;

  while (1) {
    printf("Please enter some text: ");

    chars_read = getline(&lineptr, &n, stdin);

    if (chars_read == -1) {
      if (feof(stdin)) {
        break;
      } else {
        perror("getline failed");
        exit(EXIT_FAILURE);
      }
    }

    if (chars_read == 1 && lineptr[0] == '\n') {
      break;
    }

    printf("Token:\n");

    char *saveptr;
    char *token = strtok_r(lineptr, " \n", &saveptr);

    while (token != NULL) {
      printf(" %s\n", token);
      token = strtok_r(NULL, " \n", &saveptr);
    }
  }
  free(lineptr);
  return 0;
}
