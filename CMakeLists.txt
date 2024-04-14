cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(PixelFun LANGUAGES CXX)

# add compilation flags
set(CMAKE_CXX_STANDARD 17)

# set up SDL2pp library
set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER OFF) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF OFF) # if you need SDL_ttf support
add_subdirectory(libSDL2pp)

add_subdirectory(fmt)

file(GLOB SOURCES
	src/*.h
	src/*.hpp
	src/*.cpp
	src/**/*.h
	src/**/*.hpp
	src/**/*.cpp
)

add_subdirectory(libquickjs)

find_package(SDL2 REQUIRED)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt libquickjs SDL2pp::SDL2pp ${SDL2_LIBRARIES})
