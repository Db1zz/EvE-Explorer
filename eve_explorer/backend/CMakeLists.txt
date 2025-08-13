cmake_minimum_required(VERSION 3.11)
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

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
	include(FetchContent)
	FetchContent_Declare(
		raylib
		DOWNLOAD_EXTRACT_TIMESTAMP OFF
		URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
	)
	FetchContent_MakeAvailable(raylib)
endif()

set(RAYLIB_CPP_VERSION v5.5.0)
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    if (NOT DEFINED RAYLIB_CPP_VERSION)
        set(RAYLIB_CPP_VERSION next)
    endif()
    include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
		GIT_TAG ${RAYLIB_CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

file(GLOB INCLUDE ${INCLUDE_DIR}/*.h)
file(GLOB SRC ${SRC_DIR}/*.cc)

add_executable(${PROJECT_NAME} ${SRC})

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
	add_dependencies(${PROJECT_NAME} eve_universe_database_worker)
endif()


target_include_directories(
	${PROJECT_NAME} PRIVATE
		${INCLUDE_DIR}
		${SQLITE_MODERN_CPP})
# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(
		${PROJECT_NAME} PRIVATE
			"-framework IOKit"
			"-framework Cocoa"
			"-framework OpenGL"
)
endif()

target_link_libraries(
	${PROJECT_NAME} PRIVATE
		SQLite3
		raylib
		raylib_cpp
)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
						${CMAKE_SOURCE_DIR}/eve_explorer/backend/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
