cmake_minimum_required (VERSION 2.8)

project(WidgetLib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -g -Wall")

include_directories(include)
include_directories(include/evt)
include_directories(lib/include)

find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)

add_subdirectory(lib)
add_subdirectory(src)

# Copying the fonts
file(COPY "${PROJECT_SOURCE_DIR}/SDL_Fonts" DESTINATION ${PROJECT_SOURCE_DIR}/bin/)

# Installing files
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp)
set(HEADERS ${HEADERS} "${PROJECT_SOURCE_DIR}/lib/include/graphics.hpp")

install(FILES ${HEADERS} DESTINATION include/WidgetLib)

file(GLOB FONTS ${PROJECT_SOURCE_DIR}SDL_Fonts/*.ttf)
install(FILES ${FONTS} DESTINATION share/WidgetLib/SDL_Fonts)

# Packaging
include (InstallRequiredSystemLibraries)

include (CPack)
