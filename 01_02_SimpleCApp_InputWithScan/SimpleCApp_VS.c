#include <stdio.h>
#include <stdint.h>

int32_t f(int32_t x);
int scan_sx(int32_t* x);

void print_fx(int32_t x, int32_t y);

int main()
{
    // Play with IPO model: (I)nput, (P)rocess, (O)utput
    // (I) Proper input from user
    int32_t x;
    int retValue = scan_sx(&x);     // we will implement user's input with scanf function.
    printf("\nRead %i parameters from user input.\n", retValue);
 
    // (P) Process the input; f(x), f(2x), f(3x), f(x) = x * x + 5 * x + 5;
    int32_t y1 = f(1 * x);          
    int32_t y2 = f(2 * x);
    int32_t y3 = f(3 * x);
    int32_t y4 = f(4 * x);

    // (O) Output the result
    print_fx(1 * x, y1);
    print_fx(2 * x, y2);
    print_fx(3 * x, y3);
    print_fx(4 * x, y4);

    return 0;
}

int32_t f(int32_t x)
{
    return x * x + 5 * x + 5;
}

int scan_sx(int32_t* x) // we will return the return value from scanf_s, while the user input will be an argument
{
    // stops and waits for user's keyboard input for a number and press Enter
    printf("Enter the value x: ");
    // In case of correct input scanf_s should return 1 (one integer argument expected to be assigned)
    return scanf_s("%i", x);    // scanf -> scanf_s -> windows only behavior. TODO: learn more about it.
}

void print_fx(int32_t x, int32_t y)
{
    printf("Function f(x) output: f(%d) = %d\n", x, y);
}
