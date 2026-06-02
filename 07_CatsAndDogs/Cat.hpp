#pragma once

#include "Pet.hpp"

namespace PetManager
{
	class Cat : public Pet			// Inherite the data from main class Pet
	{
		public:
			using Pet::Pet;			// Usging the constructor from the main class Pet
			//~Cat()
			//{
			//	std::cout << "Destroying a cat...\n";
			//}

			std::string_view GetKind() const noexcept override
			{
				return "Cat";
			} // this is virtual function in the parrent class (Pet), indicated with "override"

	};
}
