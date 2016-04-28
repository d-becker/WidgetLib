cmake_minimum_required (VERSION 3.2)

project(WidgetLib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -g -Wall")

include_directories(include)
include_directories(include/evt)
include_directories(lib/include)

find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)

link_directories(lib)

add_subdirectory(src)
