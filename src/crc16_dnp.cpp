#include <stdint.h>
#include "crc.h"

static bool crc_tab16_dnp_init = false;
static uint16_t crc_tab16_dnp[256];

static void crc_16_dnp_init_tab(void)
{
	int i;
	int j;
	uint16_t crc;
	uint16_t c;

	for(i = 0; i < 256; i++)
	{
		crc = 0;
		c = (uint16_t)i;
		for(j = 0; j < 8; j++)
		{
			if((crc ^ c) & 0x0001) 
				crc = ( crc >> 1 ) ^ CRC_POLY_16_DNP;
			else 
				crc = crc >> 1;
			c = c >> 1;
		}
		crc_tab16_dnp[i] = crc;
	}
	crc_tab16_dnp_init = true;
}


uint16_t crc_16_dnp(const unsigned char* ptr, size_t num_bytes)
{
	uint16_t crc = CRC_START_16_DNP;
	size_t a;

	if(!crc_tab16_dnp_init)
		crc_16_dnp_init_tab();
	if(ptr != NULL)
		for(a = 0; a < num_bytes; a++)
			crc = (crc >> 8) ^ crc_tab16_dnp[(crc ^ (uint16_t)*ptr++) & 0x00FF];
	crc = ~crc;
	
	return crc;
}

uint16_t crc_16_dnp_reverse(uint16_t crc)
{
	uint16_t low_byte  = (crc & 0xff00) >> 8;
	uint16_t high_byte = (crc & 0x00ff) << 8;
	return low_byte | high_byte;
}

uint16_t update_crc_16_dnp(uint16_t crc, unsigned char c)
{
	if(!crc_tab16_dnp_init)
		crc_16_dnp_init_tab();
	return (crc >> 8) ^ crc_tab16_dnp[(crc ^ (uint16_t)c) & 0x00FF];
}