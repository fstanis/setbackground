// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include <windows.h>

#include "com.h"
#include "core.h"
#include "styles.h"
#include "errors.h"
#include "legacy.h"
#include "util.h"

static BOOL is_style_valid(int style) {
  return style == STYLE_CENTER || style == STYLE_STRETCH || style == STYLE_TILE;
}

int set_background_windows(const char* path, int style) {
  if (!is_style_valid(style)) {
    return E_UNSUPPORTED_STYLE;
  }

  WCHAR pathW[MAX_PATH];
  if (!parse_path(path, pathW, MAX_PATH)) {
    return E_INVALID_PATH;
  }

  // Windows XP only supports BMP images.
  if (is_winxp() && !is_bmp(pathW)) {
    return E_INVALID_FORMAT;
  }

  // We try the newer COM-based method first, then revert to legacy if it fails.
  if (com_set_wallpaper(pathW, style)) {
    return E_SUCCESS;
  }

  if (legacy_set_wallpaper(pathW, style)) {
    return E_SUCCESS;
  }
  return E_FAIL;
}
