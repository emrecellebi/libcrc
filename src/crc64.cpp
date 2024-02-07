#include <stdint.h>
#include "crc.h"

static bool crc_tab64_init = false;
static uint64_t crc_tab64[256];

static void init_crc64_tab(void)
{
	uint64_t i;
	uint64_t j;
	uint64_t c;
	uint64_t crc;

	for(i = 0; i < 256; i++)
	{
		crc = 0;
		c = i << 56;
		for(j = 0; j < 8; j++)
		{
			if((crc ^ c) & 0x8000000000000000ull)
				crc = (crc << 1) ^ CRC_POLY_64;
			else 
				crc = crc << 1;
			c = c << 1;
		}
		crc_tab64[i] = crc;
	}
}

uint64_t crc_64_ecma(const unsigned char* ptr, size_t num_bytes)
{
	uint64_t crc = CRC_START_64_ECMA;
	size_t a;
	
	if(!crc_tab64_init)
		init_crc64_tab();
	
	if(ptr != NULL)
		for(a = 0; a < num_bytes; a++)
			crc = (crc << 8) ^ crc_tab64[((crc >> 56) ^ (uint64_t)*ptr++) & 0x00000000000000FFull];
	return crc;
}

uint64_t crc_64_we(const unsigned char* ptr, size_t num_bytes)
{
	uint64_t crc = CRC_START_64_WE;
	size_t a;
	
	if(!crc_tab64_init)
		init_crc64_tab();
	
	if(ptr != NULL)
		for(a = 0; a < num_bytes; a++)
			crc = (crc << 8) ^ crc_tab64[ ((crc >> 56) ^ (uint64_t)*ptr++) & 0x00000000000000FFull];
	return crc ^ 0xFFFFFFFFFFFFFFFFull;
}

uint64_t update_crc_64(uint64_t crc, unsigned char c)
{
	return (crc << 8) ^ crc_tab64[ ((crc >> 56) ^ (uint64_t)c) & 0x00000000000000FFull];
}