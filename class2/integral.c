#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846
#define N 10000

int main(void) {
  double xlim = 2*PI;
  double sum = 0.0;
  for (int i=0; i<N; i++) {
    double t = (i / (double) N) * xlim;
    sum += sin(t);
  }
  printf("The integral of sin(x) from x=0 to x=2*pi is approximately %f\n", sum);

  return 0;
}
