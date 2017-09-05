#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([setbackground], [0.1])
AC_CONFIG_SRCDIR([src/lib/setbackground.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_RANLIB
AM_PROG_AR

# Use the C language and compiler for the following checks
AC_LANG([C])

# Checks for libraries.
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([GLIB], [glib-2.0])
PKG_CHECK_MODULES([XFCONF], [libxfconf-0])
PKG_CHECK_MODULES([DCONF], [dconf])
PKG_CHECK_MODULES([DBUS], [dbus-1])
AC_CHECK_LIB([dl], [dlsym], [DL_LIBS=-ldl])
AC_SUBST(DL_LIBS)

# Checks for header files.
AC_HEADER_STDC

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([
  Makefile
  src/lib/Makefile
  src/cli/Makefile
])

AC_OUTPUT
