#!/bin/sh
mkdir -p build
cd build

cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/x86_64-w64-mingw32.cmake ..
make

