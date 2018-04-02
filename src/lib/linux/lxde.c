// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include <glib.h>

#include "common.h"

static const char* DESKTOP = "LXDE";
static const char* PCMANFM_PATH = "/usr/bin/pcmanfm";

gboolean is_lxde(const gchar* desktop) {
  return g_strcmp0(desktop, DESKTOP) == 0 && file_exists(PCMANFM_PATH);
}

static inline gchar* pcmanfm_config_dir() {
  return g_build_filename(g_get_user_config_dir(), "pcmanfm", "*", "desktop-items-*.conf", NULL);
}

static const char* CONF_GROUP = "*";
static const char* CONF_KEY_IMAGE = "wallpaper";
static const char* CONF_KEY_STYLE = "wallpaper_mode";

static const char* CONF_VALUE_STYLE_CENTER = "center";
static const char* CONF_VALUE_STYLE_STRETCH = "stretch";
static const char* CONF_VALUE_STYLE_TILE = "tile";

static const gchar* value_for_style(int style) {
  switch (style) {
    case STYLE_CENTER:
      return CONF_VALUE_STYLE_CENTER;
    case STYLE_STRETCH:
      return CONF_VALUE_STYLE_STRETCH;
    case STYLE_TILE:
      return CONF_VALUE_STYLE_TILE;
    default:
      return NULL;
  }
}

static gboolean set_background_config(const gchar* config, const gchar* path, const gchar* style) {
  GKeyFile* key_file = g_key_file_new();
  if (!g_key_file_load_from_file(key_file, config, G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS, NULL)) {
    return FALSE;
  }
  g_key_file_set_string(key_file, CONF_GROUP, CONF_KEY_IMAGE, path);
  g_key_file_set_string(key_file, CONF_GROUP, CONF_KEY_STYLE, style);
  gboolean result = g_key_file_save_to_file(key_file, config, NULL);
  g_key_file_free(key_file);
  return result;
}

int set_background_lxde(const gchar* path, int style) {
  const gchar* style_value = value_for_style(style);
  if (!style_value) {
    return E_UNSUPPORTED_STYLE;
  }

  __pid_t pcmanfm_pid = find_pid_for_exe_path(PCMANFM_PATH);
  if (!pcmanfm_pid) {
    return E_LXDE_PCMANFM_NOT_RUNNING;
  }

  // Force pcmanfm to create config files, if they don't exist.
  kill(pcmanfm_pid, SIGUSR1);

  gchar* dir = pcmanfm_config_dir();
  gchar** files = glob_path(dir);
  g_free(dir);
  
  if (files == NULL) {
    return E_LXDE_FAIL;
  }

  gboolean success = TRUE;
  for (gchar** file = files; *file != NULL; file++) {
    success &= set_background_config(*file, path, style_value);
    g_free(*file);
  }
  g_free(files);

  // Force pcmanfm to reload config files.
  kill(pcmanfm_pid, SIGUSR1);

  if (!success) {
    return E_LXDE_FAIL;
  }
  return E_SUCCESS;
}
