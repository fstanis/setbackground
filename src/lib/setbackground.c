#include "setbackground.h"

#include "linux/core.h"

int set_background(const char* path) {
  return set_background_linux(path);
}
