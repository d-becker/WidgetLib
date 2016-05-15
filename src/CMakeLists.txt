cmake_minimum_required (VERSION 2.8)

set(SRC_FILES
	Button.cpp
	Checkbox.cpp
	Container.cpp
	DrawingCanvas.cpp
	FreePanel.cpp
	Label.cpp
	RadioButton.cpp
	Selectable.cpp
	SelectablePanel.cpp
	Selection.cpp
	Selector.cpp
	TextBox.cpp
	TextDisplay.cpp
	Toplevel.cpp
	Widget.cpp	
)

set(MAIN_TEST main.cpp)

set(LIBS 
	FlugiLib
	${SDL_LIBRARY}
	${SDL_TTF_LIBRARY}
)

# Making the test executable
add_executable(WidgetLibTest ${MAIN_TEST} ${SRC_FILES})
target_link_libraries(WidgetLibTest ${LIBS})

# Making dynamic lib
add_library(WidgetLib SHARED ${SRC_FILES})
target_link_libraries(WidgetLib ${LIBS})
