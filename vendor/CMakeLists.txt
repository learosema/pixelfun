include(FetchContent)

# Dependencies

FetchContent_Declare(
  doctest
  GIT_REPOSITORY "https://github.com/onqtam/doctest.git"
  GIT_TAG v2.4.11
)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
  GIT_TAG 10.2.1
)

FetchContent_Declare(
  SDL2
  GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
  GIT_TAG release-2.30.1
)

FetchContent_Declare(
	quickjs
	GIT_REPOSITORY "https://github.com/bellard/quickjs.git"
	GIT_TAG d378a9f3a583cb787c390456e27276d0ee377d23        # Latest release as of May 20, 2024
)

FetchContent_Declare(
	libSDL2pp
	GIT_REPOSITORY https://github.com/libSDL2pp/libSDL2pp.git
	GIT_TAG 1447f88546061e663ebdc878e94bfc6ed95ab6fb
)

# Settings

# For SDL2 to be able to override options
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(DOCTEST_NO_INSTALL ON)
set(FMT_INSTALL OFF)
set(SDL2_DISABLE_SDL2MAIN ON)

# libSDL2pp Settings

set(SDL2PP_WITH_IMAGE OFF)
set(SDL2PP_WITH_TTF OFF)
set(SDL2PP_WITH_MIXER OFF)
set(SDL2PP_STATIC ON)
set(SDL2_STATIC ON)

add_subdirectory(quickjs-setup)

# Populate

FetchContent_MakeAvailable(doctest fmt quickjs SDL2 libsdl2pp)
