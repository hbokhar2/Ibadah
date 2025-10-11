cmake_minimum_required(VERSION 3.24)
set(PROJECT_NAME HorrorGame)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GODOT_INCLUDE 
	"${CMAKE_SOURCE_DIR}/../../godot-cpp/include"
	"${CMAKE_SOURCE_DIR}/../../godot-cpp/gen/include"
	"${CMAKE_SOURCE_DIR}/../../godot-cpp/gdextension"
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
	"${CMAKE_SOURCE_DIR}/*.cpp"
	"${CMAKE_SOURCE_DIR}/*.c"
)

if(WIN32)
	set(GODOT_LIB "${CMAKE_SOURCE_DIR}/../../godot-cpp/bin/libgodot-cpp.windows.template_debug.x86_64.lib")
elseif(UNIX)
	set(GODOT_LIB "${CMAKE_SOURCE_DIR}/../../godot-cpp/bin/libgodot-cpp.linux.template_debug.x86_64.a")
endif()

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${GODOT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GODOT_LIB})
