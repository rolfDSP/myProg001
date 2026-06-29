cmake_minimum_required(VERSION 4.2)
project(myProg001)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/exe)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_executable(myProg001
    main.cpp
    TMainWindow/TMainWindow.cpp
    TStatusBar/TStatusBar.cpp
)

target_include_directories(myProg001 PRIVATE ${GTK3_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})
target_link_libraries(myProg001 PRIVATE ${GTK3_LIBRARIES})
target_compile_options(myProg001 PRIVATE ${GTK3_CFLAGS_OTHER})
