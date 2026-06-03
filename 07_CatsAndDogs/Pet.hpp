#pragma once

#include "Toy.hpp"
#include "IInteractable.hpp"

#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <stdexcept>

namespace PetManager
{
	class Pet
	{
		public:
			using ToyInteractable = IInteractable<std::string, Toy&>;  // Using an alias	
		public:
			Pet() = default;
			Pet(const std::string_view& name);
			virtual ~Pet() = default;

			void Lived();
			void Died();

			virtual std::string_view GetKind() const noexcept
			{
				return "Pet";
			} 
			inline const std::string& GetName() const noexcept
			{
				return m_name;
			}
			inline bool GetLivingStatus() const noexcept
			{
				return m_living;
			}
			inline size_t GetAge() const noexcept
			{
				return m_ageInDays;
			}


		private:
			std::string m_name;
			bool m_living = true;
			size_t m_ageInDays = 0;
	};
}

std::ostream& operator<<(std::ostream& os, const PetManager::Pet& pet);


