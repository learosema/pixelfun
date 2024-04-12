#include "sdlrenderer.h"

SDLRenderer::SDLRenderer(size_t width, size_t height)
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

void SDLRenderer::update()
{
	/*
	renderer.Clear();
	update(texture, pxfun);

	renderer.Copy(texture);
	renderer.Present();

	SDL_Delay(1000 / 60); */
}
