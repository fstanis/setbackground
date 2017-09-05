#include <glib.h>

#include "common.h"

static const char* DESKTOP = "Deepin";

gboolean is_deepin(const gchar* desktop) {
  return g_strcmp0(desktop, DESKTOP) == 0;
}

static const char* DCONF_KEY = "/com/deepin/wrap/gnome/desktop/background/picture-uri";

int set_background_deepin(const gchar* path) {
  int result = E_SUCCESS;
  gchar* file_path  = to_file_uri_path(path);
  if (!dconf_write(DCONF_KEY, file_path)) {
    result = E_DEEPIN_FAIL;
  }
  g_free(file_path);
  return result;
}
