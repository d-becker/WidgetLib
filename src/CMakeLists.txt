cmake_minimum_required (VERSION 2.8)

set(SRC_FILES
	main.cpp
	Button.cpp
	Container.cpp
	Widget.cpp	
)

add_executable(WidgetLib ${SRC_FILES})
target_link_libraries(WidgetLib libgraphics.a)
