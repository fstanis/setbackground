#include <glib.h>

#include "common.h"

static const char* DESKTOP = "XFCE";

gboolean is_xfce(const gchar* desktop) {
  return g_strcmp0(desktop, DESKTOP) == 0;
}

static const char* DESKTOP_CHANNEL = "xfce4-desktop";
static const char* PROPERTY_BASE = "/backdrop/screen0/monitor%d/workspace0/last-image";

int set_background_xfce(const gchar* path) {
  int result = E_XFCE_FAIL;

  gboolean monitor_exists = TRUE;
  for (int monitor = 0; monitor_exists; monitor++) {
    gchar* property = g_strdup_printf(PROPERTY_BASE, monitor);

    monitor_exists = xfconf_has_property(DESKTOP_CHANNEL, property);
    if (monitor_exists) {
      if (xfconf_write_property(DESKTOP_CHANNEL, property, path)) {
        result = E_SUCCESS;
      }
    }

    g_free(property);
  }
  return result;
}
