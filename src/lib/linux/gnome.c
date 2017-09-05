#include <glib.h>

#include "common.h"

static const char* DESKTOPS[] = {"GNOME", "Unity", "Pantheon", "Budgie:GNOME", NULL};

gboolean is_gnome(const gchar* desktop) {
  return g_strv_contains(DESKTOPS, desktop);
}

static const char* DCONF_KEY = "/org/gnome/desktop/background/picture-uri";

int set_background_gnome(const gchar* path) {
  int result = E_SUCCESS;
  gchar* file_path  = to_file_uri_path(path);
  if (!dconf_write(DCONF_KEY, file_path)) {
    result = E_GNOME_FAIL;
  }
  g_free(file_path);
  return result;
}