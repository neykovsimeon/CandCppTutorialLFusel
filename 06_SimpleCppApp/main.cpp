#include <iostream>
#include <cstdint>

int32_t f(int32_t x)
{
	return x * x + 5 * x + 5; 
}

struct FunctionPreCasher
{
	int32_t x = 0;
	int32_t count = 0;

	int32_t* values = nullptr;
	int32_t(*function)(int32_t x) = nullptr;

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
};

int main()
{

	FunctionPreCasher pc;
	pc.function = &f;
	std::cout << "Enter the starting value: ";
	std::cin >> pc.x;
	std::cout << "Enter the itterations: ";
	std::cin >> pc.count;

	pc.Compute();	//std::cout << "Starting at: " << pc.x << "; Number of itterations: " << pc.count << std::endl;
	pc.PrintResult();
	pc.Release();
	return 0;
}