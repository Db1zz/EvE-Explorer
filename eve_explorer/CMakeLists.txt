cmake_minimum_required(VERSION 3.11)
project(eve_explorer VERSION 0.0.1)

set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

set(EVE_UNIVERSE_DATABASE_NAME eve_universe_db.sqlite)
set(EVE_UNIVERSE_DATABASE_DIR ${RESOURCES_DIR}/sde)
set(EVE_UNIVERSE_DATABASE_PATH ${EVE_UNIVERSE_DATABASE_DIR}/${EVE_UNIVERSE_DATABASE_NAME})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

set(QML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/qml)
file(GLOB QML_SRC ${QML_DIR}/*.qml)

# The project depends on SQLite, so add it here :>
set(SQLITE_MODERN_CPP ${CMAKE_CURRENT_SOURCE_DIR}/third_party/sqlite_modern_cpp/hdr)
find_package(SQLite3 REQUIRED)

# Also on QT
find_package(Qt6 REQUIRED 
					COMPONENTS
						Gui
						Widgets
						Qml
						Quick
						Core # Quick is depends on core but I'll put it here just in case
)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

add_subdirectory(src)

qt_standard_project_setup()
qt_add_executable(${PROJECT_NAME} ${SRC} ${INCLUDE} resources.qrc)
qt_add_qml_module(${PROJECT_NAME}
	            	URI MyLib
					QML_FILES
						qml/main.qml
						qml/mapSolarSystemObject.qml
						qml/line.qml
						SOURCES
							src/types/point.h
							src/types/point.cc
							src/types/stargate.h
							src/types/stargate.cc
							src/types/solar_system.h
							src/types/solar_system.cc
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${SQLITE_MODERN_CPP}
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		eve_explorer_backend
)

if (NOT EXISTS ${EVE_UNIVERSE_DATABASE_PATH})
	if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/downloads/sqlite-latest.sqlite.bz2)
		message(STATUS "Downloading EvE Universe Database... ")
		file(DOWNLOAD 
				https://www.fuzzwork.co.uk/dump/sqlite-latest.sqlite.bz2
				${CMAKE_CURRENT_SOURCE_DIR}/downloads/sqlite-latest.sqlite.bz2
			SHOW_PROGRESS)
	endif()
	add_custom_target(eve_universe_database_worker
		COMMAND bunzip2 -f ${CMAKE_CURRENT_SOURCE_DIR}/downloads/sqlite-latest.sqlite.bz2
				&& ${CMAKE_COMMAND} -E make_directory ${EVE_UNIVERSE_DATABASE_DIR}
				&& ${CMAKE_COMMAND} -E rename
					${CMAKE_CURRENT_SOURCE_DIR}/downloads/sqlite-latest.sqlite
					${EVE_UNIVERSE_DATABASE_PATH}
				&& rm -rf ${CMAKE_CURRENT_SOURCE_DIR}/downloads)
	add_dependencies(${PROJECT_NAME} eve_universe_database_worker)
endif()

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
					COMMAND
						${CMAKE_COMMAND} -E copy_directory
						${CMAKE_SOURCE_DIR}/eve_explorer/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)
