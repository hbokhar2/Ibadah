set(TARGET_NAME Networking)

set(STEAM_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../External/SteamSDK/public/steam")
if(WIN32)
	set(STEAM_LIB "${CMAKE_CURRENT_SOURCE_DIR}/../../External/SteamSDK/redistributable_bin/win64/steam_api64.lib")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(STEAM_LIB "${CMAKE_CURRENT_SOURCE_DIR}/../../External/SteamSDK/redistributable_bin/linux64/libsteam_api.so")
endif()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
	"*.cpp"
	"*.c"
)

add_library(${TARGET_NAME} OBJECT
	${SOURCES}
)

target_include_directories(${TARGET_NAME} PUBLIC
	${STEAM_INCLUDE_DIR}
)

target_link_libraries(${TARGET_NAME} PRIVATE
	Input
	${STEAM_LIB}
)
