# PixelFun

Basically it is QuickJS + SDL2 = PixelFun.

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

## Build instructions

First things first, remember to also check out submodules:

```sh
git clone --recurse-submodules git@github.com:learosema/pixelfun.git
```

Pixelfun uses the CMake build system. Additionally, it requires the SDL2 development files installed on the system.

On a mac, the required dependencies can be installed via `brew install cmake sdl2 sdl2_image`. Build instructions on other platforms will follow.

On Linux: `apt install libsdl2-dev libsdl2-image-dev`

## Cross compilation to Windows (via MingW32)

I'm providing a cmake toolchain file for MingW32.
To install the SDL2 binaries, I'm providing an install script (`scripts/install-sdl2-mingw-cross.sh`).

You can cross compile it from osx or linux via `scripts/mingw-build.sh`.

All this stuff is still new to me, I haven't done non-web-development (C++) for decades.

## Attributions

PixelFun wouldn't be possible without these:

- [CMake](https://cmake.org)
- [SDL2](https://libsdl.org)
- [QuickJS](https://bellard.org/quickjs/)
- [QuickJSpp](https://github.com/ftk/quickjspp/)
- [libSDL2pp](https://github.com/libSDL2pp/libSDL2pp)
