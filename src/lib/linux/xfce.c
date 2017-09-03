#include <glib.h>

#include "common.h"

const char* DESKTOP_CHANNEL = "xfce4-desktop";
const char* PROPERTY_BASE = "/backdrop/screen0/monitor%d/workspace0/last-image";

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
