cmake_minimum_required(VERSION 3.24)

set(TARGET_NAME Ibadah)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(${TARGET_NAME} LANGUAGES C CXX)

file(GLOB SOURCES CONFIGURE_DEPENDS
	"*.cpp"
	"*.c"
)

add_subdirectory(godot-cpp godot-cpp)
add_subdirectory(Entities)
add_subdirectory(Scenes)
add_subdirectory(Systems)

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
	${CMAKE_CURRENT_SOURCE_DIR}/../GD/Bin
	COMMENT "Copying lib${TARGET_NAME} to GD/Bin directory"
)
