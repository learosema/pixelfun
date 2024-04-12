#include <cstdint>

struct ICanvas {
	virtual void putpixel(uint16_t x, uint16_t y) = 0;
};
