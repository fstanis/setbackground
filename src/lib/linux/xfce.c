#include <glib.h>

#include "common.h"
#include "xfconfdl.h"

static const char* DESKTOP = "XFCE";

gboolean is_xfce(const gchar* desktop) {
  return g_strcmp0(desktop, DESKTOP) == 0;
}

static const char* DESKTOP_CHANNEL = "xfce4-desktop";
static const char* PROPERTY_IMAGE = "/backdrop/screen0/monitor%d/workspace0/last-image";
static const char* PROPERTY_STYLE = "/backdrop/screen0/monitor%d/workspace0/image-style";
static const int STYLE_CENTER = 1;

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
  for (int monitor = 0; monitor_exists && result == E_SUCCESS; monitor++) {
    gchar* image_property = g_strdup_printf(PROPERTY_IMAGE, monitor);
    monitor_exists = xfconf_channel_has_property(chan, image_property);
    if (monitor_exists) {
      if (!xfconf_channel_set_string(chan, image_property, path)) {
        result = E_XFCE_FAIL;
      }

      gchar* style_property = g_strdup_printf(PROPERTY_STYLE, monitor);
      if (!xfconf_channel_set_int(chan, style_property, STYLE_CENTER)) {
        result = E_XFCE_FAIL;
      }
      g_free(style_property);
    }
    g_free(image_property);
  }
  return result;
}
