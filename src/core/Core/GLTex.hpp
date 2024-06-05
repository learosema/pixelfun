#pragma once
#include <cstdint>
#include <iostream>
#include <glad/glad.h>


#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

class GLTex {

public:
    explicit GLTex(uint32_t width, uint32_t height);
    virtual ~GLTex();

    inline uint8_t* getPixels() const { return _data; }
    inline GLuint   getTexture() const { return _texture; }

    void update();
    void resize(uint16_t width, uint16_t height);
private:
    GLuint _texture;
    uint32_t _width;
    uint32_t _height;
    uint8_t _channels;
    uint8_t* _data;
};
