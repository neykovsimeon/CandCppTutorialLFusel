#include <stdio.h>
#include <stdint.h>

struct accumulateData
{
	// In "C" we cannot give here default values.
	int64_t sum;						// Sum of all values
	int64_t num;						// Number of summed values
};
void newAccumulateData(struct accumulateData* data)
{
	// 1st method: representative !
	//(*data).sum = 0;
	//(*data).num = 0;
	// 2nd method: to be used
	data->sum = 0; // struct "data" is given trough its address (pointer), thus we derefence its members with "->"
	data->num = 0; // struct "data" is given trough its address (pointer), thus we derefence its members with "->"
}
void accumulate(struct accumulateData* data, int64_t value_acc)
{
	data->sum += value_acc; 
	data->num++;
}
// Optional method for small structs: require the mechanism for struct's members copy
//int64_t accumulateResult(struct accumulateData data)
//{
//	return data.sum / data.num;
//}
// General method to be used
// TODO: to clarify and understand the difference between pass variable as reference versus pointers
int64_t accumulateResult(struct accumulateData* data)
{
	return data->sum / data->num;
}

int main()
{
	printf("==== Hello from Pointers-And-Structs! ====\n\n");
	/******************************************/

	struct accumulateData data;
	newAccumulateData(&data);

	accumulate(&data, 10);
	accumulate(&data, 20);
	accumulate(&data, 30);

	//int64_t avg = data.sum / data.num;			// Optional - representative. The average calculated
	//int64_t avg = accumulateResult(data);			// In case the optional accumulateResult method is used
	int64_t avg = accumulateResult(&data);			// The division result is casted to integer (int64_t) average
	printf("The average is: %lli\n", avg);


	return 0;
}