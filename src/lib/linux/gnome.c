#include <glib.h>

#include "common.h"

static const char* DESKTOPS[] = {"GNOME", "Unity", "Pantheon", "Budgie:GNOME", NULL};

gboolean is_gnome(const gchar* desktop) {
  return g_strv_contains(DESKTOPS, desktop);
}

static const char* DCONF_KEY_IMAGE = "/org/gnome/desktop/background/picture-uri";
static const char* DCONF_KEY_STYLE = "/org/gnome/desktop/background/picture-options";
static const char* STYLE_CENTER = "centered";

int set_background_gnome(const gchar* path) {
  if (!dconf_write(DCONF_KEY_STYLE, STYLE_CENTER)) {
    return E_GNOME_FAIL;
  }

  int result = E_SUCCESS;
  gchar* file_path  = to_file_uri_path(path);
  if (!dconf_write(DCONF_KEY_IMAGE, file_path)) {
    result = E_GNOME_FAIL;
  }
  g_free(file_path);
  return result;
}
