#include "PixelFunEngine.hpp"
#include "GLTex.hpp"
#include <SDL.h>
#include <fmt/format.h>

void consoleLog(qjs::rest<qjs::Value> args) {
    for (qjs::Value arg : args) std::cout << arg.toJSON() << " ";
    std::cout << "\n";
}

PixelFunEngine::PixelFunEngine(const uint16_t width, const uint16_t height)
{
    _runtime = std::make_unique<qjs::Runtime>();
    _texture = std::make_unique<GLTex>(width, height);
}

PixelFunEngine::~PixelFunEngine()
{

}

void PixelFunEngine::runScript(const std::string &javascript)
{
    _context.reset();
    _context = std::make_unique<qjs::Context>(*(_runtime.get()));
	auto& console = _context->addModule("console");
	console.function<&consoleLog>("log");

	// import module
	_context->eval(R"script(
		import * as console from 'console';
		globalThis.console = console;
	)script", "<import>", JS_EVAL_TYPE_MODULE);

	_context->eval(fmt::format(R"script(
		let WIDTH = {};
		let HEIGHT = {};
	)script", _width, _height));

	_context->eval(R"script(
		function pixelfun(x, y, t) {
			return [255, 0, 0];
		}
	)script");
    _context->eval(javascript + ";globalThis.pixelfun = pixelfun;", "<main>", JS_EVAL_TYPE_MODULE);
}

void PixelFunEngine::frame()
{
	pxfun_t pxfun = static_cast<pxfun_t>(_context->eval("pixelfun"));
	double ticks = SDL_GetTicks() / 1000.0;

	auto pixels = _texture->getPixels();
	for (Uint16 y = 0; y < _height; y++) {
		for (Uint16 x = 0; x < _width; x++) {
			Uint16 i = y * _width + x;
			auto color = pxfun(x, y, ticks);
			pixels[i * 4 + 0] = static_cast<uint8_t>(std::floor(color[2]));
			pixels[i * 4 + 1] = static_cast<uint8_t>(std::floor(color[1]));
			pixels[i * 4 + 2] = static_cast<uint8_t>(std::floor(color[0]));
			pixels[i * 4 + 3] = 255;
		}
	}
}

void PixelFunEngine::resize(const uint16_t width, const uint16_t height)
{
    _texture->resize(width, height);
    _width = width;
    _height = height;
    _context->eval(fmt::format(R"script(
        width = {}; height = {};
    )script", width, height));
}
