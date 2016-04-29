cmake_minimum_required (VERSION 3.2)

include_directories(include)

set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_library(FlugiLib src/graphics.cpp)
