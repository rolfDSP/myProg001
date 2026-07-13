cmake_minimum_required(VERSION 3.10)
project(SVG_Example CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Place the built executable in the project's exe/ subfolder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/exe)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3  REQUIRED gtk+-3.0)
pkg_check_modules(RSVG  REQUIRED librsvg-2.0)

add_executable(svg_example main.cpp)

target_include_directories(svg_example PRIVATE
    ${GTK3_INCLUDE_DIRS}
    ${RSVG_INCLUDE_DIRS}
)

target_compile_options(svg_example PRIVATE
    ${GTK3_CFLAGS_OTHER}
    ${RSVG_CFLAGS_OTHER}
)

target_link_directories(svg_example PRIVATE
    ${GTK3_LIBRARY_DIRS}
    ${RSVG_LIBRARY_DIRS}
)

target_link_libraries(svg_example PRIVATE
    ${GTK3_LIBRARIES}
    ${RSVG_LIBRARIES}
)