cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
if (MINGW)

endif()
project(PixelFun LANGUAGES CXX)

# libSDLpp configuration
set(SDL2PP_WITH_IMAGE OFF)
set(SDL2PP_WITH_TTF OFF)
set(SDL2PP_WITH_MIXER OFF)
set(SDL2PP_STATIC ON)
set(SDL2_STATIC ON)

if (MINGW)
	# message(STATUS doing stuff with mingw)
	set(SDL2_DIR "vendor/mingw/SDL-2.30.2/cmake")
endif()

# add compilation flags
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vendor/fmt)
add_subdirectory(vendor/libquickjs)

add_subdirectory(vendor/libSDL2pp)

file(GLOB SOURCES
	src/*.h
	src/*.hpp
	src/*.cpp
	src/**/*.h
	src/**/*.hpp
	src/**/*.cpp
)


# 1. Look for a SDL2 package, 2. look for the SDL2 component and 3. fail if none can be found
# find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

# 1. Look for a SDL2 package, 2. Look for the SDL2maincomponent and 3. DO NOT fail when SDL2main is not available
# find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} ${SDL2PP_HEADERS} ${SDL2PP_SOURCES} ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${SDL2_INCLUDE_DIRS})


target_include_directories(${PROJECT_NAME} PRIVATE vendor/libSDL2pp)
# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()

if(MINGW)
	target_compile_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt libquickjs SDL2pp::SDL2pp ${SDL2_LIBRARIES})
