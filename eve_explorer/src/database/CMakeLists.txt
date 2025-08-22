# The lib depends on SQLite, so add it here :>
set(SOURCES
	sqlite_eve_universe_database.cc
)

set(INCLUDE
	ieve_universe_database.h
	sqlite_eve_universe_database.h
)

qt_add_library(database ${SOURCES} ${INCLUDE})
target_include_directories(database
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
		${SQLITE_MODERN_CPP}
)

target_link_libraries(database
	PUBLIC
		types
		SQLite3
)