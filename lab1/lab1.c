#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

  char *line = NULL;
  size_t n = 0;

  printf("Please enter some text: ");

  size_t len = getline(&line, &n, stdin);

  if (len < 0) {
    perror("getline failed");
    free(line);
    exit(EXIT_FAILURE);
  }

  char *saveptr = NULL;
  char *ret = strtok_r(line, " ", &saveptr);
  printf("Tokens:\n");
  printf("  %s\n", ret);
  while ((ret = strtok_r(NULL, " ", &saveptr))) {
    printf("  %s\n", ret);
  }
  free(line);
  return 0;
}
