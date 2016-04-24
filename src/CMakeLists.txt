cmake_minimum_required (VERSION 2.8)

set(SRC_FILES
	main.cpp
	Button.cpp
	Container.cpp
	FreePanel.cpp
	Label.cpp
	TextBox.cpp
	TextDisplay.cpp
	Toplevel.cpp
	Widget.cpp	
)

set(LIBS 
	libgraphics.a
	${SDL_LIBRARY}
	${SDL_TTF_LIBRARY}
)

add_executable(WidgetLib ${SRC_FILES})
target_link_libraries(WidgetLib ${LIBS})
