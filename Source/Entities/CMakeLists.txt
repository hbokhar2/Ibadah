set(TARGET_NAME Entities)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
	"*.cpp"
	"*.c"
)

add_library(${TARGET_NAME} STATIC 
	${SOURCES}
)

target_include_directories(${TARGET_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/Player
)

target_link_libraries(${TARGET_NAME} PRIVATE
	godot-cpp
	Systems
)
