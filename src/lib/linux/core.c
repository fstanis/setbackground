// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include "core.h"

#include <glib.h>

#include "common.h"
#include "platforms.h"

int set_background_linux(const char* path, int style) {
  if (!file_exists(path)) {
    return E_INVALID_PATH;
  }
  gchar* real_path = get_real_path(path);
  if (!real_path) {
    return E_INVALID_PATH;
  }

  gchar* desktop = get_desktop_environment();
  int result = E_UNSUPPORTED_DESKTOP_ENVIRONMENT;
  if (is_gnome(desktop)) {
    result = set_background_gnome(real_path, style);
  } else if (is_kde(desktop)) {
    result = set_background_kde(real_path, style);
  } else if (is_xfce(desktop)) {
    result = set_background_xfce(real_path, style);
  } else if (is_cinnamon(desktop)) {
    result = set_background_cinnamon(real_path, style);
  } else if (is_mate(desktop)) {
    result = set_background_mate(real_path, style);
  } else if (is_deepin(desktop)) {
    result = set_background_deepin(real_path, style);
  } else if (is_lxde(desktop)) {
    result = set_background_lxde(real_path, style);
  }
  g_free(desktop);
  g_free(real_path);  
  return result;
}
