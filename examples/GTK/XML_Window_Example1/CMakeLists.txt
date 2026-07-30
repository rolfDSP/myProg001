cmake_minimum_required(VERSION 3.10)
project(XML_Window_Example1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/exe)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_executable(XML_Window_Example1
    main.cpp
)

target_include_directories(XML_Window_Example1 PRIVATE
    ${GTK3_INCLUDE_DIRS}
)

target_link_libraries(XML_Window_Example1 PRIVATE ${GTK3_LIBRARIES})
target_compile_options(XML_Window_Example1 PRIVATE ${GTK3_CFLAGS_OTHER})

# Required so GTK can resolve signal handler names at runtime (gtk_builder_connect_signals)
target_link_options(XML_Window_Example1 PRIVATE -rdynamic)