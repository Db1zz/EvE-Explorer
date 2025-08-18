cmake_minimum_required(VERSION 3.11)
project(eve_explorer VERSION 0.0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(COMPILER_FLAGS
	"-Wno-deprecated"
)
set(CMAKE_CXX_FLAGS ${COMPILER_FLAGS})

set(INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/include/eve_explorer_qml_integration
	${CMAKE_CURRENT_SOURCE_DIR}/include/eve_explorer)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(QML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/qml)
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(EVE_UNIVERSE_DATABASE_NAME eve_universe_db.sqlite)
set(EVE_UNIVERSE_DATABASE_DIR ${RESOURCES_DIR}/sde)
set(EVE_UNIVERSE_DATABASE_PATH ${EVE_UNIVERSE_DATABASE_DIR}/${EVE_UNIVERSE_DATABASE_NAME})

set(SQLITE_MODERN_CPP ${CMAKE_CURRENT_SOURCE_DIR}/third_party/sqlite_modern_cpp/hdr)

find_package(SQLite3 REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

foreach(CURR_DIR IN LISTS INCLUDE_DIR)
	file(GLOB INCLUDE ${CURR_DIR}/*.h)
endforeach()

file(GLOB SRC ${SRC_DIR}/*.cc)
file(GLOB QML_SRC ${QML_DIR}/*.qml)
find_package(Qt6 REQUIRED 
					COMPONENTS
						Gui
						Widgets
						Qml
						Quick
						Core
)
qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME} ${SRC} ${INCLUDE} resources.qrc)

qt_add_qml_module(${PROJECT_NAME}
					URI qml.aboba
					QML_FILES
						qml/main.qml
					SOURCES
						${CMAKE_CURRENT_SOURCE_DIR}/include/eve_explorer_qml_integration/vector_integration.h
)

if (NOT EXISTS ${EVE_UNIVERSE_DATABASE_PATH})
	if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/downloads/sqlite-latest.sqlite.bz2)
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


target_include_directories(
	${PROJECT_NAME} PRIVATE
		${INCLUDE_DIR}
		${SQLITE_MODERN_CPP}
)

target_link_libraries(
	${PROJECT_NAME} PRIVATE
		SQLite3
		Qt6::Widgets
		Qt6::Gui
		Qt6::Qml
		Qt6::Quick
		Qt6::Core
)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
					COMMAND
						${CMAKE_COMMAND} -E copy_directory
						${CMAKE_SOURCE_DIR}/eve_explorer/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)
