#include <iostream>
#include <exception>

#include <SDL.h>
// #include <SDL_image.h>

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;


void fillTexture(Texture &tex)
{
	auto ticks = SDL_GetTicks() >> 2;
	auto lock = tex.Lock();
	Uint8* pixels = (Uint8*)lock.GetPixels();
	for (Uint16 y = 0; y < 200; y++) {
		for (Uint16 x = 0; x < 320; x++) {
			Uint16 i = y * 320 + x;
			pixels[i * 4 + 0] = ticks + (x * 255 / 319);
			pixels[i * 4 + 1] = (Uint8)((ticks) & 255);
			pixels[i * 4 + 2] = 0;
			pixels[i * 4 + 3] = 255;
		}
	}
}

int main()
try
{
	// Initialize SDL library
	SDL sdl(SDL_INIT_VIDEO);

	// Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
	Window window("SDL2pp demo",
				  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				  640, 400,
				  SDL_WINDOW_RESIZABLE);

	// Create accelerated video renderer with default driver
	Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

	Texture vram(renderer, SDL_PIXELFORMAT_ARGB8888,
				 SDL_TEXTUREACCESS_STREAMING, 320, 200);

	// Main loop
	while (1)
	{
		// Event processing:
		// - If window is closed, or Q or Escape buttons are pressed,
		//   quit the application
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

		int vcenter = renderer.GetOutputHeight() / 2; // Y coordinate of window center

		// Clear screen
		renderer.Clear();
		fillTexture(vram);
		renderer.SetTarget(vram);

		renderer.SetDrawColor(Color(255, 255, 255));
		renderer.DrawPoint(Point(100, 100));
		renderer.DrawLine(Point(0,0), Point(320,200));
		renderer.SetTarget();
		renderer.Copy(vram);
		// Show rendered frame
		renderer.Present();

		// Frame limiter: sleep for a little bit to not eat 100% of CPU
		SDL_Delay(1000 / 60);
	}

	// Here all resources are automatically released and library deinitialized
	return 0;
}
catch (std::exception &e)
{
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	return 1;
}
