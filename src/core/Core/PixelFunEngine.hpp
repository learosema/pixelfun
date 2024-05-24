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

    inline uint16_t getWidth() const { return _width; }
    inline uint16_t getHeight() const { return _height; }

private:
    uint16_t _width;
    uint16_t _height;
    std::shared_ptr<GLTex> _texture = nullptr;
    std::shared_ptr<qjs::Runtime> _runtime = nullptr;
	std::shared_ptr<qjs::Context> _context = nullptr;
};
