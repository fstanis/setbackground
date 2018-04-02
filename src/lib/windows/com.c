// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include <initguid.h>
#include <shobjidl.h>

#include "com.h"
#include "styles.h"

static DWORD value_for_style(int style) {
  switch (style) {
    case STYLE_CENTER:
      return DWPOS_CENTER;
    case STYLE_STRETCH:
      return DWPOS_STRETCH;
    case STYLE_TILE:
      return DWPOS_TILE;
  }
  return -1;
}

static inline BOOL load_interface(IDesktopWallpaper** iface) {
  return !FAILED(CoCreateInstance(&CLSID_DesktopWallpaper, NULL, CLSCTX_ALL,
                                  &IID_IDesktopWallpaper, (LPVOID*)iface));
}

// This COM interface is only supported in Windows 8 and above.
BOOL com_set_wallpaper(const WCHAR* path, int style) {
  DWORD style_value = value_for_style(style);

  BOOL result = FALSE;
  CoInitialize(NULL);
  IDesktopWallpaper* pDesktopWallpaper = NULL;
  if (load_interface(&pDesktopWallpaper)) {
    HRESULT res;
    res = IDesktopWallpaper_SetPosition(pDesktopWallpaper, style_value);
    if (!FAILED(res)) {
      res = IDesktopWallpaper_SetWallpaper(pDesktopWallpaper, NULL, path);
      if (!FAILED(res)) {
        result = TRUE;
      }
    }
  }
  CoUninitialize();
  return result;
}
