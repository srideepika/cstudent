#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

// TODO:
// Make your screen bigger, e.g., 20x20. Replace all references to the size with WIDTH and HEIGHT, so you can change this.
// Make a function to put a smiley face into the screen array. Start with write_smiley(char** screen, int x, int y), with x=0 and y=0.
// 012345
// 1 | |
// 2\___/
// 
// Improve the function to look at x and y, so you can put many smileys onto your "screen".
// Improve the function to know about WIDTH and HEIGHT so it should not cause weirdness if you don't have enough space on your "screen" for it.
// Improve your function to do nothing if it would run into another smiley.
//
// Build another function that draws something of your own design.

void write_smiley(char** screen, int x, int y) {
  assert(x >= 0 && x <= 10);
  assert(y >= 0 && y <= 10);
  assert(screen != NULL);
  assert(screen[0] != NULL);
}

// This is a helper to print some number of # on a line followed by a newline.
void print_hline(int size) {
  for(int i=0; i<size; i++) {
    printf("#");
  }
  printf("\n");
}

int main(void) {
  // This is our screen, for now.
  char screen[10][10];

  // What does memset do? Why are we using it?
  memset(&screen, ' ', 10*10);

  // These print statements talk about how to use sizeof.
  printf("sizeof(char)=%d\n", (int) sizeof(char));
  printf("sizeof(int)=%d\n", (int) sizeof(int));
  printf("sizeof(float)=%d\n", (int) sizeof(float));
  printf("sizeof(double)=%d\n", (int) sizeof(double));
  printf("sizeof(uint32_t)=%d\n", (int) sizeof(uint32_t));
  printf("sizeof(char*)=%d\n", (int) sizeof(char*));
  printf("sizeof(screen)=%d\n", (int) sizeof(screen));
  printf("sizeof(screen[0])=%d\n", (int) sizeof(screen[0]));
  printf("sizeof(&screen[0])=%d\n", (int) sizeof(&screen[0]));
  printf("sizeof(screen[0][0])=%d\n", (int) sizeof(screen[0][0]));
  printf("sizeof(&screen[0][0])=%d\n", (int) sizeof(&screen[0][0]));
  printf("10*10=%d\n", 10*10);


  // This is an example of how to 'draw' or access a 2d array.
  screen[0][4] = '!';
  screen[1][5] = '!';
  screen[9][9] = '@';

  // The following code prints the values in your screen. You'll want to draw smileys before this point.
  print_hline(12);
  for(int i=0; i<10; i++) {
    printf("#%.*s#\n", 10, screen[i]);
  }
  print_hline(12);
}
