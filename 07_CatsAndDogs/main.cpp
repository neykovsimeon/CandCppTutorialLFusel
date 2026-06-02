#include "Pet.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

#include <iostream>

int main()
{
	using namespace PetManager;

	Dog bruno("Bruno");
	Cat pifka("Pifka");
	Pet oscar("Oscar");

	//Pet* pt = new Cat("Pifa"); 
	//delete pt; // Ensure both parrent and chaild destructurs are called: make the parrent destructor virtual

	//Pet* op = &oscar;
	//Cat* cbCat = dynamic_cast<Cat*>(op); // will return nulptr
	//Dog* cbDog = dynamic_cast<Dog*>(op); // will return normal pointer
	
	bruno.Lived(); oscar.Lived();
	bruno.Lived(); oscar.Lived();
	bruno.Lived(); oscar.Lived();
	bruno.Lived(); oscar.Lived();
	pifka.Lived(); pifka.Lived();
	pifka.Lived(); pifka.Lived();
	pifka.Lived(); pifka.Lived();
	pifka.Lived(); pifka.Lived();
	bruno.Died();

	std::cout << bruno << std::endl;
	std::cout << oscar << std::endl;
	std::cout << pifka << std::endl;

	
	std::cout << "\nHello World! Cats and Dogs...\n";

	return 0;
}

