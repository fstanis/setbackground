// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include "setbackground.h"

#ifdef __linux__ 
#include "linux/core.h"

int set_background(const char* path, int style) {
  return set_background_linux(path, style);
}
#elif _WIN32
#include "windows/core.h"

int set_background(const char* path, int style) {
  return set_background_windows(path, style);
}
#elif __APPLE__
#include "darwin/core.h"

int set_background(const char* path, int style) {
  return set_background_darwin(path, style);
}
#endif
