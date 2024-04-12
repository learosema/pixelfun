#pragma once
#include <iostream>
#include <exception>

#include <SDL.h>

#include <SDL2pp/SDL2pp.hh>

#include <quickjs.h>

using namespace SDL2pp;


typedef std::function<std::vector<double> (int, int, double)> pxfun_t;
typedef std::function<void(double)> framefun_t;
typedef std::function<void()> setupfun_t;

class Application
{
public:
	int load(const std::string& path);

	int run(const std::string& code);

private:
	void update(Texture& texture, const pxfun_t& fun);

	std::string readFile(const std::string &path);

};
