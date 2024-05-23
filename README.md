# PixelFun

PixelFun is a JavaScript playground for creative development. It is a standalone application
Basically it is QuickJS + SDL2 = PixelFun.

## Prerequisites

First things first, remember to also check out submodules:

```sh
git clone --recurse-submodules git@github.com:learosema/pixelfun.git
```

## Dependencies

Pixelfun uses the CMake meta build system, and optionally ninja (make as fallback). Additionally, it requires the SDL2 development files installed on the system.

```sh
# Mac
brew install cmake ninja sdl2 sdl2_image

# Linux
sudo apt install cmake ninja-build libsdl2-dev libsdl2-image-dev`

# Windows is untested, sorry
```

## Build instructions

```sh
# Create makefile
cmake --preset release

# Build project
cmake --build build/release
```

## Cross compilation to Windows (via MingW)

I'm providing a cmake toolchain file for MingW.

To install the mingw toolchain on a Mac, run: `brew install mingw-w64` (or Linux `sudo apt install mingw-w64`).

To install the SDL2 binaries, I'm providing an install script (`scripts/install-sdl2-mingw-cross.sh`).

You can cross compile it from osx or linux via `scripts/mingw-build.sh`.

All this stuff is still new to me, I haven't done non-web-development (C++) for decades.

## Usage

Create a function `pixelfun()` that returns a color at a given tick time, and save it inside a javascript file:

```js
function pixelfun(x,y,t) {
  const red = 255;
  const green = (x * 255 / WIDTH)|0;
  const blue = (y * 255 / HEIGHT)|0;
  return [red, green, blue];
}
```

Then, run it:

```sh
pixelfun pixelfun.js
```

Enjoy 💖



## Attributions

PixelFun wouldn't be possible without these:

- [CMake](https://cmake.org)
- [Ninja](https://ninja-build.org/)
- [SDL2](https://libsdl.org)
- [QuickJS](https://bellard.org/quickjs/)
- [QuickJSpp](https://github.com/ftk/quickjspp/)
- [libSDL2pp](https://github.com/libSDL2pp/libSDL2pp)
