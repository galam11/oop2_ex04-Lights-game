#include "Controller.h"
#include <iostream>


int main() try
{
	Controller controller;


	controller.run();
	return 0;
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
	return 1;
}
catch (...)
{
	std::cerr << "An unknown error occurred." << std::endl;
	return 1;
}