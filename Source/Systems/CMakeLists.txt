set(TARGET_NAME Systems)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
	"*.cpp"
	"*.c"
)

add_library(${TARGET_NAME} STATIC
	${SOURCES}
)

target_include_directories(${TARGET_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${TARGET_NAME} PUBLIC
	godot-cpp
)
