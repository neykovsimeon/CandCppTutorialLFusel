#include <iostream>
#include <cstdint>
#include <cstring>
#include <cstdlib>

int32_t f(int32_t x)
{
	return x * x + 5 * x + 5; 
}

class FunctionPreCasher
{	
	public:		
		FunctionPreCasher() = default;
		// Constructor to create new object as a copy from another object: 
		FunctionPreCasher(const FunctionPreCasher& another)
		{
			x = another.x;
			count = another.count;
			function = another.function;
			if (another.values)
			{
				values = new int32_t[another.count];
				if (values)
				{
					std::memcpy(values, another.values, sizeof(int32_t) * another.count);
				}
			}
		}
		// Proper customer constructor introduced here.
		FunctionPreCasher(int32_t x, uint32_t count, int32_t(*function)(int32_t)) 
		{
			Setup(x, count, function);
		}
		// Proper custom destructor introduced here.
		~FunctionPreCasher() 
		{
			Release();
		}

		// this way we disable the use of "=" operator with FunctionPreCasher ojects
		FunctionPreCasher& operator=(const FunctionPreCasher& another)
		{
			if (this != &another) // prevent self-assignment
			{
				this->~FunctionPreCasher();
				this->FunctionPreCasher::FunctionPreCasher(another);
			}
			return *this;
		}

		void Setup(int32_t x, uint32_t count, int32_t(*function)(int32_t))
		{
			if (!values) // not yet to concern the topic how to properly handle errors
			{
				this->x = x;
				this->count = count;
				this->function = function;
			}
		}
		void Compute()
		{
			Release();
			values = new int32_t[count];
			if (function && count > 0)
			{
				if (values)
				{
					for (int32_t i = 1; i <= count; i++)
					{
						values[i - 1] = function(i * x); 
					}
				}
			}
		}
		void Release()
		{
			if (values)
			{
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
		}

	private:
		int32_t* values = nullptr;
		int32_t x = 0;
		int32_t count = 0;
		int32_t(*function)(int32_t x) = nullptr;	
};

void PrintPreCasher(const FunctionPreCasher pc)
{
	std::cout << "Printing with: " << &pc << std::endl;
	pc.PrintResult();
}

int main()
{
	int32_t x;
	uint32_t count;
	std::cout << "Enter the starting value: ";
	std::cin >> x;
	std::cout << "Enter the itterations: ";
	std::cin >> count;

	FunctionPreCasher pc(x, count, &f);
	pc.Compute();
	PrintPreCasher(pc);

	FunctionPreCasher spc(10, 3, &f);
	spc.Compute();

	spc = pc;
	PrintPreCasher(spc);

	FunctionPreCasher stored5 = pc;
	PrintPreCasher(stored5);

	return 0;
}