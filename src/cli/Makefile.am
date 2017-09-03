AM_CPPFLAGS = -I$(top_srcdir)/src/lib
AM_CFLAGS = -Wall -Wextra

bin_PROGRAMS = setbackground

setbackground_SOURCES = main.c

setbackground_LDADD = $(top_builddir)/src/lib/libsetbackground.a
setbackground_LDADD += @GLIB_LIBS@ @DCONF_LIBS@ @DBUS_LIBS@ @XFCONF_LIBS@
