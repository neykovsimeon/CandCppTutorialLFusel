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

	LinkedPetsList<Pet*> pets;;
	pets.Append(&bruno);
	pets.Append(&pifka);
	pets.Append(&oscar);
	pets.Append(&rex);
	pets.Append(&pisan);

	LinkedPetsList<Pet*> second = pets;				// Example operator '=' overloaded
	LinkedPetsList<Pet*> third(pets);				// Example copy constructor: new is third, old stays active: pets
	LinkedPetsList<Pet*> moved(std::move(pets));	// Example move constructor: new is moved, pets becomes empty

	//for (auto it = pets.begin(); !(it == pets.end()); it++)
	//{
	//	std::cout << "Pets before erase: " << *it.Data() << std::endl;
	//}
	//std::cout << std::endl;

	//for (auto it = pets.begin(); !(it == pets.end()); it++)
	//{
	//	std::cout << "Pets before erase: " << **it << std::endl; 
	//}	// Only < *it >  will print tjust addresses. Double de-referenciation < **it > gives the Data
	//std::cout << std::endl;

	// Exampke intro to the range loop:
	//int x[8] = { 2, 4, 6, 8, 10, 12, 14, 16 };
	//for (int i = 0; i < 8; i++) std::cout << "A) " << x[i] << std::endl;
	//for (int i : x)				std::cout << "B) " <<	i  << std::endl;
	for (const Pet* pet : moved)
	{
		std::cout << "Pets before erase: " << *pet << std::endl;
	}
	std::cout << std::endl;

	moved.Erase(2);
	for (const Pet* pet : moved)
	{
		std::cout << "Pets after erase: " << *pet << std::endl;
	}
	std::cout << std::endl;

	std::cout << "First Pet: "  << *pets.At(0) << std::endl;
	std::cout << "Second Pet: " << *pets.At(1) << std::endl;
	std::cout << "Third Pet: "  << *pets.At(2) << std::endl << std::endl;

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
	bruno.Died();

	std::cout << bruno << std::endl;
	std::cout << oscar << std::endl;
	std::cout << pifka << std::endl;

	
	std::cout << "\nHello World! Cats and Dogs...\n";

	return 0;
}

