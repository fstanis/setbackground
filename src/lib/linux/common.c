#include "common.h"

#include <stdlib.h>

#include <dbus/dbus.h>
#include <dconf.h>
#include <glib.h>

#include "xfconfdl.h"

gboolean dconf_write(const gchar* key, const gchar* value) {
  DConfClient* client = dconf_client_new();
  GVariant* variant = g_variant_new_string(value);
  gboolean result =
      dconf_client_write_sync(client, key, variant, NULL, NULL, NULL);
  g_object_unref(client);
  return result;
}

gboolean dbus_session_send_message(DBusMessage* msg, DBusError* err) {
  DBusConnection* conn = dbus_bus_get(DBUS_BUS_SESSION, err);
  if (conn) {
    gboolean result = FALSE;
    DBusMessage* reply =
        dbus_connection_send_with_reply_and_block(conn, msg, -1, err);
    if (reply) {
      result = TRUE;
      dbus_message_unref(reply);
    }
    dbus_connection_flush(conn);
    return result;
  }
  return FALSE;
}

gchar* to_file_uri_path(const gchar* path) {
  static const gchar* base = "file://%s";
  return g_strdup_printf(base, path);
}

gchar* get_desktop_environment() {
  const char* result = getenv("XDG_CURRENT_DESKTOP");
  return g_strdup(result);
}

gboolean file_exists(const gchar* path) {
  if (access(path, F_OK) != 0) {
    return FALSE;
  }
  return TRUE;
}

gchar* get_real_path(const gchar* path) {
  static char pathTemp[PATH_MAX];
  if (realpath(path, pathTemp) != pathTemp) {
    return NULL;
  }
  return g_strdup(pathTemp);
}
