set(SOURCES
	# Empty
)

qt_add_library(core ${SOURCES})

target_include_directories(core
	PUBLIC	
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(core
	PUBLIC
		database
		types
		utilities
)