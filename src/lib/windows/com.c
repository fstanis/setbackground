// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#include <initguid.h>
#include <shobjidl.h>

#include "com.h"

static const DWORD STYLE_CENTER = DWPOS_CENTER;

static inline BOOL load_interface(IDesktopWallpaper** iface) {
  return !FAILED(CoCreateInstance(&CLSID_DesktopWallpaper, NULL, CLSCTX_ALL,
                                  &IID_IDesktopWallpaper, (LPVOID*)iface));
}

// This COM interface is only supported in Windows 8 and above.
BOOL com_set_wallpaper(const WCHAR* path) {
  BOOL result = FALSE;
  CoInitialize(NULL);
  IDesktopWallpaper* pDesktopWallpaper = NULL;
  if (load_interface(&pDesktopWallpaper)) {
    HRESULT res;
    res = IDesktopWallpaper_SetPosition(pDesktopWallpaper, STYLE_CENTER);
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
