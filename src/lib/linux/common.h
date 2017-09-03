#ifndef __SETBACKGROUND_COMMON_H__
#define __SETBACKGROUND_COMMON_H__

#include <dbus/dbus.h>
#include <glib.h>

#include "errors.h"

gboolean dconf_write_property(const gchar* property, const gchar* value);
gboolean dbus_session_send_message(DBusMessage* msg, DBusError* err);
gboolean xfconf_has_property(const gchar* channel, const gchar* property);
gboolean xfconf_write_property(const gchar* channel, const gchar* property,
                               const gchar* value);

gchar* to_file_uri_path(const gchar* path);
gchar* get_desktop_environment();
gboolean file_exists(const gchar* path);
gchar* get_real_path(const gchar* path);

#endif /* __SETBACKGROUND_COMMON_H__ */
