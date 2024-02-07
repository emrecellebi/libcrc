#include <stdint.h>
#include "crc.h"

static bool crc_tab16_init = false;
static uint16_t crc_tab16[256];

static void init_crc16_tab(void)
{
	uint16_t i;
	uint16_t j;
	uint16_t crc;
	uint16_t c;

	for(i = 0; i < 256; i++)
	{
		crc = 0;
		c = i;
		for(j = 0; j < 8; j++)
		{
			if((crc ^ c) & 0x0001)
				crc = (crc >> 1) ^ CRC_POLY_16;
			else
				crc = crc >> 1;
			c = c >> 1;
		}
		crc_tab16[i] = crc;
	}
	crc_tab16_init = true;
}

uint16_t crc_16(const unsigned char* ptr, size_t num_bytes)
{
	uint16_t crc = CRC_START_16;
	size_t a;

	if(!crc_tab16_init)
		init_crc16_tab();
	
	if(ptr != NULL)
		for(a = 0; a < num_bytes; a++)
			crc = (crc >> 8) ^ crc_tab16[(crc ^ (uint16_t)*ptr++) & 0x00FF];
	return crc;
}

uint16_t crc_16_modbus(const unsigned char* ptr, size_t num_bytes)
{
	uint16_t crc = CRC_START_MODBUS;
	size_t a;

	if(!crc_tab16_init)
		init_crc16_tab();

	if(ptr != NULL)
		for(a = 0; a < num_bytes; a++)
			crc = (crc >> 8) ^ crc_tab16[(crc ^ (uint16_t)*ptr++) & 0x00FF];
	return crc;
}

uint16_t update_crc_16(uint16_t crc, unsigned char c)
{
	if(!crc_tab16_init)
		init_crc16_tab();
	return (crc >> 8) ^ crc_tab16[(crc ^ (uint16_t)c) & 0x00FF];
}