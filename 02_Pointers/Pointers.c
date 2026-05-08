#include <stdio.h>
#include <stdint.h>

void accumulate(int64_t* sum_acc, int64_t* num_acc, int64_t value_acc)
{
	(*sum_acc)+= value_acc; // *sum_acc+= value_acc;
	(*num_acc)++;
}

int main()
{
	printf("==== Hello from Pointers! ====\n\n");
	/**************************************/

	int64_t sum = 0;						// Sum of all values
	int64_t num = 0;						// Number of summed values

	accumulate(&sum, &num, 10);
	accumulate(&sum, &num, 20);


	int64_t avg = sum / num;				// the average calculated
	printf("The average is: %lli\n", avg);


	return 0;
}