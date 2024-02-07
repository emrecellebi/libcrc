#include <stdint.h>
#include "crc.h"

static bool crc_tab32_init = false;
static uint32_t crc_tab32[256];

static void init_crc32_tab(void)
{
	uint32_t i;
	uint32_t j;
	uint32_t crc;

	for(i = 0; i < 256; i++)
	{
		crc = i;
		for(j = 0; j < 8; j++)
		{
			if(crc & 0x00000001L)
				crc = (crc >> 1) ^ CRC_POLY_32;
			else 
				crc = crc >> 1;
		}
		crc_tab32[i] = crc;
	}
}

uint32_t crc_32(const unsigned char* ptr, size_t num_bytes)
{
	uint32_t crc = CRC_START_32;
	size_t a;
	
	if(!crc_tab32_init)
		init_crc32_tab();
	
	if(ptr != NULL)
		for(a = 0; a < num_bytes; a++)
			crc = (crc >> 8) ^ crc_tab32[ (crc ^ (uint32_t)*ptr++) & 0x000000FFul];
	return (crc ^ 0xFFFFFFFFul);
}

uint32_t update_crc_32(uint32_t crc, unsigned char c)
{
	return (crc >> 8) ^ crc_tab32[(crc ^ (uint32_t)c) & 0x000000FFul];
}