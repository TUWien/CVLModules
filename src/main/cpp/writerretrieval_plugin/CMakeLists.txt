PROJECT(MyWriterRetrieval)

IF(EXISTS ${CMAKE_SOURCE_DIR}/../CMakeUser.cmake)
	include(${CMAKE_SOURCE_DIR}/../CMakeUser.cmake)
ENDIF()

# include macros needed
include("${CMAKE_CURRENT_SOURCE_DIR}/../Utils.cmake")

SET(PLUGIN_VERSION "0.0.1")
add_definitions(-DPLUGIN_VERSION="${PLUGIN_VERSION}")


file(GLOB TI_PLUGIN_SOURCES "MyWriterRetrieval.cpp")
file(GLOB TI_PLUGIN_HEADERS "MyWriterRetrieval.h")

set(TI_PLUGIN_NAME ${PROJECT_NAME})

# ReadFramework is needed by Writer Retrieval plugin
TI_FIND_RDF()

set(LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs ${CMAKE_CURRENT_BINARY_DIR}) #add libs directory to library dirs
link_directories(
	${LIBRARY_DIR}
	${RDF_BUILD_DIRECTORY}
)

include_directories (
	${RDF_INCLUDE_DIRECTORY}
)

add_library(${TI_PLUGIN_NAME} SHARED ${TI_PLUGIN_SOURCES} ${TI_PLUGIN_HEADERS})
target_link_libraries(${TI_PLUGIN_NAME} ${TI_INTERFACE_NAME} ${OpenCV_LIBS} ${RDF_LIBS} Qt5::Core)
add_dependencies(${TI_PLUGIN_NAME} ${TI_INTERFACE_NAME})

if(MSVC) # linux does not need this
    set_target_properties(${TI_PLUGIN_NAME} PROPERTIES COMPILE_FLAGS "-DTI_DLL_EXPORT")
endif()

if(NOT MSVC) # enable soname
    set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION ${TI_VERSION_MAJOR}.${TI_VERSION_MINOR}.${TI_VERSION_PATCH})
    set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION ${TI_VERSION_MAJOR})
endif()

message(STATUS "${TI_PLUGIN_NAME} added...")

##################################################### add testing exe ##########
SET(TI_EXAMPLE_NAME Test${TI_PLUGIN_NAME})
file(GLOB TI_EXAMPLE_SOURCES "testApp.cpp")

add_executable(${TI_EXAMPLE_NAME} WIN32  MACOSX_BUNDLE ${TI_EXAMPLE_SOURCES})
target_link_libraries(${TI_EXAMPLE_NAME} ${TI_INTERFACE_NAME} ${OpenCV_LIBS} ${CURL_LIBRARY})
set_target_properties(${TI_EXAMPLE_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")

add_dependencies(${TI_EXAMPLE_NAME} ${TI_INTERFACE_NAME} ${TI_PLUGIN_NAME})


# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

	### DependencyCollector
if (MSVC)
	set(DC_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/DependencyCollector.py)
	set(DC_CONFIG ${CMAKE_BINARY_DIR}/DependencyCollector.ini)

	GET_FILENAME_COMPONENT(VS_PATH ${CMAKE_LINKER} PATH)
	if(CMAKE_CL_64)
		SET(VS_PATH "${VS_PATH}/../../../Common7/IDE/Remote Debugger/x64")
	else()
		SET(VS_PATH "${VS_PATH}/../../Common7/IDE/Remote Debugger/x86")
	endif()
	SET(DC_PATHS_RELEASE ${OpenCV_DIR}/bin/Release ${QT_QMAKE_PATH} ${VS_PATH} ${RDF_BUILD_DIRECTORY}/Release ${CURL_BUILD_DIR}/lib/Release)
	SET(DC_PATHS_DEBUG ${OpenCV_DIR}/bin/Debug ${QT_QMAKE_PATH} ${VS_PATH} ${RDF_BUILD_DIRECTORY}/Debug ${CURL_BUILD_DIR}/lib/Debug)

	configure_file(${CMAKE_SOURCE_DIR}/cmake/DependencyCollector.config.cmake.in ${DC_CONFIG})

	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND python ${DC_SCRIPT} --infile $<TARGET_FILE:${PROJECT_NAME}> --configfile ${DC_CONFIG} --configuration $<CONFIGURATION>)
endif(MSVC)