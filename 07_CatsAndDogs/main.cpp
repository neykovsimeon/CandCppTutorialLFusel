#include "Cat.hpp"
#include "Dog.hpp"
#include "LinkedPetsList.hpp"

#include <iostream>

int main()
{
	using namespace PetManager;
	using namespace PetsList;

	Dog bruno("Bruno");
	Cat pifka("Pifka");
	Cat oscar("Oscar");
	Dog rex("Rex");
	Cat pisan("Pisan");

	LinkedPetsList<PetManager::Pet*> lpl;
	lpl.Append(&bruno);
	lpl.Append(&pifka);
	lpl.Append(&oscar);
	lpl.Append(&rex);
	lpl.Append(&pisan);

	for (size_t i = 0; i < lpl.Count(); i++)
	{
		std::cout << (i + 1) << ". pet before erase: " << *lpl[i] << std::endl;
	}
	std::cout << std::endl;

	lpl.Erase(2);
	for (size_t i = 0; i < lpl.Count(); i++)
	{
		std::cout << (i + 1) << ". pet after erase: " << *lpl[i] << std::endl;
	}
	std::cout << std::endl;

	std::cout << "First Pet: "  << *lpl.At(0) << std::endl;
	std::cout << "Second Pet: " << *lpl.At(1) << std::endl;
	std::cout << "Third Pet: "  << *lpl.At(2) << std::endl << std::endl;

	ToyBone bone;
	ToyMouse mouse;

	std::cout << "Playing with our pets:...." << std::endl;
	std::cout << bruno.GetName() << " gets the bone: "	<< bruno.Interact(bone)	 << std::endl;
	std::cout << pifka.GetName() << " gets the mouse: " << pifka.Interact(mouse) << std::endl;
	std::cout << oscar.GetName() << " gets the bone: "	<< oscar.Interact(bone)  << std::endl << std::endl;
	
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

