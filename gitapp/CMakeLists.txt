cmake_minimum_required (VERSION 2.6)
project (gitapp)

set (gitapp_VERSION_MAJOR 1)
set (gitapp_VERSION_MINOR 0)
configure_file (
   "${PROJECT_SOURCE_DIR}/gitappconfig.h.in"
   "${PROJECT_BINARY_DIR}/gitappconfig.h"
)
include_directories("${PROJECT_BINARY_DIR}")
include_directories("/usr/local/include")
link_directories("/usr/local/lib")


set(EXTRA_LIBS git2)
add_executable(gitapp gitapp.cpp)
target_link_libraries(gitapp ${EXTRA_LIBS})
