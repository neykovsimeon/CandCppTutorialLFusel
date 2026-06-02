#include "SimpleCppApp.hpp"

#include <iostream>
#include <stdexcept>


int main()  noexcept
{
	try
	{
		return SimpleCppApp::SaveMain();
	}
	catch (const std::exception& ex)
	{
		std::cout << "Exception occured: " << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknowns exception occured! " << std::endl;
	}

	return -1;
}


