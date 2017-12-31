set(SRCS
  "main.c"
)

include_directories(
  "${PROJECT_SOURCE_DIR}/src/lib"
)

link_libraries(
  "setbackground"
)

add_executable(cli "${SRCS}")

set_target_properties(cli PROPERTIES OUTPUT_NAME setbackground)
