#include <cstdint>

#include "color.hpp"

class ICanvas {
	virtual void putpixel(uint16_t x, uint16_t y, const Color& color) = 0;
	virtual void moveTo(uint16_t x, uint16_t y) = 0;
	virtual void lineTo(uint16_t x, uint16_t y, const Color& color) = 0;
	virtual void rect(uint16_t x, uint16_t y, size_t w, size_t h) = 0;
	virtual void fillRect(uint16_t x, uint16_t y, size_t w, size_t h) = 0;
	virtual void ellipse(uint16_t x, uint16_t y, size_t w, size_t h) = 0;
	virtual void fillEllipse(uint16_t x, uint16_t y, size_t w, size_t h) = 0;
};
