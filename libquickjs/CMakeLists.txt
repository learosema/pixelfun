cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(libquickjs C)

set(QUICKJS_VERSION STRING "0.1.0")
set(COMPILE_FLAGS -Wall -Wno-array-bounds)

set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# config build target: "Debug" or "Release"
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(COMPILE_FLAGS ${COMPILE_FLAGS} -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(COMPILE_FLAGS ${COMPILE_FLAGS} -O3)
endif()

# add -lm if on Linux to handle math.h
# see: https://askubuntu.com/a/332919
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND LINK_LIBRARIES "m")
endif()



add_compile_options(${COMPILE_FLAGS})
add_compile_definitions(
    -D_GNU_SOURCE
    -DCONFIG_BIGNUM
	-DCONFIG_VERSION=${\"QUICKJS_VERSION\"}
)

add_library(libquickjs
	./quickjs/quickjs.h
	./quickjs/quickjs-libc.h
	./quickjs/quickjs.c
	./quickjs/libregexp.c
	./quickjs/libunicode.c
	./quickjs/cutils.c
	./quickjs/libbf.c
	./quickjs/quickjs-libc.c
)

file(GLOB QUICKJS_HEADERS
  ./quickjs/*.h
)
file(MAKE_DIRECTORY include)
file(COPY ${QUICKJS_HEADERS} DESTINATION include)


foreach(Item IN LISTS QUICKJS_HEADERS)
	cmake_path(GET Item FILENAME HFile)
	file(COPY_FILE ${Item} include/${HFile})
endforeach()
target_include_directories(libquickjs PUBLIC include)
