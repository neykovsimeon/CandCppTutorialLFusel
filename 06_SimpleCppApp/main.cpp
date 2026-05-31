#include <iostream>
#include <cstdint>
#include <cstring>
#include <cstdlib>

int32_t f(int32_t x)
{
	return x * x + 5 * x + 5; 
}

class FunctionPreCacher
{	
	public:		
		FunctionPreCacher() = default;
		// Constructor to create new object as a copy from another object: 
		FunctionPreCacher(const FunctionPreCacher& another)
		{			
			x = another.x;
			count = another.count;
			function = another.function;
			if (another.values)
			{
				values = new int32_t[another.count];
				if (values)
				{
					std::cout << "Allocate values with <<COPY>> from " << another.values << " to " << this->values << std::endl;
					std::memcpy(values, another.values, sizeof(int32_t) * another.count);
				}
			}
		}
		// The big five concept: plain copy of an object to "itself" (same object's pointer), leave with new name, destroys the old one
		// Constructor to create new object as an another/old object is "moved" into the new one: the source won't be a const anymore
		// "noexcept" means the function won't throw exceptions
		FunctionPreCacher(FunctionPreCacher&& another) noexcept						// double && used as a "move" semantic
		{
			x = another.x;
			count = another.count;
			function = another.function;
			values = another.values;

			another.values = nullptr;
		}
		// Proper customer constructor introduced here.
		FunctionPreCacher(int32_t x, uint32_t count, int32_t(*function)(int32_t)) 
		{
			Setup(x, count, function);
		}
		// Proper custom destructor introduced here.
		~FunctionPreCacher() 
		{
			Release();
		}

		// The Big three concept: "copy" type assign operator overload
		FunctionPreCacher& operator=(const FunctionPreCacher& another)
		{
			if (this != &another) // prevent self-assignment
			{
				this->~FunctionPreCacher();
				this->FunctionPreCacher::FunctionPreCacher(another);
			}
			return *this;
		}

		// The Big five concept: "move" type assign operator overload
		FunctionPreCacher& operator=(FunctionPreCacher&& another) noexcept
		{
			if (this != &another) // prevent self-assignment
			{
				this->~FunctionPreCacher();
				this->FunctionPreCacher::FunctionPreCacher(std::move(another));
			}
			return *this;
		}

		void Setup(int32_t x, uint32_t count, int32_t(*function)(int32_t))
		{
			Release();
			this->x = x;
			this->count = count;
			this->function = function;
		}

		FunctionPreCacher& Compute()
		{
			if (function && count > 0)
			{
				Release();
				values = new int32_t[count];
				if (values)
				{
					//std::cout << "Allocate values and Compute().." << this->values << std::endl;
					for (int32_t i = 1; i <= count; i++)
					{
						values[i - 1] = function(i * x); 
					}
				}
			}

			return *this;
		}

		void Release()
		{
			if (values)
			{
				//std::cout << "Delete values with Release().." << this->values << std::endl;
				delete[] values; // delete[] specifies we delete certain amount (count) of data -> delete an array
				values = nullptr;
			}
		}
		void PrintResult() const
		{
			if(values)
				for (int32_t i = 1; i <= count; i++)
				{
					std::cout << "f(" << i * x << ") = " << values[i - 1] << std::endl;
				}
			std::cout << std::endl;
		}

	private:
		int32_t* values = nullptr;
		int32_t x = 0;
		int32_t count = 0;
		int32_t(*function)(int32_t x) = nullptr;	
};

// Describe a container for FunctionPreCacher objects
class PreCacherContainer
{
	public:
		PreCacherContainer() = default;													// Default constructor

		// The big three: no specific implementation, because it is done in FunctionPreCasher class
		/*******************************************************************************************************************/
		PreCacherContainer(const PreCacherContainer&) = default;						// Default copy constructor
		~PreCacherContainer() = default;												// Default destructor

		PreCacherContainer& operator=(const PreCacherContainer&) = default;				// Default "copy" assign operator overload
		/*******************************************************************************************************************/
		// Added The Big five concept; "move" concept constructor and assign operator overload
		PreCacherContainer(PreCacherContainer&&) noexcept = default;					// Default "move" constructor - The Big five concept
		PreCacherContainer& operator=(PreCacherContainer&&) noexcept = default;			// Default "move" assign operator overload - The Big five concept

		void PrintResult() const
		{
			//std::cout << "Container at " << this << std::endl;
			for (int i = 0; i < m_usage; i++)
			{
				std::cout << "FunctionPreCacher #" << (i + 1) << std::endl;
				m_preCachers[i].PrintResult();
			}
		}
		// The Big three concept: Append with "copy" assignment, (const) object passed by reference
		void Append(const FunctionPreCacher& pc)
		{
			if (m_usage < 8)
			{
				m_preCachers[m_usage++] = pc; // m_usage would be frist taken with its old value, then assignment, then m_usage increment
			}
		}
		// The Big five concept: Append with "move" assignment, (no const) object passed by downble reference, noexcept
		void Append(FunctionPreCacher&& pc)
		{
			if (m_usage < 8)
			{
				m_preCachers[m_usage++] = std::move(pc); // m_usage would be first taken with its old value, then assignment, then m_usage increment
			}
		}

	
	private:
		FunctionPreCacher m_preCachers[8];
		int m_usage = 0;
};

int main()
{
	int32_t x;
	uint32_t count;
	std::cout << "Enter the starting value: ";
	std::cin >> x;
	std::cout << "Enter the itterations: ";
	std::cin >> count;

	PreCacherContainer cnt;						// Create a container for FunctionPreCacher objects

	// Intro to Big Five: Motivation why: Implementation as is now
	// 1. Creates the object with Compute (alocate an array for the values, etc)
	// 2. Appends the object into the container (with copy) - this is an allocation again for another memory block for the same object's values, etc
	// 3. While getting out from append function - destructs the original Computed object and we get left with the appended copy only
	// ===> this means we allocate memory twice to do work (Compute) once - like we store the Computed results twice, then destructs one of these
	// Solution to come to prevent the waste of memory: 
	// Include in your class member functions for "move" constructor and "move" assignment (while Big three comes with "copy" versions of these members)
	// The idea would be, that the new (copied/destinate) object, should actually steal the pointer to the old (source) object, the old object to be discarted.
	// This is already the case with copy, but we waste memory (allocate twice). The goal for "move" concept is to prevent the waste of memory
	cnt.Append(std::move(FunctionPreCacher(x, count, &f).Compute()));
	cnt.Append(std::move(FunctionPreCacher((x * 2), count, &f).Compute()));
	cnt.Append(std::move(FunctionPreCacher(x, (count * 2), &f).Compute()));
	cnt.Append(std::move(FunctionPreCacher((x * 2), (count * 2), &f).Compute()));

	cnt.PrintResult();


	return 0;
}