set(TARGET_NAME Entities)

add_subdirectory(Player)

add_library(${TARGET_NAME} STATIC 
	$<TARGET_OBJECTS:Player>
)

target_link_libraries(${TARGET_NAME} PUBLIC
	Player
)
