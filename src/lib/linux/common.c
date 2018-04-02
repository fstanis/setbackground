// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include "common.h"

#include <stdlib.h>

#include <dbus/dbus.h>
#include <dconf.h>
#include <glib.h>
#include <glob.h>

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

__pid_t find_pid_for_exe_path(const gchar* path) {
  GDir* proc = g_dir_open("/proc", 0, NULL);
  if (!proc) {
    return 0;
  }

  __pid_t result = 0;
  const gchar* filename;

  while ((filename = g_dir_read_name(proc)) && result == 0) {
    int pid = atoi(filename);
    if (pid > 0) {
      gchar* proc_exe = g_strdup_printf("/proc/%d/exe", pid);
      gchar* exe_path = get_real_path(proc_exe);
      g_free(proc_exe);
      if (g_strcmp0(exe_path, path) == 0) {
        result = pid;
      }
      g_free(exe_path);
    }
  }

  g_dir_close(proc);

  return result;
}

#define MAX_GLOB_RESULTS 50

gchar** glob_path(const gchar* path) {
  static gchar* files[MAX_GLOB_RESULTS];

  glob_t results;
  if (glob(path, GLOB_NOSORT, NULL, &results) != 0) {
    return NULL;
  }
  gchar** result = NULL;
  if (results.gl_pathc < MAX_GLOB_RESULTS) {
    for (gsize i = 0; i < results.gl_pathc; i++) {
      files[i] = results.gl_pathv[i];
    }
    files[results.gl_pathc] = NULL;
    result = g_strdupv(files);
  }
  globfree(&results);

  return result;
}

static const char* DCONF_VALUE_STYLE_CENTER = "centered";
static const char* DCONF_VALUE_STYLE_STRETCH = "stretched";
static const char* DCONF_VALUE_STYLE_TILE = "wallpaper";

int gnome_set_style(const gchar* key, int style) {
  const gchar* value = NULL;
  switch (style) {
    case STYLE_CENTER:
      value = DCONF_VALUE_STYLE_CENTER;
      break;
    case STYLE_STRETCH:
      value = DCONF_VALUE_STYLE_STRETCH;
      break;
    case STYLE_TILE:
      value = DCONF_VALUE_STYLE_TILE;
      break;
    default:
      return E_UNSUPPORTED_STYLE;
  }

  if (!dconf_write(key, value)) {
    return E_STYLE_FAIL;
  }

  return E_SUCCESS;
}
