#pragma once
#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "irenderer.h"

using namespace SDL2pp;

class SDLRenderer : IRenderer {
	SDLRenderer(size_t width = 320, size_t height = 200);
	virtual ~SDLRenderer();
	virtual void update();

private:
	size_t m_width = 320;
	size_t m_height = 200;
	SDL* m_pSDL = NULL;
	Window* m_pWindow = NULL;
	Renderer* m_pRenderer = NULL;
	Texture* m_pTexture = NULL;
};
