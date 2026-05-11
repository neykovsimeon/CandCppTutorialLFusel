#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

uint64_t GetUIDa()
{
	// Add static modifier concept
	static uint64_t id = 0; // id is not being re-initialized each time when the function is invoked.
	return id++;			// first take the old value and then increment
}

uint64_t GetUIDb()
{
	// Add static modifier concept
	static uint64_t id = 5; // id is not being re-initialized each time when the function is invoked.
	return id++;  			// first take the old value and then increment
}

int main()
{
	printf("\n==== Hello from Memory Utilities, const and static ====\n");

	for (uint64_t i = 0; i < 64; i++)
	{
		uint64_t uida = GetUIDa();
		uint64_t uidb = GetUIDb();
		//printf("UID = %llu\n", uid);
		printf("UIDa = %"PRIu64" & UIDb = %"PRIu64"\n", uida, uidb);
	}

	const int32_t count = 32;
	const int32_t size = count * sizeof(int32_t);

	int32_t* const arrayA = malloc(size); // the ptr to the 1st element is const, it is not that the element itself is made const
	int32_t* const arrayB = malloc(size); // the ptr to the 1st element is const, it is not that the element itself is made const

	if (arrayA && arrayB)
	{
		// Init arrays
		for (int32_t i = 0; i < count; i++)
		{
			arrayA[i] = i * 11;
		}
		// arrayB init with memset() with the same value -1 for all elements
		memset(arrayB, 0xFF, size);

		// compare arrays before copy
		int32_t abEqual = memcmp(arrayA, arrayB, size) == 0;
		printf("\nArrays equal bevore copy (1 for equal, 0 for not equal): %i \n", abEqual);

		// Copy arrays
		memcpy(arrayB, arrayA, size); // arguments: source, destination, size

		// compare arrays after copy
		abEqual = memcmp(arrayA, arrayB, size) == 0;
		printf("\nArrays equal bevore copy (1 for equal, 0 for not equal): %i \n", abEqual);
	}

	// Free allocated memory
	if (arrayA) free(arrayA);
	if (arrayB) free(arrayB);

	return 0;
}
