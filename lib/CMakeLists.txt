cmake_minimum_required (VERSION 3.2)

include_directories(include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

add_library(FlugiLib STATIC src/graphics.cpp)

# Making code position independent to be able to use it in shared libraries.
set_target_properties(FlugiLib PROPERTIES 
	COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -fPIC"
)
