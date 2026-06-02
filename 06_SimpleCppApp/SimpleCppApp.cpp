#include "SimpleCppApp.hpp"


int SimpleCppApp::SaveMain()
{
	int32_t x;
	uint32_t count;
	std::cout << "Enter the starting value: ";
	std::cin >> x;
	std::cout << "Enter the itterations: ";
	std::cin >> count;
	
	//FunctionPreCacher vc(x, count, &fVector);
	//vc(); // vc -> vector container, vc() -> vc.Compute()
	//std::cout << vc << std::endl;

	PreCacherContainer<SimpleCppAppVector> cnt;						// Create a container for FunctionPreCacher objects
	// Showed differnt usages also for Compute() overloaded
	cnt << std::move(FunctionPreCacher(x, count, &f)())						 // 0, use it with operator function call Compute() overloaded
		<< std::move(FunctionPreCacher((x * 2), count, &f).operator()())	 // 1, use it with operator function call Compute() overloaded
		//<< std::move(FunctionPreCacher()(x, (count * 2), &f))				 // 2, use it with operator function call Compute() overloaded
		<< std::move(FunctionPreCacher((x * 2), (count * 2), &f).Compute())	 // 3,
		<< std::move(FunctionPreCacher((x * 3), (count * 3), &f));			 // 4, Remove the computation. Used to demonstrate the use for bool() overloaded

	//cnt[3].PrintResult();
	std::cout << cnt;

	return 0;
}

