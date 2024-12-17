#include <iostream>
#include <exception>
#include "quickjspp.hpp"

#include "application.h"

int main(int argc, char* argv[])
{
	Application app;
	try {
		return app.load(std::string(argc == 2 ? argv[1] : ""));

	}
	catch (qjs::exception &e) {
		std::cerr << (std::string)qjs::Value(e.get()) << std::endl;
		return 1;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}
