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
  glad
  GIT_REPOSITORY "https://github.com/krieselreihe/glad.git"
  GIT_TAG v1.0.0
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

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
  GIT_TAG v1.13.0
)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
  # GIT_TAG 085781f5ca5372d5fc804d7e44b5bf27a8994af7 # Branch: docking, date: 19.03.2024, 06:52 GMT+1
  GIT_TAG 975beafafdcf8cdfa1b83261ce8c8cbeaa28091b # docking / 24.05.2024, 22:34 GMT+1
)

FetchContent_Declare(
    zep
    GIT_REPOSITORY "https://github.com/Rezonality/zep.git"
    GIT_TAG e743a43c384796dc0fc449245d9edf42390a7124
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
add_subdirectory(imgui-setup)

# Populate



FetchContent_MakeAvailable(doctest fmt glad imgui quickjs SDL2 libsdl2pp spdlog)

add_subdirectory(zep_imgui)
