cmake_minimum_required (VERSION 2.8.1)

project(WidgetLib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -g -Wall -lSDL -lSDL_ttf")

include_directories(include)
include_directories(lib/include)

link_directories(lib)

add_subdirectory(src)
