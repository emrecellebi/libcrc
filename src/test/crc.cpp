#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "crc.h"

int main(int argc, char** argv)
{
	if(argc <= 1)
	{
		printf("crc : No command specified. Use 'crc --help' for a detailed command list");
		return 1;
	}
	
	if(argc == 3 && strcmp(argv[1], "--crc8") == 0)
	{
		char* ptr = argv[2];
		size_t len = strlen(ptr);
		char data[len + 1];
		strcpy(data, ptr);
		
		uint8_t hash = crc_8((const unsigned char*)data, strlen(data));
		printf("CRC8 Hash: 0x%X, %d", hash, hash);
		return 1;
	}
	
	if(argc == 3 && strcmp(argv[1], "--crc16") == 0)
	{
		char* ptr = argv[2];
		size_t len = strlen(ptr);
		char data[len + 1];
		strcpy(data, ptr);
		
		uint16_t hash = crc_16((const unsigned char*)data, strlen(data));
		printf("CRC16 Hash: 0x%X, %d", hash, hash);
		return 1;
	}
	
	if(argc == 3 && strcmp(argv[1], "--crc16-modbus") == 0)
	{
		char* ptr = argv[2];
		size_t len = strlen(ptr);
		char data[len + 1];
		strcpy(data, ptr);
		
		uint16_t hash = crc_16_modbus((const unsigned char*)data, strlen(data));
		printf("CRC16 Hash: 0x%X, %d", hash, hash);
		return 1;
	}
	
	if(argc == 3 && strcmp(argv[1], "--crc16-kermit") == 0)
	{
		char* ptr = argv[2];
		size_t len = strlen(ptr);
		char data[len + 1];
		strcpy(data, ptr);
		
		uint16_t hash = crc_16_kermit((const unsigned char*)data, strlen(data));
		printf("CRC16 Hash: 0x%X, %d", hash, hash);
		return 1;
	}
	
	if(argc == 3 && strcmp(argv[1], "--crc16-ccitt-false") == 0)
	{
		char* ptr = argv[2];
		size_t len = strlen(ptr);
		char data[len + 1];
		strcpy(data, ptr);
		
		uint16_t hash = crc_16_ccitt((const unsigned char*)data, strlen(data), CRC_START_16_CCITT_FFFF);
		printf("CRC16 Hash: 0x%X, %d", hash, hash);
		return 1;
	}
	
	if(argc == 3 && strcmp(argv[1], "--crc16-ccitt-aug") == 0)
	{
		char* ptr = argv[2];
		size_t len = strlen(ptr);
		char data[len + 1];
		strcpy(data, ptr);
		
		uint16_t hash = crc_16_ccitt((const unsigned char*)data, strlen(data), CRC_START_16_CCITT_1D0F);
		printf("CRC16 Hash: 0x%X, %d", hash, hash);
		return 1;
	}
	
	if(argc == 3 && strcmp(argv[1], "--crc16-ccitt-xmodem") == 0)
	{
		char* ptr = argv[2];
		size_t len = strlen(ptr);
		char data[len + 1];
		strcpy(data, ptr);
		
		uint16_t hash = crc_16_ccitt((const unsigned char*)data, strlen(data), CRC_START_16_XMODEM);
		printf("CRC16 Hash: 0x%X, %d", hash, hash);
		return 1;
	}
	
	if(argc == 3 && strcmp(argv[1], "--crc16-dnp") == 0)
	{
		char* ptr = argv[2];
		size_t len = strlen(ptr);
		char data[len + 1];
		strcpy(data, ptr);
		
		uint16_t hash = crc_16_dnp((const unsigned char*)data, strlen(data));
		printf("CRC16 Hash: 0x%X, %d", hash, hash);
		return 1;
	}
	
	if(argc == 3 && strcmp(argv[1], "--crc16-sick") == 0)
	{
		char* ptr = argv[2];
		size_t len = strlen(ptr);
		char data[len + 1];
		strcpy(data, ptr);
		
		uint16_t hash = crc_16_sick((const unsigned char*)data, strlen(data));
		printf("CRC16 Hash: 0x%X, %d", hash, hash);
		return 1;
	}
	
	if(argc == 3 && strcmp(argv[1], "--crc32") == 0)
	{
		char* ptr = argv[2];
		size_t len = strlen(ptr);
		char data[len + 1];
		strcpy(data, ptr);
		
		uint32_t hash = crc_32((const unsigned char*)data, strlen(data));
		printf("CRC32 Hash: 0x%lX, %ld", hash, hash);
		return 1;
	}
	
	if(argc == 3 && strcmp(argv[1], "--crc64-ecma") == 0)
	{
		char* ptr = argv[2];
		size_t len = strlen(ptr);
		char data[len + 1];
		strcpy(data, ptr);
		
		uint64_t hash = crc_64_ecma((const unsigned char*)data, strlen(data));
		printf("CRC64 Hash: 0x%llX, %lld", hash, hash);
		return 1;
	}
	
	if(argc == 3 && strcmp(argv[1], "--crc64-we") == 0)
	{
		char* ptr = argv[2];
		size_t len = strlen(ptr);
		char data[len + 1];
		strcpy(data, ptr);
		
		uint64_t hash = crc_64_we((const unsigned char*)data, strlen(data));
		printf("CRC64 Hash: 0x%llX, %lld", hash, hash);
		return 1;
	}
	
	if(argc == 3 && strcmp(argv[1], "--nmea-chk") == 0)
	{
		char* ptr = argv[2];
		size_t len = strlen(ptr);
		char data[len + 1];
		strcpy(data, ptr);
		
		/**
			$GPGGA,152926,6027.8259,N,02225.6713,E,8,09,2.0,44.7,M,20.6,M,,*
			$GPGSV,3,2,09,18,28,305,43,23,14,340,39,26,64,222,49,28,60,084,49*
			$GPGSV,3,2,11,19,24,158,,07,21,237,,25,16,039,,24,11,315,*
			$GPGGA,001431.003,3907.3885,N,12102.4767,W,1,05,02.1,00545.5,M,-26.0,M,,*5D
		**/
		
		unsigned char buffer[4];
		checksum_NMEA((const unsigned char*)data, buffer);
		printf("CRC16 Hash: 0x%X, %d", buffer, buffer);
		return 1;
	}
	
	if(argc == 2 && strcmp(argv[1], "--help") == 0)
	{
		printf("\nCopyright (c) 2012-2024 Emre Celebi\n\n");
		printf("Usage: crc [-options] <parameters>\n");
		printf("   --crc8 <str>\n");
		printf("   --crc16 <str>\n");
		printf("   --crc16-modbus <str>\n");
		printf("   --crc16-kermit <str>\n");
		printf("   --crc16-ccitt-false <str>\n");
		printf("   --crc16-ccitt-aug <str>\n");
		printf("   --crc16-ccitt-xmodem <str>\n");
		printf("   --crc16-dnp <str>\n");
		printf("   --crc16-sick <str>\n");
		printf("   --crc32 <str>\n");
		printf("   --crc64-ecma <str>\n");
		printf("   --crc64-we <str>\n");
		printf("   --nmea-chk <str>\n");
		printf("   --version\n");
		printf("   --help\n");
		return 1;
	}
	
	if(argc == 2 && strcmp(argv[1], "--version") == 0)
	{
		printf("\nencrypt version: 0.0.6\n");
		printf("Last revised: 04th Feb 2024\n");
		printf("The last version is always avaible\n");
		printf("Created By Emre Celebi\n");
		return 1;
	}
	
	return 0;
}