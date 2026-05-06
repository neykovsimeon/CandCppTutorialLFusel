#include <stdio.h>
#include <stdint.h>

int32_t f(int32_t x); // in C it works without this declaration, but in C++ it doesn't.
void print_fx(int32_t x, int32_t y);

int main()
{
	// Play with IPO model: (I)nput, (P)rocess, (O)utput
  	// (I) Simulate input from user
	int32_t x = 5; 
    // uint32_t, uint8_t, etc for unsigned. In C89, we don't have these types, 
    // but let's assume we are using a modern C compiler that supports C99 or later for the sake of this example. 
    // In C89, you would typically use 'int' and ensure it is 32 bits on your platform.

	// (P) Process the input; f(x), f(2x), f(3x)
    int32_t y1 = f(1 * x);        // x * x + 5 * x + 5;
    int32_t y2 = f(2 * x);
    int32_t y3 = f(3 * x);
    int32_t y4 = f(4 * x);

	// (O) Output the result
    //printf("\nOutput the result f(x) --> f(%d) =  %d\n", x, y1);
    //printf("Output the result f(2x) --> f(%i) =  %i\n", 2*x, y2);
    //printf("Output the result f(3x) --> f(%i) =  %i\n", 3*x, y3);
    print_fx(1 * x, y1);
    print_fx(2 * x, y2);
    print_fx(3 * x, y3);
    print_fx(4 * x, y4);

    
    return 0;
}

int32_t f(int32_t x)
{
    //int32_t y = x * x + 5 * x + 5;
    // !! if there is no return statement in the original code, which is a problem. Let's add it.
    // it works as a C app, won't compile without a return statement in C++ non-void function.

    return x * x + 5 * x + 5; //y; direct return without using a variable. Is it more efficient?
}

void print_fx(int32_t x, int32_t y)
{
	printf("Function f(x) output: f(%d) = %d\n", x, y);
}
