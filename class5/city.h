#ifndef _CITY_H
#define _CITY_H 1

#define CITY_STRING_SIZE 80
#define NUM_CITIES 30

// A city has a name and a population.
typedef struct city_s {
  int population;
  char name[CITY_STRING_SIZE];
} city;

// Load cities from cities.csv file.
int load_cities(city *ptrs[NUM_CITIES]);

// For use with qsort.
int sort_by_name(const void* lhs, const void* rhs);
int sort_by_population(const void* lhs, const void* rhs);

// For use with compute_average.
int get_city_string_length(const city* x);
int get_city_population(const city* x);
// Compute the average of the function applied to a list of a cities.
double compute_average(city* ptrs[NUM_CITIES], int (*callback)(const city*));

#endif
