#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *history[5];
static int history_cnt = 0;
static int history_next = 0;

void history_add(char *line) {

  if (history[history_next] != NULL) {
    free(history[history_next]);
  }

  history[history_next] = strdup(line);
  history_next = (history_next + 1) % 5;

  if (history_cnt < 5) {
    history_cnt++;
  }
}

void history_print() {
  int begin;
  if (history_cnt < 5) {
    begin = 0;
  } else {
    begin = history_next;
  }

  for (int i = 0; i < history_cnt; i++) {
    int index = (begin + i) % 5;
    fputs(history[index], stdout);
  }
}

void free_history() {
  for (int i = 0; i < 5; i++) {
    free(history[i]);
    history[i] = NULL;
  }
}

int main() {
  char *line = NULL;
  size_t size = 0;

  while (1) {
    printf("Enter input: ");
    fflush(stdout);

    ssize_t readline = getline(&line, &size, stdin);

    if (readline == -1) {
      break;
    }

    if (line == NULL) {
      perror("line");
      break;
    }

    history_add(line);

    if (strcmp(line, "print\n") == 0) {
      history_print();
    }
  }

  free(line);
  free_history();
  return 0;
}
