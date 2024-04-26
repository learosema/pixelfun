# PixelFun

Basically it is QuickJS + SDL2 = PixelFun.

Disclaimer: Sort of. Still very unstable. So maybe not too much fun.

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

Pixelfun uses the CMake build system. Additionally, it requires the SDL2 development files installed on the system.

On a mac, the required dependencies can be installed via `brew install cmake sdl2 sdl2_image`. Build instructions on other platforms will follow.

On Linux: `apt instal libsdl2-dev libsdl2-image-dev`

## Attributions

PixelFun wouldn't be possible without these:

- [CMake](https://cmake.org)
- [QuickJS](https://bellard.org/quickjs/)
- [QuickJSpp](https://github.com/ftk/quickjspp/)
- [SDL2](https://libsdl.org)
