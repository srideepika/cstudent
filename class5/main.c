#include "city.h"
#include <stdlib.h>
#include <stdio.h>

void print_cities(city *ptrs[NUM_CITIES], int N) {
  // TODO
}

int main(void) {
  city cities[NUM_CITIES] = {0};

  // Create a list of city pointers.
  // Note that we can grab the memory addresses of the city objects even before we fill them with data from the file...
  city* ptrs[NUM_CITIES];
  for (int i=0; i<NUM_CITIES; i++) {
    ptrs[i] = &cities[i];
  }
  // Load data.
  int rc = load_cities(ptrs);
  if (rc != 0) return rc;

  // Sort by name and print data.
  qsort(ptrs, NUM_CITIES, sizeof(city*), sort_by_name);
  printf("Sort By Name:\n");
  print_cities(ptrs, 5);
  
  // Sort by population and print data.
  printf("Sort By Population:\n");
  qsort(ptrs, NUM_CITIES, sizeof(city*), sort_by_population);
  print_cities(ptrs, 5);

  printf("Average City Name Length: %1.2f\n", compute_average(ptrs, get_city_string_length));
  // TODO implement and uncomment out this:
  //printf("Average Population: %1.2f\n", compute_average(ptrs, get_city_population));

  return 0;
}
