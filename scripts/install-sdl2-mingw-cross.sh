#!/bin/sh
SDL_VERSION=2.30.2
SDL_IMAGE_VERSION=2.8.2
DEST=vendor/mingw

mkdir -p ${DEST}
echo "Prebuilt libraries for cross compilation to mingw" > ${DEST}/README.md
curl -s -L https://github.com/libsdl-org/SDL/releases/download/release-${SDL_VERSION}/SDL2-devel-${SDL_VERSION}-mingw.tar.gz | tar xvzf - -C ${DEST}
curl -s -L https://github.com/libsdl-org/SDL_image/releases/download/release-${SDL_IMAGE_VERSION}/SDL2_image-devel-${SDL_IMAGE_VERSION}-mingw.tar.gz | tar xvzf - -C ${DEST}

# mkdir -p /usr/local/i686-w64-mingw32 /usr/local/x86_64-w64-mingw32
# cd mingw/SDL2-${SDL_VERSION}
# make cross

# cd ../SDL2_image-${SDL_IMAGE_VERSION}
# make cross
