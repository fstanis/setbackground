// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

#ifndef __SETBACKGROUND_LINUX_PLATFORMS_H__
#define __SETBACKGROUND_LINUX_PLATFORMS_H__

int set_background_xfce(const gchar* path);
gboolean is_xfce(const gchar* desktop);

int set_background_kde(const gchar* path);
gboolean is_kde(const gchar* desktop);

int set_background_gnome(const gchar* path);
gboolean is_gnome(const gchar* desktop);

int set_background_cinnamon(const gchar* path);
gboolean is_cinnamon(const gchar* desktop);

int set_background_mate(const gchar* path);
gboolean is_mate(const gchar* desktop);

int set_background_deepin(const gchar* path);
gboolean is_deepin(const gchar* desktop);

int set_background_lxde(const gchar* path);
gboolean is_lxde(const gchar* desktop);

#endif /* __SETBACKGROUND_LINUX_PLATFORMS_H__ */
