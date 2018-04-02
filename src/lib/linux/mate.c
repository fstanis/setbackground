// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include <glib.h>

#include "common.h"

static const char* DESKTOP = "MATE";

gboolean is_mate(const gchar* desktop) {
  return g_strcmp0(desktop, DESKTOP) == 0;
}

static const char* DCONF_KEY_IMAGE = "/org/mate/desktop/background/picture-filename";
static const char* DCONF_KEY_STYLE = "/org/mate/desktop/background/picture-options";

int set_background_mate(const gchar* path, int style) {
  int result = gnome_set_style(DCONF_KEY_STYLE, style);
  if (result != E_SUCCESS) {
    return result;
  }
  if (!dconf_write(DCONF_KEY_IMAGE, path)) {
    return E_MATE_FAIL;
  }
  return E_SUCCESS;
}
