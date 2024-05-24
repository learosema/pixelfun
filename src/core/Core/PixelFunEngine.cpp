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
    _width = width;
    _height = height;
    _runtime = std::make_shared<qjs::Runtime>();
    _texture = std::make_shared<GLTex>(width, height);
    runScript("");
}

PixelFunEngine::~PixelFunEngine()
{

}

void PixelFunEngine::runScript(const std::string &javascript)
{
    _context.reset();
    _context = std::make_shared<qjs::Context>(*(_runtime.get()));
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
/**
 * Cosine based palette, 4 vec3 params
 * @see https://iquilezles.org/articles/palettes/
 * @param {float} t a parameter between 0..1 (can be bigger, lower but repeats)
 * @param {[number, number, number]} a first vector
 * @param {[number, number, number]} b second vector
 * @param {[number, number, number]} c third vector
 * @param {[number, number, number]} d fourth vector
 * @returns {[number, number, number]} an RGB value
 */
function palette(t, a, b, c, d)
{
	const twoPI = 2 * Math.PI;
	return [
		a[0] + b[0] * Math.cos(twoPI * (c[0] * t + d[0])),
		a[1] + b[1] * Math.cos(twoPI * (c[1] * t + d[1])),
		a[2] + b[2] * Math.cos(twoPI * (c[2] * t + d[2]))
	].map(val => Math.round(val*255));
}

function twilight(t) {
	return palette(t,
		[0.5, 0.5, 0.5],
		[0.5, 0.5, 0.5],
		[2.0, 1.0, 0.0],
		[0.5, 0.2, 0.25]
	);
}

function pixelfun(x, y, t) {
	const { sin, cos } = Math;
	const i = 0.5+0.5*sin(x*0.5 + t);
	const j = 0.5+0.5*cos(y*0.5 + t);

	return twilight(t * 0.2 + i*j);
}

	)script");
    _context->eval(javascript + ";globalThis.pixelfun = pixelfun;", "<main>", JS_EVAL_TYPE_MODULE);
}

void PixelFunEngine::frame()
{
	pxfun_t pxfun = static_cast<pxfun_t>(_context->eval("pixelfun"));
	double ticks = SDL_GetTicks() / 1000.0;
    assert(_texture != nullptr);
	auto pixels = _texture->getPixels();
	for (uint16_t y = 0; y < _height; y++) {
		for (uint16_t x = 0; x < _width; x++) {

			uint16_t i = (y * _width + x);
			auto color = pxfun(x, y, ticks);
			pixels[i * 4 + 0] = static_cast<uint8_t>(std::floor(color[2]));
			pixels[i * 4 + 1] = static_cast<uint8_t>(std::floor(color[1]));
			pixels[i * 4 + 2] = static_cast<uint8_t>(std::floor(color[0]));
			pixels[i * 4 + 3] = 255;
		}
	}
    _texture->update();
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
