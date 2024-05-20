FetchContent_GetProperties(quickjs)
if (NOT quickjs_POPULATED)
  FetchContent_Populate(quickjs)
endif ()

set(QUICKJS_VERSION "0.1.0")

# TODO Do I need this?
# set(COMPILE_FLAGS -Wall -Wno-array-bounds)
# set(CMAKE_C_STANDARD 17)
# set(CMAKE_C_STANDARD_REQUIRED 17)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#
# # config build target: "Debug" or "Release"
# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#     set(COMPILE_FLAGS ${COMPILE_FLAGS} -g)
# elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
#     set(COMPILE_FLAGS ${COMPILE_FLAGS} -O3)
# endif()

add_library(libquickjs
	${quickjs_SOURCE_DIR}/quickjs.h
	${quickjs_SOURCE_DIR}/quickjs-libc.h
	${quickjs_SOURCE_DIR}/quickjs.c
	${quickjs_SOURCE_DIR}/libregexp.c
	${quickjs_SOURCE_DIR}/libunicode.c
	${quickjs_SOURCE_DIR}/cutils.c
	${quickjs_SOURCE_DIR}/libbf.c
	${quickjs_SOURCE_DIR}/quickjs-libc.c
)

file(GLOB QUICKJS_HEADERS
  ./quickjs/*.h
)
file(MAKE_DIRECTORY include)

foreach(Item IN LISTS QUICKJS_HEADERS)
	cmake_path(GET Item FILENAME HFile)
	file(COPY_FILE ${Item} include/${HFile})
endforeach()



# add -lm if on Linux to handle math.h
# see: https://askubuntu.com/a/332919
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(quickjs PRIVATE m)
endif()

# TODO Do i need this?
# if(MINGW)
# 	set(COMPILE_FLAGS ${COMPILE_FLAGS} -static-libgcc)
# 	list(APPEND LINK_LIBRARIES "pthread")
# endif()

target_include_directories(quickjs PUBLIC include)
target_compile_definitions(quickjs PRIVATE
	_GNU_SOURCE
	CONFIG_BIGNUM
	CONFIG_VERSION=\"${QUICKJS_VERSION}\"
)
target_compile_features(quickjs PRIVATE c_std_17)
