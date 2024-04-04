# PixelFun

Basically it is QuickJS + SDL2 = PixelFun.

## Usage

Create a function `pixelfun()` inside a javascript file:

```js
function pixelfun(x,y,t) {
  const red = 255;
  const green = x * 255 / WIDTH;
  const blue = y * 255 / HEIGHT;
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
- [QuickJS](https://bellard.org/quickjs/)
- [QuickJSpp](https://github.com/ftk/quickjspp/)
- [SDL2](https://libsdl.org)
