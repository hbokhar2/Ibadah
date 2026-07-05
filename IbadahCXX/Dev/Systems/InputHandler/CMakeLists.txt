set(TARGET InputHandler)

add_library(${TARGET} SHARED
	"${CMAKE_SOURCE_DIR}/../InputHandler.cpp"
)

set_target_properties(${TARGET} PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(${TARGET} 
	PUBLIC
		"${CMAKE_SOURCE_DIR}/../"
)

if(WIN32)
	set(GODOT_LIB "${CMAKE_SOURCE_DIR}/../../godot-cpp/bin/libgodot-cpp.windows.template_debug.x86_64.lib")
elseif(UNIX)
	set(GODOT_LIB "${CMAKE_SOURCE_DIR}/../../godot-cpp/bin/libgodot-cpp.linux.template_debug.x86_64.a")
endif()

target_link_libraries(${TARGET} 
	PUBLIC 
		${GODOT_LIB}
)
