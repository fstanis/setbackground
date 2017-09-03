#AM_CPPFLAGS = -I$(top_srcdir)/src/lib/linux
AM_CFLAGS = -Wall -Wextra
AM_CFLAGS += @GLIB_CFLAGS@ @DCONF_CFLAGS@ @DBUS_CFLAGS@ @XFCONF_CFLAGS@

lib_LIBRARIES = libsetbackground.a

include_HEADERS = setbackground.h

libsetbackground_a_SOURCES = setbackground.c errors.h
libsetbackground_a_SOURCES += linux/core.c linux/common.c linux/core.h linux/common.h
libsetbackground_a_SOURCES += linux/kde.c linux/xfce.c linux/platforms.h
