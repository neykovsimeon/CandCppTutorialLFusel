#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int32_t f(int32_t x);
int scan_int_inputs(int32_t* input, const char* userMessage);

void Exec_ProcessAndOutput(int32_t x, int32_t count);
void print_fx(int32_t x, int32_t y, int32_t count);

int main()
{
    // Play with IPO model: (I)nput, (P)rocess, (O)utput
    // (I) Proper input from user
    int32_t x, count;
    const char* userMessage = "Please enter integer value for x: ";
    int retValue_x      = scan_int_inputs(&x, userMessage);
    userMessage = "Please enter integer value for count: ";
    int retValue_count  = scan_int_inputs(&count, userMessage);

    // (P) Process the input; f(x), f(2x), f(3x), f(x) = x * x + 5 * x + 5;
    // (O) Output the result
    if (retValue_x == 1 && retValue_count ==1 && count > 0)
    {
        Exec_ProcessAndOutput(x, count);
    }
    else if (retValue_x == EOF || retValue_count == EOF)
    {
        printf("\nEOF returned, IO error!\n");
    }
    else if (retValue_count == 1 && count <= 0)
    {
        printf("\nThe count (second input value) must be bigger than 0!\n");
    }
    else 
    {
        printf("\nWrong user input(s)! The input(s) must be integer numbers, result's user range is +/- 2,147,483,647.\n");
    }

    return 0;
}

int32_t f(int32_t x)
{
    return x * x + 5 * x + 5;
}

int scan_int_inputs(int32_t* input, const char* userMessage) // we will return the return value from scanf_s, while the user input will be an argument
{
    // stops and waits for user's keyboard input for a number and press Enter
    printf(userMessage);
    // In case of correct input scanf_s should return 1 (one integer argument expected to be assigned)
    return scanf_s("%i", input);    // scanf -> scanf_s -> windows only behavior. TODO: learn more about it.
}

void print_fx(int32_t x, int32_t y, int32_t count)
{
    printf("Count number: %i : Function f(x) output: f(%i) = %i\n", count, x, y);
}

void Exec_ProcessAndOutput(int32_t x, int32_t count)
{
    // Implementation with dynamic array concept, malloc and sizeof
    // Memory allocation for count * size of the (int32_t). Good for C (review for C++)
    int32_t* y_value = malloc(count * sizeof(int32_t)); 

    if (y_value) // C -> NULL, C++ -> nullptr, it should be enough to ask simply for if (y_value)
    {
        // (P) Process
        for (int32_t i = 1; i <= count; i++)
        {
            y_value[i - 1] = f(i * x);
        }

        // (O) Output
        for (int32_t i = 1; i <= count; i++)
        {
            print_fx(i * x, y_value[i - 1], i);
        }

        // Free the memory
        free(y_value);
    }
}
