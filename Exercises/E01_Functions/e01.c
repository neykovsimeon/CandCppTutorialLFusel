/*
 *
 *  Backend code for the 01 Functions exercise.
 *  Take a look at it and have fun ;-)
 *
 *  NOTE: This will only work on windows
 *
 */
#include <stdio.h>
#include <stdint.h>
#include <intrin.h>

int32_t serial_status = -1; // >= 0 -> Read for data
							// = -1 -> Serial closed (not opened)
							// = -2 -> Serial closed (error)

int32_t GetSerialStatus()
{
    return serial_status;
}

void SerialSentStatusAnalizer(static int32_t status)
{
    printf("serial_status = %i \n", status);
    if (status == -1)
    {
        printf("Error in serial interface! Be sure you have opened the interface with SerialBegin(). \n");
    }
    else if (status == -2)
    {
        printf("Parity doesn't have a valid value (0x0 or 0x1)!");
    }
    else if (status == -3)
    {
        printf("Expected parity is not the same as the localy calculated parity! \n");
    }
    else if (status >= 0)
    {
        printf("Serial data transmission in progress, %i Word(s) has been sent. \n", status);
    }
    else
    {
        printf("Unexpected value of serial_status! \n");
    }
}

/*
* The __popcnt16 function computes the number of set bits(1s) in a 16 - bit unsigned short integer.
* It's a compiler intrinsic that maps to the x86 POPCNT CPU instruction 
* (an instruction-set extension on modern Intel/AMD processors) and is 
* exposed by compilers/headers (e.g., MSVC/GCC/Clang intrinsics) to count set bits in a 16-bit value.
* Thus this code would only work on platforms that support the POPCNT instruction and 
* with compilers that provide the __popcnt16 intrinsic (like MSVC on Windows).
*/
uint16_t CountSetBits_PopulationCount(uint16_t value)
{ 
	return __popcnt16(value);
}

/*
* Below is Brian Kernighan’s algorithm  to count bits without platform specific commands
*/
uint16_t CountSetBits(uint16_t value)
{
    uint16_t count = 0;
    while (value > 0)
    {
		value &= (value - 1); // Clear the least significant bit set
        count++;
    }
    return count;
}

void SerialBegin()
{
    if (serial_status == -1)
    {
        printf("==== Ready for sending serial Data... ==== \n");
        serial_status = 0;
    }
    else if (serial_status >= 0)
    {
        printf("Serial already opened! \n");
    }
    else
    {
        printf("Error in Serial interface! SerialBegin() is used again without first SerialEnd() for previous session \n");
    }
}

void SerialEnd()
{
    if (serial_status >= 0)
    {
        printf("==== End of serial data transmition (Sent %i Words(s)) ==== \n", serial_status);
        serial_status = -1;
    }
    else if (serial_status == -1)
    {
        printf("Serial already closed! \n");
    }
    else
    {
        printf("==== Serial data transmission ended with error! ==== \n");
    }
}

uint32_t SerialSend(uint16_t data, uint8_t parity)
{
    if (serial_status < 0)
    {
        printf("Error in serial interface! Be sure you have opened the interface with SerialBegin(). \n");
        return serial_status;
    }

    if (parity != 0 && parity != 1)
    {
        serial_status = -2;
        printf("Parity doesn't have a valid value (0x0 or 0x1)!");
        return serial_status;
    }

    uint16_t bitsCount = CountSetBits(data);
    uint8_t expectedParity = bitsCount % 2; // work with unsigned
    if (expectedParity != parity)
    {
        serial_status = -3;
        printf("Expected parity is not the same as the localy calculated parity");
        return serial_status;
    }

    printf("Sending...: 0x%04X 0x%01x \n", data, parity);
    serial_status++;

    return serial_status;
}
