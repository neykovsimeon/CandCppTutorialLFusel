#include <stdio.h>
#include <stdint.h>

typedef int64_t accumulateInt;				// gives the opportunity to change the type at one place only
// todo: learn about size_t -> unsigned int matched to the platform's/system's bus size (32/64 bit)
// todo: learn the platform differences and C versus C++ differences

typedef struct
{
	// In "C" we cannot give here default values.
	accumulateInt sum;						// Sum of all values
	accumulateInt num;						// Number of summed values
} accumulateData;

// with typedef struct we define custom data type and no longer need to use "struct" key word below
/**************************************************************************************************/
void newAccumulateData(accumulateData* data)
{
	// 1st method: representative !
	//(*data).sum = 0;
	//(*data).num = 0;
	// 2nd method: to be used
	data->sum = 0; // struct "data" is given trough its address (pointer), thus we derefence its members with "->"
	data->num = 0; // struct "data" is given trough its address (pointer), thus we derefence its members with "->"
}
void accumulate(accumulateData* data, accumulateInt value_acc)
{
	data->sum += value_acc;
	data->num++;
}
// Optional method for small structs: require the mechanism for struct's members copy
//accumulateInt accumulateResult(accumulateData data)
//{
//	return data.sum / data.num;
//}
// General method to be used
// TODO: to clarify and understand the difference between pass variable as reference versus pointers
accumulateInt accumulateResult(accumulateData* data)
{
	return data->sum / data->num;
}

int main()
{
	printf("==== Hello from Pointers-And-Structs with typedef! ====\n\n");
	/*********************************************************/

	accumulateData data;
	newAccumulateData(&data);

	accumulate(&data, 10);
	accumulate(&data, 20);
	accumulate(&data, 30);
	accumulate(&data, 40);

	//int64_t avg = data.sum / data.num;			// Optional - representative. The average calculated
	//int64_t avg = accumulateResult(data);			// In case the optional accumulateResult method is used
	accumulateInt avg = accumulateResult(&data);			// The division result is casted to integer (int64_t) average
	printf("The average is: %lli\n", avg);		// printf for int
	//printf("The average is: %f\n", avg);			// printf for float 


	return 0;
}

/*  Options possible:
*
*  typedef struct accumulateData // gives the name of the struct
*  {
*  	// Gives both the struct name and the defined type name
*  	accumulateInt sum;						// Sum of all values
*  	accumulateInt num;						// Number of summed values
*  } accumulateData; // gives the name of the typedef
* 
*  1) then we can create an instance directly:
*  accumulateData data1;
* 
*  2) also we can use the clasical way:
*  struct accumulateData data2;
* 
*  When we use it with no name struct, then the option 2) above is not valid
*  typedef struct
*  {
*  	// Gives both the struct name and the defined type name
*  	accumulateInt sum;						// Sum of all values
*  	accumulateInt num;						// Number of summed values
*  } accumulateData; // gives the name of the typedef 
*/