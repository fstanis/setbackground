// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#ifndef __SETBACKGROUND_ERROR_H__
#define __SETBACKGROUND_ERROR_H__

enum _error {
    E_SUCCESS = 0,
    E_INVALID_PATH = 1,
    E_UNSUPPORTED_DESKTOP_ENVIRONMENT = 2,
    E_KDE_NO_PLASMASHELL = 3,
    E_KDE_UNSUPPORTED_VERSION = 4,
    E_KDE_FAIL = 5,
    E_XFCE_FAIL = 6,
    E_MATE_FAIL = 7,
    E_CINNAMON_FAIL = 8,
    E_DEEPIN_FAIL = 9,
    E_GNOME_FAIL = 10,
    E_LXDE_PCMANFM_NOT_RUNNING = 11,
    E_LXDE_FAIL = 12,
    E_INVALID_FORMAT = 13,
    E_UNSUPPORTED_STYLE = 14,
    E_STYLE_FAIL = 15
  };

#endif /* __SETBACKGROUND_ERROR_H__ */
