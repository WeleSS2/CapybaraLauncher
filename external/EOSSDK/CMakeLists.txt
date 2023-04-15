set(STEAMAPI_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include")

# Support both 32 and 64 bit builds

if (WIN32)
	set(STEAMAPI_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/win64/steam_api64.lib")
endif (WIN32)

if (UNIX)
	if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		set(STEAMAPI_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/linux32/libsteam_api.so")
	else ()
		set(STEAMAPI_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/linux64/libsteam_api.so")
	endif ()
endif (UNIX)

string(STRIP "${STEAMAPI_LIBRARIES}" STEAMAPI_LIBRARIES)