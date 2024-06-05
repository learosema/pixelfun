#pragma once
#include <cstdint>
#include <iostream>

class Color {

public:
	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) {
		m_red = red;
		m_green = green;
		m_blue = blue;
		m_alpha = alpha;
	}

	inline uint8_t red() const { return m_red; }

	inline uint8_t green() const { return m_red; }

	inline uint8_t blue() const { return m_blue; }

	inline uint8_t alpha() const { return m_blue; }

private:
	uint8_t m_red;
	uint8_t m_green;
	uint8_t m_blue;
	uint8_t m_alpha;
};
