#--------------------------------------
macro(GET_DIR_NAME DIRNAME)
   	string(REGEX MATCH "([^/]*)$" TMP ${CMAKE_CURRENT_SOURCE_DIR})
   	set(${DIRNAME} ${TMP})
endmacro(GET_DIR_NAME DIRNAME)
#--------------------------------------

#--------------------------------------
macro(ADD_ALL_SUBDIR)
    file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child})
            if(${child} STREQUAL "CMakeFiles")
            else(${child})
                LIST(APPEND dirlist ${child})
            endif()
        endif()
    endforeach()
    foreach(subdir ${dirlist})
        add_subdirectory(${subdir})
    endforeach()
endmacro(ADD_ALL_SUBDIR)
#--------------------------------------

#--------------------------------------
macro(SETUP_PROJECT MODE TARGET_NAME STR_TARGET_SOURCES STR_TARGET_LIBS)
	string(REPLACE " " ";" LIST_TARGET_SOURCES ${STR_TARGET_SOURCES})
	string(REPLACE " " ";" LIST_TARGET_LIBS ${STR_TARGET_LIBS})
	if(${STR_TARGET_SOURCES} STREQUAL " ")
		message(WARNING "Target [${TARGET_NAME}] has no source, so it won't be generated.")
	else()
		if(${MODE} STREQUAL "EXE")
			add_executable( ${TARGET_NAME} ${LIST_TARGET_SOURCES})
			set(INSTALL_DIR "bin")
			install (TARGETS ${TARGET_NAME} DESTINATION ${INSTALL_DIR})
		elseif(${MODE} STREQUAL "LIB")
			add_library(${TARGET_NAME} ${LIST_TARGET_SOURCES})
			#set(INSTALL_DIR "lib/Gen")
		else()
			message(FATAL_ERROR "Mode [${MODE}] is not supported, so target [TARGET_NAME] is not generated!")
			set(MODE_NOTSUPPORT " ")
		endif()
		if(NOT DEFINED MODE_NOTSUPPORT)
			if( NOT ${FOLDER_NAME} STREQUAL " ")
				SET_TARGET_PROPERTIES(${TARGET_NAME} PROPERTIES FOLDER ${FOLDER_NAME})
			endif()
			if(NOT ${STR_TARGET_LIBS} STREQUAL " ")
				target_link_libraries( ${TARGET_NAME} ${LIST_TARGET_LIBS} )
			endif()
			#install (TARGETS ${TARGET_NAME} DESTINATION ${INSTALL_DIR})
			message(STATUS "Setup Target ${FOLDER_NAME}/[${TARGET_NAME}] success")
		endif()
	endif()
endmacro(SETUP_PROJECT TARGET_NAME STR_TARGET_SOURCES STR_TARGET_LIBS)
#--------------------------------------

#--------------------------------------
macro(SETUP_PROJECT_DR MODE TARGET_NAME STR_TARGET_SOURCES STR_TARGET_LIBS_COMMON STR_TARGET_LIBS_DEBUG STR_TARGET_LIBS_RELEASE)
	string(REPLACE " " ";" LIST_TARGET_SOURCES ${STR_TARGET_SOURCES})

	string(REPLACE " " ";" STR_TARGET_LIBS_COMMON ${STR_TARGET_LIBS_COMMON})
	string(REPLACE " " ";" LIST_TARGET_LIBS_COMMON ${STR_TARGET_LIBS_COMMON})

	string(REPLACE " " ";" STR_TARGET_LIBS_DEBUG ${STR_TARGET_LIBS_DEBUG})
	string(REPLACE " " ";" LIST_TARGET_LIBS_DEBUG ${STR_TARGET_LIBS_DEBUG})

	string(REPLACE " " ";" STR_TARGET_LIBS_RELEASE ${STR_TARGET_LIBS_RELEASE})
	string(REPLACE " " ";" LIST_TARGET_LIBS_RELEASE ${STR_TARGET_LIBS_RELEASE})
	
	if(${STR_TARGET_SOURCES} STREQUAL " ")
		message(WARNING "Target [${TARGET_NAME}] has no source, so it won't be generated.")
	else()
		if(${MODE} STREQUAL "EXE")
			add_executable( ${TARGET_NAME} ${LIST_TARGET_SOURCES})
			set(INSTALL_DIR "bin")
		elseif(${MODE} STREQUAL "LIB")
			add_library(${TARGET_NAME} ${LIST_TARGET_SOURCES})
			set(INSTALL_DIR "lib/${FOLDER_NAME}")
		else()
			message(FATAL_ERROR "Mode [${MODE}] is not supported, so target [TARGET_NAME] is not generated!")
			set(MODE_NOTSUPPORT " ")
		endif()
		if(NOT DEFINED MODE_NOTSUPPORT)
			if( NOT ${FOLDER_NAME} STREQUAL " ")
				SET_TARGET_PROPERTIES(${TARGET_NAME} PROPERTIES FOLDER ${FOLDER_NAME})
			endif()
			if(NOT ${STR_TARGET_LIBS_COMMON} STREQUAL " ")
				target_link_libraries( ${TARGET_NAME} ${LIST_TARGET_LIBS_COMMON} )
			endif()
			if(NOT ${STR_TARGET_LIBS_DEBUG} STREQUAL " ")
				target_link_libraries( ${TARGET_NAME} debug ${LIST_TARGET_LIBS_DEBUG} )
			endif()
			if(NOT ${STR_TARGET_LIBS_RELEASE} STREQUAL " ")
				target_link_libraries( ${TARGET_NAME} optimized ${LIST_TARGET_LIBS_RELEASE} )
			endif()
			install (TARGETS ${TARGET_NAME} DESTINATION ${INSTALL_DIR})
			message(STATUS "Setup Project ${Mode} ${FOLDER_NAME}/[${TARGET_NAME}]")
		endif()
	endif()
endmacro(SETUP_PROJECT_DR MODE TARGET_NAME STR_TARGET_SOURCES STR_TARGET_LIBS_COMMON STR_TARGET_LIBS_DEBUG STR_TARGET_LIBS_RELEASE)
#--------------------------------------

#--------------------------------------
macro(INSTALL_SHADERS)
	# copy shader files to build directory
	file(GLOB SHADERS
		"${CMAKE_CURRENT_SOURCE_DIR}/*.vs"
		"${CMAKE_CURRENT_SOURCE_DIR}/*.fs"
		"${CMAKE_CURRENT_SOURCE_DIR}/*.gs"
	)

	foreach(SHADER ${SHADERS})
		string(REGEX MATCH "([^/]*)$" TMP ${SHADER})
		add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SHADER} "${CMAKE_SOURCE_DIR}/data/shaders/${FOLDER_NAME}/${DIRNAME}/${TMP}")
		install(FILES ${SHADER} DESTINATION "data/shaders/${FOLDER_NAME}/${DIRNAME}")
	endforeach(SHADER)
endmacro(INSTALL_SHADERS)
#--------------------------------------


#--------------------------------------
macro(QT_BEGIN)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
endmacro(QT_BEGIN)

macro(QT_END)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTORCC OFF)
endmacro(QT_END)
#--------------------------------------

#--------------------------------------
#--------------------------------------


set_property(GLOBAL PROPERTY USE_FOLDERS ON)

cmake_minimum_required(VERSION 3.5)
project(FantasyLab LANGUAGES CXX)

# The version number.
set (${PROJECT_NAME}_VERSION_MAJOR 1)
set (${PROJECT_NAME}_VERSION_MINOR 0)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/CMake"
  ${CMAKE_MODULE_PATH}
)

# Find the QtWidgets library
set(USE_QT_OPENGL_API ON)
find_package(Qt5 REQUIRED Widgets OpenGL)

configure_file(config/config.in ${CMAKE_SOURCE_DIR}/config/config.out)
install(FILES "${CMAKE_SOURCE_DIR}/config/config.out"
  DESTINATION config)
configure_file(config/ROOT_PATH.h.in config/ROOT_PATH.h)

include_directories (
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/include/3rdParty
	${CMAKE_BINARY_DIR}/config
	# $ENV{XXX_INCLUDE_PATH}
	# ...
)
link_directories (
	${PROJECT_SOURCE_DIR}/lib
	${PROJECT_SOURCE_DIR}/lib/QTGL
	# $ENV{XXX_LIB_PATH}
	# ...
)


add_subdirectory (source)
add_subdirectory (lib)

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
set (CPACK_PACKAGE_CONTACT       "12345678@qq.com")
include (CPack)
