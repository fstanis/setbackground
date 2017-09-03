#include <stdio.h>

#include "setbackground.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "must specify 1 argument, got %d\n", argc-1);
    return 1;
  }
  printf("%d\n", set_background(argv[1]));
}
