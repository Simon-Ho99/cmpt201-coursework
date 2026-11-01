#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("start...");
  pid_t pid = fork();

  if (pid == 0) {
    printf("child -- child: %d, parent: %d\n", getpid(), getppid());
  } else {
    printf("Parent -- child: %d, parent: %d\n", getpid(), pid);
  }

  return 0;
}
