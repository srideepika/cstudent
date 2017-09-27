#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

// A pool is a data structure often seen in C programming and resource-constrained systems. You want to have variable length "linked" lists, but you want to bound how big they can possibly be as a group, and you want to be able to make a new node in a linked list very quickly.

// There are 32 or 2^5 items in our pool by default.
// People tend to pick powers of 2 for things like this because they're faster on a computer. 
#define POOL_SIZE (32)
// A more reasonable size might be 4096, or 2^12.
//#define POOL_SIZE (1 << 12)

// This is a magic pointer that signifies there is no "next" when we see it.
#define NULL_ENTRY (POOL_SIZE+1)

// Our "pointer" type, which refers to the next thing in a list, is defined to be an int here.
typedef int POINTER;
// Our "value" type, or what we're putting in pool and our lists, is defined to be a double here.
typedef double VALUE;

// An entry in the pool contains a "pointer" to the next element and a value.
struct Entry {
  // We assume it's part of a list; if not, it's next will be NULL_ENTRY.
  POINTER next;
  // The value stored. We never clear these, but set them anew when we allocate an entry from the pool.
  VALUE value;
};

// In C, "static" means "private to this file" and is sometimes required for constants -- it can also help the compiler optimize.
static struct Entry pool[POOL_SIZE];
// This POINTER is the start of a list, actually. This linked list will have all the items in the pool that are "free" or not currently used.
static POINTER free = 0;

// We need to make sure that the pool starts in a reasonable state.
// Therefore, we make the free list point at the first item in the pool, and every item in the pool point to the next except the last, which has the magical end of list marker, NULL_ENTRY.
void clear_pool() {
  free = 0;
  for (int i=0; i<POOL_SIZE; i++) {
    pool[i].next = i+1;
    pool[i].value = -42;
  }
  pool[POOL_SIZE-1].next = NULL_ENTRY;
}

// This function takes a value, puts it in an Entry, and returns a pointer to that Entry (its index) to us.
POINTER alloc(VALUE value) {
  // Pop from the "free" list.
  POINTER step = free;
  // If there's more free nodes, then make sure we know where they are.
  if (step != NULL_ENTRY) {
    // The second entry in the free list is now the first entry.
    free = pool[step].next;
  }
  // The entry that was previously free is now a list of length 1.
  pool[step].next = NULL_ENTRY;
  pool[step].value = value;
  // Pass back the location of that entry.
  return step;
}

// How do you count the items in a linked list?
int list_size(POINTER start) {
  // TODO, does nothing right now.
  return -1;
}

// How do you add an item to the end of a linked list?
void push_back(POINTER start, VALUE value) {
  // TODO, does nothing right now.
  return;
}

bool list_equals_array(POINTER list, double* array, int array_len) {
  if (list_size(list) != array_len) return false;
  // TODO, do this better!
  return false;
}

// Given a value and a list, alloc a new entry and put it on the front of this list.
POINTER push_front(VALUE value, POINTER list) {
  POINTER new = alloc(value);
  assert(new != NULL_ENTRY);
  // To push on the front of a linked list, we take our new node and set it's next pointer to be the old beginning of the list.
  pool[new].next = list;
  return new;
}

// Given a list, take its first element off and put it in the free list.
POINTER free_front(POINTER list) {
  // Don't do anything with empty lists.
  assert(list != NULL_ENTRY);

  // What is leftover of this list once we chop the first one off?
  POINTER leftover = pool[list].next;
  
  // Move our first node into the "free" list.
  pool[list].next = free;
  free = list;

  // return the rest of this linked list.
  return leftover;
}

// This function demonstrates writing one of our linked lists to a particular file.
void fprint_list(FILE* f, POINTER start) {
  for(POINTER x = start; x != NULL_ENTRY; x = pool[x].next) {
    fprintf(f, "%1.3f ", pool[x].value);
  }
  fprintf(f, "\n");
}
// This is the difference between printf and fprintf:
void print_list(POINTER start) {
  fprint_list(stdout, start);
}

// This is a method to debug and visualize the lists/data in the pool.
void debug_pool() {
  printf("free_list_start = %d\n", free);
  printf("NULL_ENTRY (end of list) = %d\n", NULL_ENTRY);
  for (int i=0; i<POOL_SIZE; i++) {
    printf("pool[%d] {.next=%d, .value=%lf}\n", i, pool[i].next, pool[i].value);
  }
}

// We've not dealt with command line arguments yet.
// Try running this program without arguments to see the asserts fail:
//   gcc pool_list.c && ./a.out
// Try running it with my data file:
//   gcc pool_list.c && ./a.out test.txt
int main(int argc, char **argv) {
  clear_pool();

  assert(argv != NULL);
  assert(argc == 2);

  FILE* input = fopen(argv[1], "r");
  assert(input != NULL);

  // Create a list of [9,8,7]
  POINTER test_list = push_front(9.0, push_front(8.0, alloc(7.0)));
  
  // Print test_list.
  printf("Test List:\t");
  fprint_list(stdout, test_list);

  // Create a pointer to hold a list from our file.
  POINTER file_list = NULL_ENTRY;

  // Load up entries from a file.
  while (true) {
    double value;
    // Read a floating point value from the input file.
    int status = fscanf(input, "%lf", &value);
    if (status == EOF) break;
    if (status != 1) {
      // Be nice about errors and quit if we get the wrong file.
      fprintf(stderr, "Unable to read a value, fscanf -> %d", status);
      return -1;
    }

    // Add the value we read into the list.
    file_list = push_front(value, file_list);
  }

  // Make sure we read the things we wanted to read.
  printf("File List:\t");
  fprint_list(stdout, file_list);
  
  // Print test_list; show that it still works -- reading from the file should not have changed this!
  printf("Test List:\t");
  fprint_list(stdout, test_list);

  // Look at the pool.
  debug_pool();


  // Now test the functions we wrote:
  assert(list_size(test_list) == 3);

  // Add an item, check that size increases:
  push_back(test_list, 1.0);
  assert(list_size(test_list) == 4);

  // Now make sure the list is actually correct.
  double expected[] = {9,8,7,1};
  assert(list_equals_array(test_list, expected, 4));

  return 0;
}
