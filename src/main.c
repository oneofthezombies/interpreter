#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 256

volatile sig_atomic_t stop;

void handle_sigint(int sig) {
  printf("signal: %d", sig);
  stop = 1;
}

int main() {
  stop = 0;
  char input[BUFFER_SIZE] = {
      0,
  };

  signal(SIGINT, handle_sigint);
  while (stop == 0) {
    sleep(1);
  }

  return 0;
}
