// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include "legacy.h"

static const WCHAR* REGISTRY_KEY_PATH = L"Control Panel\\Desktop";
static const WCHAR* REGISTRY_VALUE_TILE = L"TileWallpaper";
static const WCHAR* REGISTRY_VALUE_STYLE = L"WallpaperStyle";
static const WCHAR TILE_DISABLED[] = L"0";
static const WCHAR STYLE_CENTER[] = L"0";

static inline BOOL open_key(HKEY* key) {
  return RegOpenKeyExW(HKEY_CURRENT_USER, REGISTRY_KEY_PATH, 0,
                       KEY_READ | KEY_SET_VALUE, key) == ERROR_SUCCESS;
}

// The wallpaper style is stored in the registry.
BOOL update_registry() {
  HKEY key;
  if (open_key(&key)) {
    RegSetValueEx(key, REGISTRY_VALUE_TILE, 0, REG_SZ,
                  (const BYTE*)TILE_DISABLED, sizeof(TILE_DISABLED));
    RegSetValueEx(key, REGISTRY_VALUE_STYLE, 0, REG_SZ,
                  (const BYTE*)STYLE_CENTER, sizeof(STYLE_CENTER));
    RegCloseKey(key);
    return TRUE;
  }
  return FALSE;
}

// Change the wallpaper by setting a system-wide SPI_SETDESKWALLPAPER parameter.
// Prior to Windows 8, this was the only way to modify the background image.
BOOL legacy_set_wallpaper(const WCHAR* path) {
  if (!update_registry()) {
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
