#include <stdio.h>
#include <stdint.h>

#include "crc.h"

unsigned char* checksum_NMEA(const unsigned char* ptr, unsigned char* result)
{
	unsigned char checksum = 0;

	if(ptr == NULL) return NULL;
	if(result == NULL) return NULL;

	if(*ptr == '$') ptr++;
	while(*ptr && *ptr != '\r' && *ptr != '\n' && *ptr != '*')
		checksum ^= *ptr++;
	snprintf((char*)result, 3, "%02hhX", checksum);
	return result;
}