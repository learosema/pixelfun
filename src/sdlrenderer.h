#pragma once
#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "irenderer.h"
#include "quickjsenv.h"

using namespace SDL2pp;

class SDLRenderer : IRenderer {
	SDLRenderer(size_t width = 320, size_t height = 200);

	virtual void update();

private:
	size_t m_width = 320;
	size_t m_height = 200;

	std::shared_ptr<SDL> m_pSDL;
	std::shared_ptr<Window> m_pWindow;
	std::shared_ptr<Renderer> m_pRenderer;
	std::shared_ptr<Texture> m_pTexture;
	std::shared_ptr<QuickJSEnv> m_pScript;
};
