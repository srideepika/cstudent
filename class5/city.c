#include "city.h"
#include <stdio.h>
#include <string.h>

// Read from a file into an array a string that ends with a comma.
// This is "static" because it is private.
static int read_until_comma(FILE* input, char* dest, int N) {
  for (int i=0; i<N; i++) {
    int x = fgetc(input);
    if (x == EOF || x == ',') return i;
    // copy to string, unless comma or end of file.
    dest[i] = (char)x;
  }
  // Return a negative number if we ran out of space ...
  // This means we didn't find a comma.
  return -1;
}

// Code to load cities from a file.
int load_cities(city *ptrs[NUM_CITIES]) {
  FILE* fp = fopen("cities.csv", "r");
  for (int i=0; i<NUM_CITIES; i++) {
    // Read until the comma.
    int rc = read_until_comma(fp, ptrs[i]->name, CITY_STRING_SIZE);
    if (rc < 0) goto err;

    // Read a number.
    rc = fscanf(fp, "%d ", &ptrs[i]->population);
    if (rc != 1) goto err;
  }

  // This is the regular exit from this function.
  fclose(fp);
  return 0;

  // This is what we do on an error!
  // In plain C, it is common to see goto used for error-handling like this.
  // In C++ you don't see this, as you'll use a destructor to have the 
  // compiler insert this same pattern.
err:
  fprintf(stderr, "Couldn't read in a city!\n");
  fclose(fp);
  return -1;
}

int sort_by_name(const void* lhs, const void* rhs) {
  const city* lcity = *((const city**) lhs);
  const city* rcity = *((const city**) rhs);
  //printf("qsort %p <? %p\n", lhs, rhs);
  //printf("qsort %s <? %s\n", lcity->name, rcity->name);
  return strncmp(lcity->name, rcity->name, CITY_STRING_SIZE);
}

int sort_by_population(const void* lhs, const void* rhs) {
  const city* lcity = *((const city**) lhs);
  const city* rcity = *((const city**) rhs);
  //printf("qsort %p <? %p\n", lhs, rhs);
  //printf("qsort %s <? %s\n", lcity->name, rcity->name);
  return lcity->population - rcity->population;
}

int get_city_string_length(const city* x) {
  return strlen(x->name);
}

double compute_average(city* ptrs[NUM_CITIES], int (*callback)(const city*)) {
  double sum = 0;
  for (int i=0; i<NUM_CITIES; i++) {
    int x = callback(ptrs[i]);
    sum += x;
  }
  return sum / NUM_CITIES;
}

