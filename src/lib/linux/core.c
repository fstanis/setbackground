#include "core.h"

#include <glib.h>

#include "common.h"
#include "platforms.h"

const char* DESKTOP_XFCE = "XFCE";

int set_background_linux(const char* path) {
  if (!file_exists(path)) {
    return E_INVALID_PATH;
  }
  gchar* real_path = get_real_path(path);
  if (!real_path) {
    return E_INVALID_PATH;
  }

  gchar* desktop_env = get_desktop_environment();
  int result = E_UNSUPPORTED_DESKTOP_ENVIRONMENT;
  if (g_strcmp0(desktop_env, DESKTOP_XFCE) == 0) {
    result = set_background_xfce(real_path);
  }
  g_free(desktop_env);
  g_free(real_path);  
  return result;
}
