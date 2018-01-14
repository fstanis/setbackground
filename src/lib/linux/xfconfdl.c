// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include "xfconfdl.h"

#include <dlfcn.h>

static const char* LIBXFCONF = "libxfconf-0.so.2";

gboolean (*xfconf_init)(GError **error) = NULL;
XfconfChannel* (*xfconf_channel_get)(const gchar *channel_name) = NULL;
gboolean (*xfconf_channel_has_property)(XfconfChannel *channel, const gchar *property) = NULL;
gboolean (*xfconf_channel_set_string)(XfconfChannel *channel, const gchar *property, const gchar *value) = NULL;
gboolean (*xfconf_channel_set_int)(XfconfChannel *channel, const gchar *property, gint32 value) = NULL;

// We load xfconf dynamically, to avoid having it a dependency on systems not
// running XFCE.
gboolean libxfconf_try_load() {
  static void* libxfconf = NULL;
  if (libxfconf) {
    return TRUE;
  }

  libxfconf = dlopen(LIBXFCONF, RTLD_NOW | RTLD_LOCAL);
  if (!libxfconf) {
    return FALSE;
  }
  xfconf_init = dlsym(libxfconf, "xfconf_init");
  xfconf_channel_has_property = dlsym(libxfconf, "xfconf_channel_has_property");
  xfconf_channel_get = dlsym(libxfconf, "xfconf_channel_get");
  xfconf_channel_set_string = dlsym(libxfconf, "xfconf_channel_set_string");
  xfconf_channel_set_int = dlsym(libxfconf, "xfconf_channel_set_int");
  return TRUE;
}

gboolean xfconf_try_init() {
  static gboolean has_init = FALSE;
  if (has_init) {
    return TRUE;
  }

  if (!libxfconf_try_load()) {
    return FALSE;
  }
  if (xfconf_init(NULL)) {
    has_init = TRUE;
    return TRUE;
  }
  return FALSE;
}
