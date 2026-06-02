#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const static int HISTORY_SIZE = 5;

typedef struct LL {
  char *input;
  struct LL *next;
} LL;

LL *head = NULL;
LL *tail = NULL;
int history_count = 0;

char *get_input(void);
void add_to_history(char *input);
void rm_history_tail(void);
void print_history(void);
void free_history(void);

int main() {
  while (1) {
    char *input = get_input();
    if (input == NULL) {
      perror("get_input() failed\n");
      break;
    }
    add_to_history(input);
    if (strcmp(input, "print") == 0) {
      print_history();
    }
  }

  free_history();
  return 0;
}

char *get_input(void) {
  char *line = NULL;
  size_t size = 0;

  printf("Enter input: ");
  ssize_t len = getline(&line, &size, stdin);

  if (len == -1) {
    free(line);
    return NULL;
  }

  if ((len > 0) && (line[len - 1] == '\n')) {
    line[len - 1] = '\0';
  }
  return line;
}

void add_to_history(char *input) {
  LL *new_node = malloc(sizeof(LL));
  if (new_node == NULL) {
    perror("malloc error");
    free(input);
    exit(-1);
  }
  new_node->input = input;
  new_node->next = NULL;
  if (tail == NULL) {
    head = new_node;
    tail = new_node;
  } else {
    tail->next = new_node;
    tail = new_node;
  }
  history_count++;
  if (history_count > HISTORY_SIZE) {
    rm_history_tail();
  }
}

void rm_history_tail(void) {
  if (head == NULL) {
    return;
  }
  LL *old_head = head;
  head = head->next;
  if (head == NULL) {
    tail = NULL;
  }
  free(old_head->input);
  free(old_head);
  history_count--;
}

void print_history(void) {
  LL *current = head;
  while (current != NULL) {
    printf("%s\n", current->input);
    current = current->next;
  }
}

void free_history(void) {
  while (head != NULL) {
    rm_history_tail();
  }
}
