set(SOURCES
	# Empty
)

add_library(utilities ${SOURCES})

target_include_directories(utilities
	PUBLIC	
		${CMAKE_CURRENT_SOURCE_DIR}
)
