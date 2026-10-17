#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *current = free_list_ptr;

  while (current != NULL) {
    if (current->size >= size) {
      return current->id;
    }
    current = current->next;
  }
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  uint64_t best_fit_size = UINT64_MAX;
  struct header *current = free_list_ptr;

  while (current != NULL) {
    if (current->size >= size && current->size < best_fit_size) {
      best_fit_size = current->size;
      best_fit_id = current->id;
    }
    current = current->next;
  }
  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  uint64_t worst_fit_size = 0;
  struct header *current = free_list_ptr;

  while (current != NULL) {
    if (current->size >= size && current->size > worst_fit_size) {
      worst_fit_size = current->size;
      worst_fit_id = current->id;
    }
    current = current->next;
  }
  return worst_fit_id;
}

int main(void) {
  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for Best-Fit algorithm is: %d\n", best_fit_id);
  printf("The ID for Worst-Fit algorithm is: %d\n", worst_fit_id);

  free(free_block1);
  free(free_block2);
  free(free_block3);
  free(free_block4);
  free(free_block5);

  return 0;
}

/*
Part 2: Coalescing contiguous free blocks - pseudo-code

Assumptions:
- The free list is kept sorted by memory address (ascending).
- Each block has a size and a pointer/address.
- We are inserting exactly one newly freed block into the free list.
- We only need to merge the newly freed block with its immediate previous free block and/or
immediate next free block.

Pseudo-code:

coalesce(new_block):
  // Step 1: Find where new_block should be inserted by address.
  prev = NULL
  cur = free_list_head

  while cur != NULL and address(cur) < address(new_block):
    prev = cur
    cur = cur->next

  next = cur

  // Step 2: Merge with the next free block if they are contiguous.
  if next != NULL and address(new_block) + new_block.size == address(next);
    next_block.size = new_block.size + next.size
    new_block.next = next.next
  else:
    new_block.next = next

  // Step 3: Merge with the previous free block if they are contiguous.
  if prev != NULL and address(prev) + prev.size == address(new_block):
    prev.size = prev.size + new_block.size
    pre.next = new_block.next
  else:
    //No merge with previous; insert new_block after prev.
    new_block.next = next

    if prev == NULL:
      free_list_head = new_block
    else:
      prev.next = new_block

  // This handles all cases:
  // - merge only wiht next
  // - merge only with previous
  // - merge with both previous and next
  // - merge with neither
*/
