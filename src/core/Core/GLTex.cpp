#include "GLTex.hpp"
#include <iostream>
#include <cstdio>
#include "Core/Log.hpp"

GLTex::GLTex(uint32_t width, uint32_t height)
{
    _width = width;
    _height = height;
    _channels = 4;
    _data = (uint8_t *)malloc(sizeof(uint8_t) * _width * _height * _channels);
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Setup Texture Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    update();
}

GLTex::~GLTex()
{
    free(_data);
    glDeleteTextures(1, &_texture);
}

void GLTex::update()
{
        // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);
}

void GLTex::resize(uint16_t width, uint16_t height) {
    _width = width;
    _height = height;
    delete _data;
    _data = new uint8_t[_width * _height * _channels];
}
