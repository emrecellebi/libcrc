#include <stdint.h>
#include "crc.h"

static bool crc_tab16_ccitt_init = false;
static uint16_t crc_tab16_ccitt[256];

static void crc_16_ccitt_init_tab(void)
{
	uint16_t i;
	uint16_t j;
	uint16_t crc;
	uint16_t c;

	for(i = 0; i < 256; i++)
	{
		crc = 0;
		c = i << 8;
		for(j = 0; j < 8; j++)
		{
			if((crc ^ c) & 0x8000)
				crc = ( crc << 1 ) ^ CRC_POLY_16_CCITT;
			else 
				crc = crc << 1;
			c = c << 1;
		}
		crc_tab16_ccitt[i] = crc;
	}
	crc_tab16_ccitt_init = true;
}

uint16_t crc_16_ccitt_ffff(const unsigned char* ptr, size_t num_bytes)
{
	return crc_16_ccitt(ptr, num_bytes, CRC_START_16_CCITT_FFFF);
}

uint16_t crc_16_ccitt_1d0f(const unsigned char* ptr, size_t num_bytes)
{
	return crc_16_ccitt(ptr, num_bytes, CRC_START_16_CCITT_1D0F);
}

uint16_t crc_16_xmodem(const unsigned char* ptr, size_t num_bytes)
{
	return crc_16_ccitt(ptr, num_bytes, CRC_START_16_XMODEM);
}

uint16_t crc_16_ccitt(const unsigned char* ptr, size_t num_bytes, uint16_t start_value)
{
	uint16_t crc = start_value;
	size_t a;

	if(!crc_tab16_ccitt_init)
		crc_16_ccitt_init_tab();

	if(ptr != NULL)
		for(a = 0; a < num_bytes; a++)
			crc = (crc << 8) ^ crc_tab16_ccitt[((crc >> 8) ^ (uint16_t)*ptr++) & 0x00FF];
	return crc;
}

uint16_t update_crc_16_ccitt(uint16_t crc, unsigned char c)
{
	if(!crc_tab16_ccitt_init)
		crc_16_ccitt_init_tab();
	return (crc << 8) ^ crc_tab16_ccitt[((crc >> 8) ^ (uint16_t)c) & 0x00FF];
}