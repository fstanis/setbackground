// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#ifndef __SETBACKGROUND_WINDOWS_COM_H__
#define __SETBACKGROUND_WINDOWS_COM_H__

#include <windows.h>

BOOL com_set_wallpaper(const WCHAR* path, int style);

#endif /* __SETBACKGROUND_WINDOWS_COM_H__ */
