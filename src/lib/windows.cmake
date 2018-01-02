set(SRCS
  "windows/com.c"
  "windows/core.c"
  "windows/legacy.c"
  "windows/util.c"
)

add_definitions(
  "-D_WIN32_WINNT=0x10020000"
  "-DCINTERFACE"
  "-DCOBJMACROS"
  "-DUNICODE"
  "-D_UNICODE"
)

link_libraries(
  "-lole32"
  "-loleaut32"
  "-lshlwapi"
)
