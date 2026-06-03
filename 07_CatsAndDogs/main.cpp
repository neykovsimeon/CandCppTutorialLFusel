#include "Cat.hpp"
#include "Dog.hpp"

#include <iostream>

int main()
{
	using namespace PetManager;

	Dog bruno("Bruno");
	Cat pifka("Pifka");
	Cat oscar("Oscar");

	ToyBone bone;
	ToyMouse mouse;

	std::cout << "Playing with our pets:...." << std::endl;
	std::cout << bruno.GetName() << " gets the bone: "	<< bruno.Interact(bone)	 << std::endl;
	std::cout << pifka.GetName() << " gets the mouse: " << pifka.Interact(mouse) << std::endl;
	std::cout << oscar.GetName() << " gets the bone: "	<< oscar.Interact(bone)  << std::endl;
	
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

