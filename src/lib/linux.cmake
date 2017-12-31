find_package(PkgConfig)

pkg_check_modules(GLIB2 glib-2.0)
pkg_check_modules(DCONF dconf)
pkg_check_modules(DBUS dbus-1)

set(SRCS
  "linux/cinnamon.c"
  "linux/common.c"
  "linux/core.c"
  "linux/deepin.c"
  "linux/gnome.c"
  "linux/kde.c"
  "linux/lxde.c"
  "linux/mate.c"
  "linux/xfce.c"
  "linux/xfconfdl.c"
)

add_definitions(
  "-D_GNU_SOURCE"
)

link_libraries(
  "${GLIB2_LIBRARIES}"
  "${DCONF_LIBRARIES}"
  "${DBUS_LIBRARIES}"
  "${CMAKE_DL_LIBS}"
)

include_directories(
  "${GLIB2_INCLUDE_DIRS}"
  "${DCONF_INCLUDE_DIRS}"
  "${DBUS_INCLUDE_DIRS}"
)
