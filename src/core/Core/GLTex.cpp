#include "GLTex.hpp"
#include <iostream>

#include "Core/Log.hpp"

GLTex::GLTex(uint32_t width, uint32_t height, uint8_t channels)
{
    _width = width;
    _height = _height;
    _channels = channels;
    _data = std::make_unique<uint8_t[]>(_width * _height * _channels);

    glGenTextures(1, &_texture);
    APP_DEBUG(_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Setup Texture Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    update();
}

GLTex::~GLTex()
{
    glDeleteTextures(1, &_texture);
}

void GLTex::update()
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data.get());
}

void GLTex::resize(uint16_t width, uint16_t height) {
    _width = width;
    _height = height;
    _data.reset();
    _data = std::make_unique<uint8_t[]>(_width * _height * _channels);
}
