// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

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

static const int STYLE_VALUE_CENTER = 1;
static const int STYLE_VALUE_TILE = 2;
static const int STYLE_VALUE_STRETCH = 3;

static int value_for_style(int style) {
  switch (style) {
    case STYLE_CENTER:
      return STYLE_VALUE_CENTER;
    case STYLE_STRETCH:
      return STYLE_VALUE_STRETCH;
    case STYLE_TILE:
      return STYLE_VALUE_TILE;
    default:
      return -1;
  }
}

static gboolean set_style_for_monitor(XfconfChannel* chan, int monitor, int style) {
  gboolean result = TRUE;
  gchar* style_property = g_strdup_printf(PROPERTY_STYLE, monitor);
  if (!xfconf_channel_set_int(chan, style_property, style)) {
    result = FALSE;
  }
  g_free(style_property);
  return result;
}

int set_background_xfce(const gchar* path, int style) {
  int style_value = value_for_style(style);
  if (style_value == -1) {
    return E_UNSUPPORTED_STYLE;
  }

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

      if (!set_style_for_monitor(chan, monitor, style_value)) {
        result = E_XFCE_FAIL;
      }
    }
    g_free(image_property);
  }
  return result;
}
