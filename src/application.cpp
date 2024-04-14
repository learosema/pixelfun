#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "application.h"
#include "quickjspp.hpp"

Application::Application(size_t width, size_t height)
{
	_width = width;
	_height = height;
	_sdl = std::make_shared<SDL>(SDL_INIT_VIDEO);

	_window = std::make_shared<Window>("pixelfun",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 400,
		SDL_WINDOW_RESIZABLE
	);

	_renderer = std::make_shared<Renderer>(*_window, -1, SDL_RENDERER_ACCELERATED);

	_texture = std::make_shared<Texture>(*_renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, _width, _height);
}

int Application::load(const std::string &path)
{
	std::string code = (path.length() > 0) ? readFile(path) : "";

	return run(code, path);
}

int Application::run(const std::string &code, const std::string& path)
{
    qjs::Runtime runtime;
    qjs::Context context(runtime);
	context.eval(R"script(
		const WIDTH = 320;
		const HEIGHT = 200;
	)script");

	context.eval(R"script(
		function pixelfun(x, y, t) {
			return [255, 0, 0];
		}
	)script");

	if (code.length() > 0) {
		context.eval(code, path.c_str());
	}

	pxfun_t pxfun = (pxfun_t) context.eval("pixelfun");

	while (1)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				return 0;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
				case SDLK_q:
					return 0;
				}
			}
		}

		_renderer->Clear();
		update(pxfun);

		_renderer->Copy(*_texture);
		_renderer->Present();

		SDL_Delay(1000 / 60);
	}

	return 0;
}

void Application::update(const pxfun_t& fun) {
	auto ticks = SDL_GetTicks() >> 4;
	auto lock = _texture->Lock();
	Uint8* pixels = (Uint8*)lock.GetPixels();
	for (Uint16 y = 0; y < _height; y++) {
		for (Uint16 x = 0; x < _width; x++) {

			Uint16 i = y * _width + x;
			double ticks = SDL_GetTicks() / 1000.0;
			auto color = fun(x, y, ticks);
			pixels[i * 4 + 0] = static_cast<uint8_t>(std::floor(color[0]));
			pixels[i * 4 + 1] = static_cast<uint8_t>(std::floor(color[1]));
			pixels[i * 4 + 2] = static_cast<uint8_t>(std::floor(color[2]));
			pixels[i * 4 + 3] = 255;
		}
	}
}

std::string Application::readFile(const std::string& path)
{
    std::stringstream str;
    std::ifstream stream(path.c_str());
    if(stream.is_open())
    {
        while(stream.peek() != EOF)
        {
            str << (char) stream.get();
        }
        stream.close();
    }
	return str.str();
}

