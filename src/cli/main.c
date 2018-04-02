// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include <stdio.h>
#include <string.h>

#include "setbackground.h"
#include "styles.h"
#include "errors.h"

int style_from_string(const char* input) {
  if (strcmp(input, "center") == 0) {
    return STYLE_CENTER;
  }
  if (strcmp(input, "stretch") == 0) {
    return STYLE_STRETCH;
  }
  if (strcmp(input, "tile") == 0) {
    return STYLE_TILE;
  }

  return -1;
}

int main(int argc, char** argv) {
  if ((argc < 2) || (strcmp(argv[1], "--help") == 0)) {
    puts(
      "setbackground is a cross-platform tool for changing the desktop "
      "background (wallpaper).\n\n"
      "Usage: setbackground <file> [center|stretch|tile]\n");
    return 1;
  }

  int style = STYLE_CENTER;
  if (argc > 2) {
    style = style_from_string(argv[2]);
    if (style == -1) {
      fprintf(stderr, "Invalid style: %s\n", argv[2]);
      return 1;
    }
  }

  int error = set_background(argv[1], style);
  if (error != E_SUCCESS) {
    fprintf(stderr, "An error occurred while attemping to change the background: error code %d\n", error);
    return 1;
  }
  puts("Background image changed.");
  return 0;
}
