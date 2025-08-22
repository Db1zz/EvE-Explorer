set(SOURCES
	point.cc
	solar_system.cc
	stargate.cc
)

set(INCLUDE
	common_types.h
	point.h
	solar_system.h
	stargate.h
)

qt_add_library(types ${SOURCES} ${INCLUDE})

target_include_directories(types
	PUBLIC	
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(types
	PUBLIC
		Qt6::Core
		Qt6::Gui
		Qt6::Widgets
		Qt6::Qml
		Qt6::Quick
)