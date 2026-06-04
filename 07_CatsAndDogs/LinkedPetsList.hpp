#pragma once

#include "Pet.hpp"


namespace PetsList
{
	template<typename T>
	class LinkedPetsList
	{
		private:
			struct Element
			{
				Element() = delete;
				Element(const T& data) : // copying something to the list
					storage(data)
				{}
				Element(const T&& data) : // moving something to the list
					storage(std::move(data))
				{
				}

				Element* next = nullptr;
				T storage;
			};
			
		public:
			~LinkedPetsList()
			{
				Element* next = nullptr;
				for (Element* element = m_first; element; element = next)
				{
					next = element->next;
					delete element;
				}
			}
			void Append(const T& element)			// copy version of Append() function
			{
				AppendElement(new Element(element));
			}

			void Append(T&& element)				// Move version og Append() function
			{
				AppendElement(new Element(std::move(element)));
			}

			void Erase(size_t index)
			{
				Element** element = &m_first;
				for (size_t i = 0; i < index; i++)
				{
					element = &(*element)->next;
				}// Seeks the element At index position by going through.
				Element* next = (*element)->next;
				delete *element;
				(*element) = next;
				m_count--;
			}

			T& At(size_t index)					// Return the object's data (At) index position.
			{
				Element* element = m_first;
				for (size_t i = 0; i < index; i++)
				{
					element = element->next;
				} // Seeks the element At index position by going through.
				return element->storage;
			}
			
			const T& At(size_t index) const		// Return the object's data (At) index position.
			{
				Element* element = m_first;
				for (size_t i = 0; i < index; i++)
				{
					element = element->next;
				} // Seeks the element At index position by going through.
				return element->storage;
			}

			inline size_t Count() const noexcept
			{
				return m_count;
			}

			inline T& operator[](size_t index)
			{
				return At(index);
			}
			inline const T& operator[](size_t index) const
			{
				return At(index);
			}

		private:
			void AppendElement(Element* element)
			{
				Element** insertPosition = &m_first;
				while (*insertPosition)
				{
					insertPosition = &(*insertPosition)->next;
				}
				*insertPosition = element;
				m_count++;
			}
		
		private:
			struct Element* m_first = nullptr;
			size_t m_count = 0;

	};
}


