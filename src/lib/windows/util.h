// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#ifndef __SETBACKGROUND_WINDOWS_UTIL_H__
#define __SETBACKGROUND_WINDOWS_UTIL_H__

#include <windows.h>

BOOL file_exists(const WCHAR* path);
BOOL is_bmp(const WCHAR* path);
BOOL utf8_to_wstr(const char* in, WCHAR* out, int out_len);
BOOL parse_path(const char* path, WCHAR* out, int out_len);
BOOL is_winxp();

#endif /* __SETBACKGROUND_WINDOWS_UTIL_H__ */
