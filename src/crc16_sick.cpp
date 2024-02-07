#include <stdint.h>
#include "crc.h"

uint16_t crc_16_sick(const unsigned char* ptr, size_t num_bytes)
{
	uint16_t crc = CRC_START_16_SICK;
	uint16_t short_c;
	uint16_t short_p = 0;
	size_t a;

	if(ptr != NULL)
	{
		for(a = 0; a < num_bytes; a++)
		{
			short_c = 0x00FF & (uint16_t)*ptr;
			if(crc & 0x8000)
				crc = (crc << 1) ^ CRC_POLY_16_SICK;
			else 
				crc = crc << 1;

			crc ^= (short_c | short_p);
			short_p = short_c << 8;
			ptr++;
		}
	}
	return crc;
}

uint16_t crc_16_sick_reverse(uint16_t crc)
{
	uint16_t low_byte  = (crc & 0xFF00) >> 8;
	uint16_t high_byte = (crc & 0x00FF) << 8;
	return low_byte | high_byte;
}

uint16_t update_crc_16_sick(uint16_t crc, unsigned char c, unsigned char prev_byte)
{
	uint16_t short_c = 0x00FF & (uint16_t)c;
	uint16_t short_p = (0x00FF & (uint16_t)prev_byte) << 8;

	if(crc & 0x8000)
		crc = (crc << 1) ^ CRC_POLY_16_SICK;
	else
		crc = crc << 1;
	crc ^= (short_c | short_p);

	return crc;
}