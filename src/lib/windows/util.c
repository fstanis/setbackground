#include <shlwapi.h>
#include <stdlib.h>

#include "util.h"

BOOL file_exists(const WCHAR* path) {
  DWORD attributes = GetFileAttributes(path);
  return (attributes != INVALID_FILE_ATTRIBUTES &&
          !(attributes & FILE_ATTRIBUTE_DIRECTORY));
}

BOOL is_bmp(const WCHAR* path) {
  WCHAR* ext = PathFindExtension(path);
  return (lstrcmpi(ext, L".bmp") == 0);
}

BOOL utf8_to_wstr(const char* in, WCHAR* out, int out_len) {
  return MultiByteToWideChar(CP_UTF8, 0, in, -1, out, out_len);
}

BOOL parse_path(const char* path, WCHAR* out, int out_len) {
  WCHAR pathW[MAX_PATH];
  if (!utf8_to_wstr(path, pathW, MAX_PATH)) {
    return FALSE;
  }
  if (!file_exists(pathW)) {
    return FALSE;
  }
  return _wfullpath(out, pathW, out_len) != NULL;
}

BOOL is_winxp() {
  OSVERSIONINFO vi;
  vi.dwOSVersionInfoSize = sizeof(vi);
  GetVersionEx(&vi);
  return vi.dwMajorVersion <= 5;
}
