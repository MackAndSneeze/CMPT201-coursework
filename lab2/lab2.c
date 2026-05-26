#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char *line = NULL;
  size_t n = 0;

  while (1) {
    printf("Enter programs to run.\n");
    ssize_t len = getline(&line, &n, stdin);

    line[len - 1] = '\0';

    if (len == -1) {
      break;
    }

    pid_t pid = fork();
    if (pid == 0) { // Child Process
      if (execl(line, line, NULL) == -1) {
        perror("execution of child process failed");
        free(line);
        exit(1);
      }
    } else if (pid > 0) { // Parent Process
      int status;
      if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        free(line);
        exit(1);
      }
      // if (WIFEXITED(status)) {
      //   printf("child process has exited");
      // }
    } else {
      perror("fork");
      free(line);
      exit(1);
    }
  }
  free(line);
  return 0;
}
