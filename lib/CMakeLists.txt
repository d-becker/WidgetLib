cmake_minimum_required (VERSION 3.2)

include_directories(include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

add_library(FlugiLib STATIC src/graphics.cpp)
