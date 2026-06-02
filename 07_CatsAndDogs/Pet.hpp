#pragma once

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
			Pet() = default;
			Pet(const std::string_view& name);
			virtual ~Pet() = default;
			//{
			//	std::cout << "Destroying a pet...\n";
			//}	// "virtual" supports to call the destructor when chaild class is created as a pointer, 
			//	// like: Pet* pt = new Cat("Pifa");

			void Lived();
			void Died();

			virtual std::string_view GetKind() const noexcept
			{
				return "Pet";
			} // child classes have to implement the function for themselves

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


