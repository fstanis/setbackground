#include <glib.h>

#include "common.h"

static const char* DESKTOP = "X-Cinnamon";

gboolean is_cinnamon(const gchar* desktop) {
  return g_strcmp0(desktop, DESKTOP) == 0;
}

static const char* DCONF_KEY_IMAGE = "/org/cinnamon/desktop/background/picture-uri";
static const char* DCONF_KEY_STYLE = "/org/cinnamon/desktop/background/picture-options";
static const char* STYLE_CENTER = "centered";

int set_background_cinnamon(const gchar* path) {
  if (!dconf_write(DCONF_KEY_STYLE, STYLE_CENTER)) {
    return E_CINNAMON_FAIL;
  }

  int result = E_SUCCESS;
  gchar* file_path  = to_file_uri_path(path);
  if (!dconf_write(DCONF_KEY_IMAGE, file_path)) {
    result = E_CINNAMON_FAIL;
  }
  g_free(file_path);
  return result;
}
