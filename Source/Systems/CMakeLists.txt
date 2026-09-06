add_subdirectory(Input)
add_subdirectory(Networking)

set(TARGET_NAME Systems)

add_library(${TARGET_NAME} STATIC
	$<TARGET_OBJECTS:Input>
	$<TARGET_OBJECTS:Networking>
)

target_link_libraries(${TARGET_NAME} PUBLIC
	Input
)
