#include <windows.h>

#include "com.h"
#include "core.h"
#include "errors.h"
#include "legacy.h"
#include "util.h"

int set_background_windows(const char* path) {
  WCHAR pathW[MAX_PATH];
  if (!parse_path(path, pathW, MAX_PATH)) {
    return E_INVALID_PATH;
  }

  // Windows XP only supports BMP images.
  if (is_winxp() && !is_bmp(pathW)) {
    return E_INVALID_FORMAT;
  }

  // We try the newer COM-based method first, then revert to legacy if it fails.
  if (com_set_wallpaper(pathW)) {
    return E_SUCCESS;
  }

  if (legacy_set_wallpaper(pathW)) {
    return E_SUCCESS;
  }
  return E_FAIL;
}
