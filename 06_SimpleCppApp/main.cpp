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
		FunctionPreCacher(FunctionPreCacher&& another) noexcept						// double && used as a "move" semantic
		{
			x = another.x;
			count = another.count;
			function = another.function;
			values = another.values;

			another.values = nullptr;
		}
		FunctionPreCacher(int32_t x, uint32_t count, int32_t(*function)(int32_t)) 
		{
			Setup(x, count, function);
		}
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
		void PrintResult(std::ostream& os = std::cout) const
		{
			if(values)
				for (int32_t i = 1; i <= count; i++)
				{
					os << "f(" << i * x << ") = " << values[i - 1] << std::endl;
				}
			os << std::endl;
		}

		// Retrieve the computed value At index. Not yet validity check implemented
		int32_t At(uint32_t index) const
		{
			// TODO check the range
			return values[index];
		}
		// Retrieve the size of the array "values"
		uint32_t Size() const
		{
			return count;
		}

		FunctionPreCacher& operator()()
		{
			return Compute();
		}
		FunctionPreCacher& operator()(int32_t x, uint32_t count, int32_t(*function)(int32_t))
		{
			Setup(x, count, function);
			return Compute();
		}
		int32_t operator[](uint32_t index) const				// overload the array operator "[]"
		{
			return At(index);
		}
		operator bool()
		{
			return values != nullptr;
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

		PreCacherContainer(const PreCacherContainer&) = default;						// Default copy constructor
		~PreCacherContainer() = default;												// Default destructor

		PreCacherContainer& operator=(const PreCacherContainer&) = default;				// Default "copy" assign operator overload
		PreCacherContainer(PreCacherContainer&&) noexcept = default;					// Default "move" constructor - The Big five concept
		PreCacherContainer& operator=(PreCacherContainer&&) noexcept = default;			// Default "move" assign operator overload - The Big five concept

		void PrintResult(std::ostream& os = std::cout) const
		{
			os << "Container at " << this << std::endl;
			for (int i = 0; i < m_usage; i++)
			{
				os << "FunctionPreCacher #" << (i + 1) << std::endl;
				m_preCachers[i].PrintResult(os);
			}
		}

		void Append(const FunctionPreCacher& pc)
		{
			if (m_usage < 8)
			{
				m_preCachers[m_usage++] = pc; // m_usage would be frist taken with its old value, then assignment, then m_usage increment
			}
		}	
		void Append(FunctionPreCacher&& pc)
		{
			if (m_usage < 8)
			{
				m_preCachers[m_usage++] = std::move(pc); // m_usage would be first taken with its old value, then assignment, then m_usage increment
			}
		}
		const FunctionPreCacher& At(int index) const
		{
			return m_preCachers[index];
		}
		FunctionPreCacher& At(int index)
		{
			return m_preCachers[index];
		}
		int Size() const
		{
			return m_usage;
		}

		PreCacherContainer& operator<<(const FunctionPreCacher& pc)
		{
			Append(pc);
			return *this;
		}
		PreCacherContainer& operator<<(FunctionPreCacher&& pc)
		{
			Append(std::move(pc));
			return *this;
		}
		const FunctionPreCacher& operator[](int index) const
		{
			return At(index);
		}
		FunctionPreCacher& operator[](int index)
		{
			return At(index);
		}

	private:
		FunctionPreCacher m_preCachers[8];
		int m_usage = 0;
};

//-------------------------left hand side---------right hand side
std::ostream& operator<<(std::ostream& os, const PreCacherContainer& pc)
{
	pc.PrintResult(os);
	return os;
}

int main()
{
	int32_t x;
	uint32_t count;
	std::cout << "Enter the starting value: ";
	std::cin >> x;
	std::cout << "Enter the itterations: ";
	std::cin >> count;

	PreCacherContainer cnt;						// Create a container for FunctionPreCacher objects

	// Implementation of the Append functionlity with operator "<<" overloaded. 
	// Showed differnt usages also for Compute() overloaded
	cnt << std::move(FunctionPreCacher(x, count, &f)())						 // 0, use it with operator function call Compute() overloaded
		<< std::move(FunctionPreCacher((x * 2), count, &f).operator()())	 // 1, use it with operator function call Compute() overloaded
		<< std::move(FunctionPreCacher()(x, (count * 2), &f))				 // 2, use it with operator function call Compute() overloaded
		<< std::move(FunctionPreCacher((x * 2), (count * 2), &f).Compute())	 // 3,
		<< std::move(FunctionPreCacher((x * 3), (count * 3), &f));			 // 4, Remove the computation. Used to demonstrate the use for bool() overloaded
	//cnt.PrintResult();
	// 
	//cnt[1].PrintResult();
	//cnt[3].PrintResult();
	//for (uint32_t i = 0; i < cnt[0].Size(); i++)
	//{
	//	std::cout << "From me: " << cnt[0][i] << std::endl;
	//}
	std::cout << "Index 0: " << (bool)cnt[0] << std::endl;
	std::cout << "Index 4: " << (bool)cnt[4] << std::endl;

	// The use of std::cout (ostream)
	std::cout << cnt;

	return 0;
}