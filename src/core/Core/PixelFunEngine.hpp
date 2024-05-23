#pragma once

#include <iostream>
#include <quickjs.h>

#include "Core/GLTex.hpp"
#include "Core/quickjspp.hpp"

typedef std::function<std::vector<double> (int, int, double)> pxfun_t;

class PixelFunEngine
{
public:
    explicit PixelFunEngine(const uint16_t width, const uint16_t height);
    virtual ~PixelFunEngine();

    void runScript(const std::string& javascript);

    void frame();
    void resize(const uint16_t width, const uint16_t height);

    inline GLuint getTextureId() const { return _texture->getTexture(); }

private:
    uint16_t _width;
    uint16_t _height;
    std::unique_ptr<GLTex> _texture = nullptr;
    std::unique_ptr<qjs::Runtime> _runtime = nullptr;
	std::unique_ptr<qjs::Context> _context = nullptr;
};
