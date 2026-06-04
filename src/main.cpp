#include "Controller.h"
#include <iostream>
#include <fstream>
#include "Consts.h"

int main() try
{
	Controller controller;
	controller.run();
	return 0;
}
catch (const std::exception& e)
{
	std::ofstream ferr (ERR_FILE_PATH);
	ferr << e.what();
	ferr.close();
	return 1;
}
catch (...)
{
	std::cerr << "An unknown error occurred." << std::endl;
	return 1;
}