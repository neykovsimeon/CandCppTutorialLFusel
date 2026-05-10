#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <string.h>


int main()
{
	printf("\n==== Hello from Memory Utilities functions ====\n");

	int32_t arrayA[32];
	int32_t arrayB[32];

	// Init arrays
	// arrayA init with unique values for each element
	for (int32_t i = 0; i < 32; i++)
	{
		arrayA[i] = i * 11;
	}
	// arrayB init with memset() with the same value -1 for all elements
	memset(arrayB, 0xFF, 32 * sizeof(int32_t)); // 0xFF would represent -1 in 2's complement and will fill-up whole bit range of int32_t

	// compare arrays before copy
	// memcomp return value: 0 if equal, -1 if not equal
	// abEqual = 1 (true) if memcmp return value is 0 (equal)
	// abEqual = 0 (false) if memcmp return value is not 0 (not equal)
	int32_t abEqual = memcmp(arrayA, arrayB, 32 * sizeof(int32_t)) == 0;
	printf("\nArrays equal bevore copy (1 for equal, 0 for not equal): %i \n", abEqual);

	// Copy arrays
	memcpy(arrayB, arrayA, 32 * sizeof(int32_t)); // arguments: source, destination, size

	// compare arrays after copy
	abEqual = memcmp(arrayA, arrayB, 32 * sizeof(int32_t)) == 0;
	printf("\nArrays equal bevore copy (1 for equal, 0 for not equal): %i \n", abEqual);

	return 0;
}
