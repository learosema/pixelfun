#include <iostream>
#include <exception>
#include "quickjspp.hpp"

#include "application.h"

using namespace std;

int main(int argc, char* argv[])
{
	Application app;
	try {
		return app.load(std::string(argc == 2 ? argv[1] : ""));

	}
	catch (exception &e)
	{
		cerr << e.what() << endl;
		return 1;
	}
	catch (qjs::exception &e) {
		cerr << (std::string)qjs::Value(e.get()) << endl;
		return 1;
	}

}
