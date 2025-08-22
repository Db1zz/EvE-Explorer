cmake_minimum_required(VERSION 3.11)
project(eve_backend VERSION 0.0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(COMPILER_FLAGS
	"-Wno-deprecated"
)
set(CMAKE_CXX_FLAGS ${COMPILER_FLAGS})

add_subdirectory(core)
add_subdirectory(database)
add_subdirectory(types)
add_subdirectory(utilities)

qt_add_library(eve_explorer_backend main.cc)

target_link_libraries(eve_explorer_backend
	PUBLIC
		core
		database
		types
		utilities
		Qt6::Qml
		Qt6::Gui
)