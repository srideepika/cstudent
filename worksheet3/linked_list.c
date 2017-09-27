#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef double VALUE;
typedef struct ListEntry_s {
  struct ListEntry_s* next;
  VALUE value;
} ListEntry;
typedef ListEntry* POINTER;

// This function takes a value, puts it in an Entry, and returns a pointer to that Entry (its index) to us.
POINTER alloc(VALUE value) {
  // Ask the OS for some memory of the correct size.
  POINTER step = (POINTER) malloc(sizeof(ListEntry));
  assert(step != NULL);

  step->next = NULL;
  step->value = value;

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
  assert(new != NULL);
  new->next = list;
  return new;
}

// Given a list, take its first element off and put it in the free list.
POINTER free_front(POINTER list) {
  // Don't do anything with empty lists.
  assert(list != NULL);

  // What is leftover of this list once we chop the first one off?
  POINTER leftover = list->next;
  
  // What is created by malloc is destroyed by free.
  free(list);

  // return the rest of this linked list.
  return leftover;
}

// This function demonstrates writing one of our linked lists to a particular file.
void fprint_list(FILE* f, POINTER start) {
  for(POINTER x = start; x != NULL; x = x->next) {
    fprintf(f, "%1.3f ", x->value);
  }
  fprintf(f, "\n");
}
// This is the difference between printf and fprintf:
void print_list(POINTER start) {
  fprint_list(stdout, start);
}

// We've not dealt with command line arguments yet.
// Try running this program without arguments to see the asserts fail:
//   gcc linked_list.c && ./a.out
// Copy the data file to this directory.
//   cp ../class3/test.txt .
// Try running it with my data file:
//   gcc linked_list.c && ./a.out test.txt
int main(int argc, char **argv) {
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
  POINTER file_list = NULL;

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
