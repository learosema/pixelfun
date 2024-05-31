
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_DEBUG_POSTFIX "-debug")
set(CMAKE_RELWITHDEBINFO_POSTFIX "-reldbg")

find_package(SDL2 REQUIRED)
# find_package(Freetype REQUIRED)

FetchContent_Declare(
    zep
    GIT_REPOSITORY "https://github.com/Rezonality/zep.git"
    GIT_TAG e743a43c384796dc0fc449245d9edf42390a7124
)
FetchContent_Populate(zep)

SET(ZEP_ROOT ${zep_SOURCE_DIR})

SET(ZEP_SOURCE
${ZEP_ROOT}/include/zep/buffer.h
${ZEP_ROOT}/include/zep/range_markers.h
${ZEP_ROOT}/include/zep/glyph_iterator.h
${ZEP_ROOT}/include/zep/commands.h
${ZEP_ROOT}/include/zep/display.h
${ZEP_ROOT}/include/zep/editor.h
${ZEP_ROOT}/include/zep/filesystem.h
${ZEP_ROOT}/include/zep/indexer.h
${ZEP_ROOT}/include/zep/keymap.h
${ZEP_ROOT}/include/zep/line_widgets.h
${ZEP_ROOT}/include/zep/mcommon/animation/timer.h
${ZEP_ROOT}/include/zep/mcommon/file/cpptoml.h
${ZEP_ROOT}/include/zep/mcommon/file/path.h
${ZEP_ROOT}/include/zep/mcommon/logger.h
${ZEP_ROOT}/include/zep/mcommon/string/stringutils.h
${ZEP_ROOT}/include/zep/mcommon/threadutils.h
${ZEP_ROOT}/include/zep/mode.h
${ZEP_ROOT}/include/zep/mode_search.h
${ZEP_ROOT}/include/zep/mode_standard.h
${ZEP_ROOT}/include/zep/mode_tree.h
${ZEP_ROOT}/include/zep/mode_vim.h
${ZEP_ROOT}/include/zep/mode_repl.h
${ZEP_ROOT}/include/zep/regress.h
${ZEP_ROOT}/include/zep/scroller.h
${ZEP_ROOT}/include/zep/splits.h
${ZEP_ROOT}/include/zep/syntax.h
${ZEP_ROOT}/include/zep/syntax_providers.h
${ZEP_ROOT}/include/zep/syntax_rainbow_brackets.h
${ZEP_ROOT}/include/zep/syntax_tree.h
${ZEP_ROOT}/include/zep/syntax_markdown.h
${ZEP_ROOT}/include/zep/tab_window.h
${ZEP_ROOT}/include/zep/theme.h
${ZEP_ROOT}/include/zep/window.h
${ZEP_ROOT}/src/CMakeLists.txt
${ZEP_ROOT}/src/buffer.cpp
${ZEP_ROOT}/src/range_markers.cpp
${ZEP_ROOT}/src/glyph_iterator.cpp
${ZEP_ROOT}/src/commands.cpp
${ZEP_ROOT}/src/display.cpp
${ZEP_ROOT}/src/editor.cpp
${ZEP_ROOT}/src/filesystem.cpp
${ZEP_ROOT}/src/indexer.cpp
${ZEP_ROOT}/src/keymap.cpp
${ZEP_ROOT}/src/line_widgets.cpp
${ZEP_ROOT}/src/mcommon/animation/timer.cpp
${ZEP_ROOT}/src/mcommon/string/stringutils.cpp
${ZEP_ROOT}/src/mcommon/file/path.cpp
${ZEP_ROOT}/src/mode.cpp
${ZEP_ROOT}/src/mode_search.cpp
${ZEP_ROOT}/src/mode_standard.cpp
${ZEP_ROOT}/src/mode_tree.cpp
${ZEP_ROOT}/src/mode_vim.cpp
${ZEP_ROOT}/src/mode_repl.cpp
${ZEP_ROOT}/src/regress.cpp
${ZEP_ROOT}/src/scroller.cpp
${ZEP_ROOT}/src/splits.cpp
${ZEP_ROOT}/src/syntax.cpp
${ZEP_ROOT}/src/syntax_providers.cpp
${ZEP_ROOT}/src/syntax_rainbow_brackets.cpp
${ZEP_ROOT}/src/syntax_tree.cpp
${ZEP_ROOT}/src/syntax_markdown.cpp
${ZEP_ROOT}/src/tab_window.cpp
${ZEP_ROOT}/src/theme.cpp
${ZEP_ROOT}/src/window.cpp
)

set(SOURCES ${ZEP_SOURCE})

# Create the library - No depenencies on anything else in this file
add_library(Zep STATIC ${SOURCES})
add_library(Zep::Zep ALIAS Zep)

target_include_directories(Zep
    PRIVATE
        ${ZEP_ROOT}
        ${ZEP_ROOT}/src/mcommon
        ${ZEP_ROOT}/src
        ${ZEP_ROOT}/include
        config
    PUBLIC
        ${ZEP_ROOT}
        ${ZEP_ROOT}/include
    )

target_compile_options(Zep PRIVATE -Wno-error -Wno-deprecated-declarations -Wno-float-conversion -Wno-non-virtual-dtor -Wno-unused-variable -Wno-reorder-ctor)
target_compile_definitions(Zep PRIVATE -DZEP_USE_SDL)

# Set this to get the default file system
target_compile_definitions(Zep PRIVATE -DZEP_FEATURE_CPP_FILE_SYSTEM)


if (TARGET_LINUX)
target_link_libraries(Zep
	PUBLIC
	stdc++fs
)
endif()

set(SOURCES
    src/zep_helpers.cpp
    include/zep_helpers.h
)

add_library(zep_imgui ${SOURCES})
# Set this if we are sitting on SDL
target_compile_definitions(zep_imgui PRIVATE -DZEP_USE_SDL)

# Set this to get the default file system
target_compile_definitions(zep_imgui PRIVATE -DZEP_FEATURE_CPP_FILE_SYSTEM)

target_include_directories(zep_imgui
    PUBLIC
    include
    config
)

target_link_libraries(zep_imgui PUBLIC imgui SDL2 Zep)
