#pragma once

#include "Pet.hpp"

namespace PetManager
{
	class Cat : 
		public Pet, 
		public Pet::ToyInteractable
	{
		public:
			using Pet::Pet;									// Usging the constructor from the main class Pet

			std::string_view GetKind() const noexcept override
			{
				return "Cat";
			} // this is virtual function in the parrent class (Pet), indicated with "override"

			std::string Interact(Toy& toy) override
			{ 
				if (dynamic_cast<ToyMouse*>(&toy))
				{
					return "Jump!";
				}
				else
				{
					return "Looks confused....";
				}
			}
	};
}
