#include "INIpp.hpp"

#include <iostream>

int main()
{
	std::cout << "Hello World! INI Cpp Parser...\n" << std::endl;

	INIpp::DOMParser parser;
	parser.AddFile("./my_config.ini");

	INIpp::DOM::Document doc = parser.Get();

	std::cout << "database/server IP: " << doc["database"]["server"].KeyValue() << ";" << std::endl;

	int port = doc["database"]["port"].Get<int>();
	std::cout << "database/port <int>: " << port << ";" << std::endl;

	std::string owner = doc["owner"]["name"].Get<std::string>();
	std::cout << "owner/name <string>: " << owner << ";" << std::endl;

	return 0;
}

