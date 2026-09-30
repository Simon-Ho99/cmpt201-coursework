#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *msg = "CTRL-C pressed\n";
void sigint_handler(int signum) { write(STDOUT_FILENO, msg, strlen(msg)); }

int main() {
  struct sigaction sa;
  sa.sa_handler = sigint_handler;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);

  sigaction(SIGINT, &sa, NULL);

  while (1) {
    sleep(5);
  }
}
