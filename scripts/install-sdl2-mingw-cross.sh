#!/bin/sh
SDL_VERSION=2.30.2
SDL_IMAGE_VERSION=2.8.2

cd $(dirname $0)
cd ..
ROOT_DIR=$(pwd)
DEST=${ROOT_DIR}/vendor/mingw

mkdir -p ${DEST}
echo "Prebuilt libraries for cross compilation to mingw" > ${DEST}/README.md
curl -s -L https://github.com/libsdl-org/SDL/releases/download/release-${SDL_VERSION}/SDL2-devel-${SDL_VERSION}-mingw.tar.gz | tar xvzf - -C ${DEST}
curl -s -L https://github.com/libsdl-org/SDL_image/releases/download/release-${SDL_IMAGE_VERSION}/SDL2_image-devel-${SDL_IMAGE_VERSION}-mingw.tar.gz | tar xvzf - -C ${DEST}

mkdir -p /usr/local/i686-w64-mingw32 /usr/local/x86_64-w64-mingw32
if test -d /usr/local/x86_64-w64-mingw32/bin/SDL2.dll; then
	echo "Found a mingw32 SDL2.dll installed, skipping make cross"
else
	cd ${DEST}/SDL2-${SDL_VERSION}
	make cross
	cd ${ROOT_DIR}
fi

if test -d /usr/local/x86_64-w64-mingw32/bin/SDL2_image.dll; then
	echo "Found a mingw32 SDL2_image.dll installed, skipping make cross"
else
	cd ${DEST}/SDL2_image-${SDL_IMAGE_VERSION}
	make cross
	cd ${ROOT_DIR}
fi
