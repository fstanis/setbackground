#include "xfconfdl.h"

#include <dlfcn.h>

static const char* LIBXFCONF = "libxfconf-0.so";

gboolean (*xfconf_init)(GError **error) = NULL;
XfconfChannel* (*xfconf_channel_get)(const gchar *channel_name) = NULL;
gboolean (*xfconf_channel_has_property)(XfconfChannel *channel, const gchar *property) = NULL;
gboolean (*xfconf_channel_set_string)(XfconfChannel *channel, const gchar *property, const gchar *value) = NULL;

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