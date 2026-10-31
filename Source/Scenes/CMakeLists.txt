set(TARGET_NAME Scenes)

file(GLOB MAIN_SCENE_SOURCES CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/Main/*.cpp"
)

add_library(${TARGET_NAME} STATIC
	${MAIN_SCENE_SOURCES}
)

target_include_directories(${TARGET_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/Main
)

target_link_libraries(${TARGET_NAME} 
	PUBLIC
		godot-cpp
		Entities
		Systems
)
