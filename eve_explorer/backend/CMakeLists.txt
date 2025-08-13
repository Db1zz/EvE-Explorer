include(ExternalProject)

project(eve_explorer_backend VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SQLITE_MODERN_CPP ${CMAKE_CURRENT_SOURCE_DIR}/third_party/sqlite_modern_cpp/hdr)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(EVE_UNIVERSE_DATABASE_NAME eve_universe_db.sqlite) 
set(EVE_UNIVERSE_DATABASE_DIR ${RESOURCES_DIR}/sde)
set(EVE_UNIVERSE_DATABASE_PATH ${EVE_UNIVERSE_DATABASE_DIR}/${EVE_UNIVERSE_DATABASE_NAME})

find_package(SQLite3 REQUIRED)

file(GLOB INCLUDE ${INCLUDE_DIR}/*.h)
file(GLOB SRC ${SRC_DIR}/*.cc)

add_executable(eve_explorer_backend ${SRC})

if (NOT EXISTS ${EVE_UNIVERSE_DATABASE_PATH})
	if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/downloads/sqlite-latest.sqlite.bz2)
		file(DOWNLOAD https://www.fuzzwork.co.uk/dump/sqlite-latest.sqlite.bz2 ${CMAKE_CURRENT_SOURCE_DIR}/downloads/sqlite-latest.sqlite.bz2
			SHOW_PROGRESS)
	endif()
	add_custom_target(eve_universe_database_worker
		COMMAND bunzip2 -f ${CMAKE_CURRENT_SOURCE_DIR}/downloads/sqlite-latest.sqlite.bz2
				&& ${CMAKE_COMMAND} -E make_directory ${EVE_UNIVERSE_DATABASE_DIR}
				&& ${CMAKE_COMMAND} -E rename
					${CMAKE_CURRENT_SOURCE_DIR}/downloads/sqlite-latest.sqlite
					${CMAKE_CURRENT_SOURCE_DIR}/resources/sde/eve_universe_db.sqlite
		COMMAND rm -rf ${CMAKE_CURRENT_SOURCE_DIR}/downloads)
	add_dependencies(eve_explorer_backend eve_universe_database_worker)
endif()


target_include_directories(
	${PROJECT_NAME} PRIVATE
		${INCLUDE_DIR}
		${SQLITE_MODERN_CPP})
target_link_libraries(
	${PROJECT_NAME} PRIVATE
		SQLite3
)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
						${CMAKE_SOURCE_DIR}/eve_explorer/backend/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
