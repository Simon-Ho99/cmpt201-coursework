#define _DEFAULT_SOURCE
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 256
#define EXTRA_SIZE 256
#define BLOCK_SIZE 128

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  int len;

  if (data_size == sizeof(uint64_t)) {
    len = snprintf(buf, BUF_SIZE, format, *(uint64_t *)data);
  } else {
    len = snprintf(buf, BUF_SIZE, format, *(void **)data);
  }

  if (len < 0) {
    perror("snprintf");
    exit(EXIT_FAILURE);
  }
  write(STDOUT_FILENO, buf, len);
}

void print_byte(unsigned char value) {
  char buf[BUF_SIZE];
  int len = snprintf(buf, BUF_SIZE, "%u\n", value);
  if (len < 0) {
    perror("snprintf");
    exit(EXIT_FAILURE);
  }
  write(STDOUT_FILENO, buf, len);
}

int main(void) {
  void *new_space = sbrk(EXTRA_SIZE);
  if (new_space == (void *)-1) {
    perror("sbrk");
    exit(EXIT_FAILURE);
  }

  struct header *first_block = (struct header *)new_space;
  struct header *second_block = (struct header *)((char *)new_space + BLOCK_SIZE);

  first_block->size = BLOCK_SIZE;
  first_block->next = NULL;

  second_block->size = BLOCK_SIZE;
  second_block->next = first_block;

  print_out("first block:       %p\n", &first_block, sizeof(&first_block));
  print_out("second block:      %p\n", &second_block, sizeof(&second_block));
  print_out("first block size:  %lu\n", &first_block->size, sizeof(uint64_t));
  print_out("first block next:  %p\n", &first_block->next, sizeof(&first_block->next));
  print_out("second block size: %lu\n", &second_block->size, sizeof(uint64_t));
  print_out("second block next: %p\n", &second_block->next, sizeof(&second_block->next));

  size_t data_size = BLOCK_SIZE - sizeof(struct header);

  unsigned char *first_data = (unsigned char *)first_block + sizeof(struct header);
  unsigned char *second_data = (unsigned char *)second_block + sizeof(struct header);

  memset(first_data, 0, data_size);
  memset(second_data, 1, data_size);

  print_out("first block:       %p\n", &first_block, sizeof(&first_block));
  print_out("second block:      %p\n", &second_block, sizeof(&second_block));
  print_out("first block size:  %lu\n", &first_block->size, sizeof(uint64_t));
  print_out("first block next:  %p\n", &first_block->next, sizeof(&first_block->next));
  print_out("second block size: %lu\n", &second_block->size, sizeof(uint64_t));
  print_out("second block next: %p\n", &second_block->next, sizeof(&second_block->next));

  for (size_t i = 0; i < data_size; i++) {
    print_byte(first_data[i]);
  }
  for (size_t i = 0; i < data_size; i++) {
    print_byte(second_data[i]);
  }

  return 0;
}
