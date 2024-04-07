#include "sdlrenderer.h"

SDLRenderer::SDLRenderer(size_t width, size_t height)
{
	m_width = width;
	m_height = height;
	m_pSDL = new SDL(SDL_INIT_VIDEO);

	m_pWindow = new Window("pixelfun",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 400,
		SDL_WINDOW_RESIZABLE
	);

	m_pRenderer = new Renderer(*m_pWindow, -1, SDL_RENDERER_ACCELERATED);

	m_pTexture = new Texture(*m_pRenderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, m_width, m_height);
}

SDLRenderer::~SDLRenderer()
{
	if (m_pTexture) delete m_pTexture;
	if (m_pRenderer) delete m_pRenderer;
	if (m_pWindow) delete m_pWindow;
	if (m_pSDL) delete m_pSDL;
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
