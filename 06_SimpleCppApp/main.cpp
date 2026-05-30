#include <iostream>
#include <cstdint>

int32_t f(int32_t x)
{
	return x * x + 5 * x + 5; 
}

class FunctionPreCasher
{
	
	public:
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
			std::cout << 
				"Starting at: " << x << ";" << 
				" Number of itterations : " << count << std::endl;
			Release();
			values = new int32_t[count];
			if (function && count > 0)
			{
				if (values)
				{
					for (uint32_t i = 1; i <= count; i++)
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
		void PrintResult()
		{
			if(values)
				for (uint32_t i = 1; i <= count; i++)
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

int main()
{

	int32_t x;
	uint32_t count;
	std::cout << "Enter the starting value: ";
	std::cin >> x;
	std::cout << "Enter the itterations: ";
	std::cin >> count;

	FunctionPreCasher pc;
	pc.Setup(x, count, &f);
	pc.Compute();
	pc.PrintResult();
	pc.Release();
	return 0;
}