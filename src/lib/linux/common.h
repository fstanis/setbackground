// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#ifndef __SETBACKGROUND_LINUX_COMMON_H__
#define __SETBACKGROUND_LINUX_COMMON_H__

#include <dbus/dbus.h>
#include <glib.h>

#include "errors.h"
#include "styles.h"

gboolean dconf_write(const gchar* key, const gchar* value);
gboolean dbus_session_send_message(DBusMessage* msg, DBusError* err);

gchar* to_file_uri_path(const gchar* path);
gchar* get_desktop_environment();
gboolean file_exists(const gchar* path);
gchar* get_real_path(const gchar* path);
__pid_t find_pid_for_exe_path(const gchar* path);
gchar** glob_path(const gchar* path);
int gnome_set_style(const gchar* key, int style);

#endif /* __SETBACKGROUND_LINUX_COMMON_H__ */
