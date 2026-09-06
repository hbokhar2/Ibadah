set(TARGET_NAME Scenes)

add_subdirectory(Main)

add_library(${TARGET_NAME} STATIC
	$<TARGET_OBJECTS:Main>
)

target_link_libraries(${TARGET_NAME} 
	PRIVATE
		Entities
		Main
)
