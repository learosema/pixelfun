#pragma once
#include <iostream>
#include <exception>

#include <SDL.h>
// #include <SDL_image.h>

#include <SDL2pp/SDL2pp.hh>

#include <quickjs.h>

using namespace SDL2pp;

class Application
{
public:
	int run();

private:
	void update(Texture& texture);

	std::string readFile(std::string path);
};
