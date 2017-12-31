if (UNIX AND NOT APPLE)
  include("linux.cmake")
endif ()
if (WIN32)
  include("windows.cmake")
endif ()
if (APPLE)
  include("darwin.cmake")
endif ()

include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_library(setbackground STATIC "setbackground.c" ${SRCS})
