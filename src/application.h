#pragma once
#include <iostream>
#include <exception>

#include <SDL.h>

#include <SDL2pp/SDL2pp.hh>

#include <quickjs.h>

using namespace SDL2pp;


typedef std::function<std::vector<double> (int, int, double)> pxfun_t;
typedef std::function<void(double)> framefun_t;
typedef std::function<void()> setupfun_t;

class Application
{
public:
	Application(size_t width = 16, size_t height = 10);

	int load(const std::string& path);

	int run(const std::string& code, const std::string& path = "<eval>");

private:
	void update(const pxfun_t& fun);

	std::string readFile(const std::string &path);

	size_t _width = 320;
	size_t _height = 200;

	std::shared_ptr<SDL> _sdl;
	std::shared_ptr<Window> _window;
	std::shared_ptr<Renderer> _renderer;
	std::shared_ptr<Texture> _texture;
};
