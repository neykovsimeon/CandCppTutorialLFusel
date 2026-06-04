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
				Element(const T& data) :		// Copying something to the list
					storage(data)
				{}
				Element(T&& data) :		// Moving something to the list
					storage(std::move(data))
				{
				}

				Element* next = nullptr;
				Element* prev = nullptr;		// Adding features for double linked list, need to Iterator class
				T storage;
			};
		public:	
			class Iterator
			{
				public:
					Iterator() = default;
					Iterator(Element* element):
						m_element(element)
					{ }

					inline void Forward()
					{
						m_element = m_element->next;
					}
					inline void Backward()
					{
						m_element = m_element->prev;
					}
					inline T& Data()
					{
						return m_element->storage;
					}
					inline const T& Data() const
					{
						return m_element->storage;
					}
					T& operator*()
					{
						return Data();
					}
					const T& operator*() const
					{
						return Data();
					}

					friend bool operator==(const Iterator& lhs, const Iterator& rhs) 
					{
						return lhs.m_element == rhs.m_element;
					}
					Iterator& operator++()	// First increment, and return the incremented value
					{
						Forward();
						return *this;
					}
					Iterator operator++(int) // First store the old value, then increment. Return the old value
					{
						auto copy = *this;
						Forward();
						return copy;
					}
					Iterator& operator--()	// First decrement, and return the decremented value
					{
						Backward();
						return *this;
					}
					Iterator operator--(int) // First store the old value, then decrement. Return the old value
					{
						auto copy = *this;
						Backward();
						return copy;
					}

				private:
					Element* m_element = nullptr;
			};

		public:
			LinkedPetsList() = default;
			LinkedPetsList(const LinkedPetsList& other)			// Copy constructor
			{
				for (auto* element = other.m_first; element; element = element->next)
				{
					Append(element->storage);
				}
			}
			LinkedPetsList(LinkedPetsList&& other) noexcept: 	// Move constructor
				m_first(other.m_first), m_count(other.m_count)
			{
				other.m_first = nullptr;
				other.m_count = 0;
			}
			~LinkedPetsList()
			{
				Clear();
			}

			LinkedPetsList& operator=(const LinkedPetsList& other)				// copy version
			{
				if (this != &other)
				{
					this->~LinkedPetsList();
					new(this)LinkedPetsList(other);
				}
				return *this;
			}
			LinkedPetsList& operator=(LinkedPetsList&& other) noexcept			// move version
			{
				if (this != &other)
				{
					this->~LinkedPetsList();
					new(this)LinkedPetsList(std::move(other));
				}
				return *this;
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
				// TODO: check for valid object's data! 
				// Seek element at index
				Element** element = &m_first;
				for (size_t i = 0; i < index; i++)
				{
					element = &(*element)->next;
				}
				// Getting next pointer
				Element* next = (*element)->next;
				// Fix the backward link of the next element
				if (next)
				{
					next->prev = (*element)->prev;
				}
				// Deletion of the lement
				delete *element;
				// Fix the forward link to the element
				(*element) = next;

				m_count--;
			}
			void Clear()
			{
				Element* next;
				for (Element* element = m_first; element; element = next)
				{
					next = element->next;
					delete element;
				}
				m_first = nullptr;
				m_count = 0;
			}

			T& At(size_t index)					// Return the object's data (At) index position.
			{
				Element* element = m_first;
				for (size_t i = 0; i < index; i++)
				{
					element = element->next;
				} // Seeks the element At index position by going through.
				return element->storage;
				// TODO: check for valid object's data! 
			}
			
			const T& At(size_t index) const		// Return the object's data (At) index position.
			{
				Element* element = m_first;
				for (size_t i = 0; i < index; i++)
				{
					element = element->next;
				} // Seeks the element At index position by going through.
				return element->storage;
				// TODO: check for valid object's data! 
			}

			inline Iterator begin()
			{
				return Iterator(m_first);
			}
			inline Iterator end()
			{
				return Iterator();
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
					element->prev = *insertPosition; // Added feature used by Iterator class forming double linked list
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


