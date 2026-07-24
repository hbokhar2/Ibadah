cmake_minimum_required(VERSION 3.24)

set(TARGET_NAME Ibadah)
project(${TARGET_NAME} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB SOURCES CONFIGURE_DEPENDS
	"*.cpp"
	"*.c"
)

add_subdirectory(godot-cpp godot-cpp)
add_subdirectory(entities)
add_subdirectory(scenes)
add_subdirectory(systems)

add_library(${TARGET_NAME} SHARED 
	${SOURCES}
)

target_link_libraries(${TARGET_NAME} 
PRIVATE
	Systems
	godot-cpp

PUBLIC
	Entities
	Scenes
)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	$<TARGET_FILE:${TARGET_NAME}>
	${CMAKE_CURRENT_SOURCE_DIR}/../gd/bin
)
