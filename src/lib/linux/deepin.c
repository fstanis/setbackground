// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include <glib.h>

#include "common.h"

static const char* DESKTOP = "Deepin";

gboolean is_deepin(const gchar* desktop) {
  return g_strcmp0(desktop, DESKTOP) == 0;
}

static const char* DCONF_KEY_IMAGE = "/com/deepin/wrap/gnome/desktop/background/picture-uri";

int set_background_deepin(const gchar* path, int style) {
  if (style != STYLE_STRETCH) {
    return E_UNSUPPORTED_STYLE;
  }

  int result = E_SUCCESS;
  gchar* file_path  = to_file_uri_path(path);
  if (!dconf_write(DCONF_KEY_IMAGE, file_path)) {
    result = E_DEEPIN_FAIL;
  }
  g_free(file_path);
  return result;
}
