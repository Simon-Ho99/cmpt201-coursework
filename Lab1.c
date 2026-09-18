#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main() {
  char *lineptr = NULL;
  size_t n = 0;
  ssize_t chars_read;

  while (1) {
    printf("Enter text: ");

    chars_read = getline(&lineptr, &n, stdin);

    if (chars_read == -1) {
      break;
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
