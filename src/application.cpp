#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "application.h"
#include "quickjspp.hpp"

Application::Application(size_t width, size_t height)
{
	m_width = width;
	m_height = height;
	m_pSDL = std::make_shared<SDL>(SDL_INIT_VIDEO);

	m_pWindow = std::make_shared<Window>("pixelfun",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 400,
		SDL_WINDOW_RESIZABLE
	);

	m_pRenderer = std::make_shared<Renderer>(*m_pWindow, -1, SDL_RENDERER_ACCELERATED);

	m_pTexture = std::make_shared<Texture>(*m_pRenderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, m_width, m_height);
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

		m_pRenderer->Clear();
		update(pxfun);

		m_pRenderer->Copy(*m_pTexture);
		m_pRenderer->Present();

		SDL_Delay(1000 / 60);
	}

	return 0;
}

void Application::update(const pxfun_t& fun) {
	auto ticks = SDL_GetTicks() >> 4;
	auto lock = m_pTexture->Lock();
	Uint8* pixels = (Uint8*)lock.GetPixels();
	for (Uint16 y = 0; y < 200; y++) {
		for (Uint16 x = 0; x < 320; x++) {

			Uint16 i = y * 320 + x;
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

