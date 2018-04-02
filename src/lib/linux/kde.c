// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include <glib.h>
#include <string.h>

#include "common.h"

static const char* DESKTOP = "KDE";

gboolean is_kde(const gchar* desktop) {
  return g_strcmp0(desktop, DESKTOP) == 0;
}

static const char* SCRIPT_BASE =
    "desktops().forEach(function(d) {"
    "d.wallpaperPlugin = 'org.kde.image';"
    "d.currentConfigGroup = ['Wallpaper', 'org.kde.image', 'General'];"
    "d.writeConfig('Image', '%s');"
    "d.writeConfig('FillMode', '%d');"
    "});";

static const char* PLASMASHELL_BUS = "org.kde.plasmashell";
static const char* PLASMASHELL_PATH = "/PlasmaShell";
static const char* PLASMASHELL_IFACE = "org.kde.PlasmaShell";
static const char* PLASMASHELL_METHOD = "evaluateScript";

static const int STYLE_VALUE_CENTER = 6;
static const int STYLE_VALUE_STRETCH = 0;
static const int STYLE_VALUE_TILE = 3;

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

static DBusMessage* create_message(gchar** script) {
  DBusMessage* msg = dbus_message_new_method_call(
      PLASMASHELL_BUS, PLASMASHELL_PATH, PLASMASHELL_IFACE, PLASMASHELL_METHOD);
  if (!msg) {
    return NULL;
  }

  if (dbus_message_append_args(msg, DBUS_TYPE_STRING, script,
                               DBUS_TYPE_INVALID)) {
    return msg;
  }
  return NULL;
}

static gchar* create_script(const gchar* path, int style) {
  if (strchr(path, '\'') != NULL) {
    return NULL;
  }
  gchar* file_path = to_file_uri_path(path);
  gchar* script = g_strdup_printf(SCRIPT_BASE, file_path, style);
  g_free(file_path);
  return script;
}

static int handle_error(DBusError* error) {
  int result = E_KDE_FAIL;
  if (dbus_error_has_name(error, DBUS_ERROR_SERVICE_UNKNOWN)) {
    result = E_KDE_NO_PLASMASHELL;
  } else if (dbus_error_has_name(error, DBUS_ERROR_UNKNOWN_METHOD)) {
    result = E_KDE_UNSUPPORTED_VERSION;
  }
  dbus_error_free(error);
  return result;
}

int set_background_kde(const gchar* path, int style) {
  int style_value = value_for_style(style);
  if (style_value == -1) {
    return E_UNSUPPORTED_STYLE;
  }

  int result = E_KDE_FAIL;

  DBusError error;
  dbus_error_init(&error);

  gchar* script = create_script(path, style_value);
  if (!script) {
    return E_INVALID_PATH;
  }
  DBusMessage* msg = create_message(&script);
  if (msg) {
    if (dbus_session_send_message(msg, &error)) {
      result = E_SUCCESS;
    }
    dbus_message_unref(msg);
  }

  if (dbus_error_is_set(&error)) {
    result = handle_error(&error);
  }
  return result;
}
