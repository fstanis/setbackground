// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include <stdio.h>
#include <string.h>

#include "setbackground.h"
#include "errors.h"

int main(int argc, char** argv) {
  if ((argc != 2) || (strcmp(argv[1], "--help") == 0)) {
    puts(
      "setbackground is a cross-platform tool for changing the desktop "
      "background (wallpaper).\n\n"
      "Usage: setbackground [file]\n");
    return 1;
  }
  int error = set_background(argv[1]);
  if (error != E_SUCCESS) {
    fprintf(stderr, "An error occurred while attemping to change the background: error code %d\n", error);
    return 1;
  }
  puts("Background image changed.");
  return 0;
}
