#include <glib.h>

#include "common.h"
#include "xfconfdl.h"

static const char* DESKTOP = "XFCE";

gboolean is_xfce(const gchar* desktop) {
  return g_strcmp0(desktop, DESKTOP) == 0;
}

static const char* DESKTOP_CHANNEL = "xfce4-desktop";
static const char* PROPERTY_BASE = "/backdrop/screen0/monitor%d/workspace0/last-image";

int set_background_xfce(const gchar* path) {
  if (!xfconf_try_init()) {
    return E_XFCE_FAIL;
  }
  XfconfChannel* chan = xfconf_channel_get(DESKTOP_CHANNEL);
  if (!chan) {
    return E_XFCE_FAIL;
  }

  int result = E_SUCCESS;
  gboolean monitor_exists = TRUE;
  for (int monitor = 0; monitor_exists; monitor++) {
    gchar* property = g_strdup_printf(PROPERTY_BASE, monitor);

    monitor_exists = xfconf_channel_has_property(chan, property);
    if (monitor_exists) {
      if (!xfconf_channel_set_string(chan, property, path)) {
        result = E_XFCE_FAIL;
      }
    }

    g_free(property);
  }
  return result;
}
