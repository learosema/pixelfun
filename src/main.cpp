#include <iostream>
#include <exception>

#include "application.h"

using namespace std;

int main(int argc, char* argv[])
try
{
	Application app;

	return app.load(std::string(argc == 2 ? argv[1] : ""));
}
catch (exception &e)
{
	cerr << e.what() << endl;
	return 1;
}
