#pragma once
#include <iostream>
#include <exception>

#include <SDL.h>
// #include <SDL_image.h>

#include <SDL2pp/SDL2pp.hh>

#include <quickjs.h>

using namespace SDL2pp;


typedef std::function<std::vector<uint8_t> (int, int, double)> pxfun_t;


class Application
{
public:
	int run();

private:
	void update(Texture& texture, const pxfun_t& fun);

	std::string readFile(const std::string &path);

};
