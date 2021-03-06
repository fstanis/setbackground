// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include <glib.h>

#include "common.h"

static const char* DESKTOP = "X-Cinnamon";

gboolean is_cinnamon(const gchar* desktop) {
  return g_strcmp0(desktop, DESKTOP) == 0;
}

static const char* DCONF_KEY_IMAGE = "/org/cinnamon/desktop/background/picture-uri";
static const char* DCONF_KEY_STYLE = "/org/cinnamon/desktop/background/picture-options";

int set_background_cinnamon(const gchar* path, int style) {
  int result = gnome_set_style(DCONF_KEY_STYLE, style);
  if (result != E_SUCCESS) {
    return result;
  }

  gchar* file_path  = to_file_uri_path(path);
  if (!dconf_write(DCONF_KEY_IMAGE, file_path)) {
    result = E_CINNAMON_FAIL;
  }
  g_free(file_path);
  return result;
}
