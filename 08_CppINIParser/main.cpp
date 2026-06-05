#include "INIpp.hpp"

#include <iostream>

int main()
{
	using namespace INIpp;

	DOM::Section section("MyDummySection");
	section.Append("key1", DOM::KeyValuePair("name", "Petko"));
	section.Append("key2", DOM::KeyValuePair("workplace", "Organizatsiya na Chodovishtata i Zlodeite"));
	section.Append("key3", DOM::KeyValuePair("homeplace", "13, Mecho Rukspin street, Montana State"));


	std::cout << "\n-------- K/V of " << section.SectionName() << " -------" << std::endl;
	for (auto& key : section.Keys())
	{
		std::cout << key << ": " << section[key].KeyName() << " = " << section[key].KeyValue() << std::endl;
	}

	std::cout << "\nHello World! INI Cpp Parser..." << std::endl;

	return 0;
}

