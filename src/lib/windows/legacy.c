// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include "legacy.h"
#include "styles.h"

static const WCHAR* REGISTRY_KEY_PATH = L"Control Panel\\Desktop";
static const WCHAR* REGISTRY_VALUE_TILE = L"TileWallpaper";
static const WCHAR* REGISTRY_VALUE_STYLE = L"WallpaperStyle";

static const WCHAR TILE_ENABLED[] = L"1";
static const WCHAR TILE_DISABLED[] = L"0";
static const WCHAR STYLE_VALUE_CENTER[] = L"0";
static const WCHAR STYLE_VALUE_STRETCH[] = L"2";

static inline BOOL open_key(HKEY* key) {
  return RegOpenKeyExW(HKEY_CURRENT_USER, REGISTRY_KEY_PATH, 0,
                       KEY_READ | KEY_SET_VALUE, key) == ERROR_SUCCESS;
}

// The wallpaper style is stored in the registry.
static BOOL update_registry(int style) {
  HKEY key;
  if (open_key(&key)) {
    if (style == STYLE_TILE) {
      RegSetValueEx(key, REGISTRY_VALUE_TILE, 0, REG_SZ,
                    (const BYTE*)TILE_ENABLED, sizeof(TILE_ENABLED));
      RegSetValueEx(key, REGISTRY_VALUE_STYLE, 0, REG_SZ,
                    (const BYTE*)STYLE_VALUE_CENTER,
                    sizeof(STYLE_VALUE_CENTER));
    } else {
      RegSetValueEx(key, REGISTRY_VALUE_TILE, 0, REG_SZ,
                    (const BYTE*)TILE_DISABLED, sizeof(TILE_DISABLED));
      if (style == STYLE_CENTER) {
        RegSetValueEx(key, REGISTRY_VALUE_STYLE, 0, REG_SZ,
                      (const BYTE*)STYLE_VALUE_CENTER,
                      sizeof(STYLE_VALUE_CENTER));
      } else if (style == STYLE_STRETCH) {
        RegSetValueEx(key, REGISTRY_VALUE_STYLE, 0, REG_SZ,
                      (const BYTE*)STYLE_VALUE_STRETCH,
                      sizeof(STYLE_VALUE_STRETCH));
      }
    }
    RegCloseKey(key);
    return TRUE;
  }
  return FALSE;
}

// Change the wallpaper by setting a system-wide SPI_SETDESKWALLPAPER parameter.
// Prior to Windows 8, this was the only way to modify the background image.
BOOL legacy_set_wallpaper(const WCHAR* path, int style) {
  if (!update_registry(style)) {
    return FALSE;
  }
  BOOL result = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID)path,
                                     SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
  if (result) {
    // Force refresh, just in case.
    SendMessage(GetDesktopWindow(), WM_SETTINGCHANGE, 0, 0);
  }
  return result;
}
