#include "setbackground.h"

#ifdef __linux__ 
#include "linux/core.h"

int set_background(const char* path) {
  return set_background_linux(path);
}
#elif _WIN32
#include "windows/core.h"

int set_background(const char* path) {
  return set_background_windows(path);
}
#elif __APPLE__
#include "darwin/core.h"

int set_background(const char* path) {
  return set_background_darwin(path);
}
#endif
