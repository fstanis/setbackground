#include <glib.h>

#include "common.h"

static const char* DESKTOP = "MATE";

gboolean is_mate(const gchar* desktop) {
  return g_strcmp0(desktop, DESKTOP) == 0;
}

static const char* DCONF_KEY = "/org/mate/desktop/background/picture-filename";

int set_background_mate(const gchar* path) {
  if (!dconf_write(DCONF_KEY, path)) {
    return E_MATE_FAIL;
  }
  return E_SUCCESS;
}
