cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(SDL2Test LANGUAGES CXX)

# add compilation flags
set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR})

file(GLOB SOURCES
    src/*.cpp
    include/*.hpp
	include/*.h
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# set up SDL2pp library
set(SDL2PP_WITH_IMAGE OFF) # if you need SDL_image support
set(SDL2PP_WITH_MIXER OFF) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF OFF) # if you need SDL_ttf support
add_subdirectory(libSDL2pp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})



