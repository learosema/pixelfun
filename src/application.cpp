#include <sstream>
#include <iostream>
#include <fstream>

#include "application.h"
#include "quickjspp.hpp"

int Application::run()
{

    qjs::Runtime runtime;
    qjs::Context context(runtime);


	context.eval(R"script(

		const WIDTH = 320;
		const HEIGHT = 200;

	)script");

	context.eval(R"script(

		function pixelfun(x, y, t) {
			return [255, ((t*500+x*y)&255)|0, 255];
		}

	)script");

	pxfun_t pxfun = (pxfun_t) context.eval("pixelfun");

	SDL sdl(SDL_INIT_VIDEO);

	Window window("pixelfun",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 400,
		SDL_WINDOW_RESIZABLE
	);

	Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

	Texture texture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, 320, 200);

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

		renderer.Clear();
		update(texture, pxfun);

		renderer.Copy(texture);
		renderer.Present();

		SDL_Delay(1000 / 60);
	}

	return 0;
}

void Application::update(Texture& texture, const pxfun_t& fun) {
	auto ticks = SDL_GetTicks() >> 4;
	auto lock = texture.Lock();
	Uint8* pixels = (Uint8*)lock.GetPixels();
	for (Uint16 y = 0; y < 200; y++) {
		for (Uint16 x = 0; x < 320; x++) {

			Uint16 i = y * 320 + x;
			double ticks = SDL_GetTicks() / 1000.0;
			auto color = fun(x, y, ticks);
			pixels[i * 4 + 0] = color[0];
			pixels[i * 4 + 1] = color[1];
			pixels[i * 4 + 2] = color[2];
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

