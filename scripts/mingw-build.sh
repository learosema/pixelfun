#!/bin/sh
mkdir -p build/release

cmake --preset release -DCMAKE_TOOLCHAIN_FILE=./cmake/x86_64-w64-mingw32.cmake .
cd build/release
ninja
