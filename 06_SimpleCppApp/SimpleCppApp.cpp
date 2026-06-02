#include "SimpleCppApp.hpp"

int32_t SimpleCppApp::f(int32_t x)
{
	return x * x + 5 * x + 5;
}

int SimpleCppApp::SaveMain()
{
	int32_t x;
	uint32_t count;
	std::cout << "Enter the starting value: ";
	std::cin >> x;
	std::cout << "Enter the itterations: ";
	std::cin >> count;

	PreCacherContainer cnt;						// Create a container for FunctionPreCacher objects
	// Showed differnt usages also for Compute() overloaded
	cnt << std::move(FunctionPreCacher(x, count, &f)())						 // 0, use it with operator function call Compute() overloaded
		<< std::move(FunctionPreCacher((x * 2), count, &f).operator()())	 // 1, use it with operator function call Compute() overloaded
		<< std::move(FunctionPreCacher()(x, (count * 2), &f))				 // 2, use it with operator function call Compute() overloaded
		<< std::move(FunctionPreCacher((x * 2), (count * 2), &f).Compute())	 // 3,
		<< std::move(FunctionPreCacher((x * 3), (count * 3), &f));			 // 4, Remove the computation. Used to demonstrate the use for bool() overloaded

	cnt[3].PrintResult();

	std::cout << cnt;

	return 0;
}

