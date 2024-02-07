#ifndef LIBCRC_CRC_H
#define LIBCRC_CRC_H

#define	CRC_START_8		0x00
#define	CRC_XOR_8		0x00

#define	CRC_POLY_16			0xA001
#define	CRC_START_16		0x0000
#define	CRC_XOR_16			0x0000
#define	CRC_START_MODBUS	0xFFFF

#define CRC_POLY_16_CCITT			0x1021
#define	CRC_START_16_XMODEM			0x0000
#define	CRC_START_16_CCITT_1D0F		0x1D0F
#define	CRC_START_16_CCITT_FFFF		0xFFFF
#define	CRC_XOR_16_CCITT			0x0000

#define	CRC_POLY_16_KERMIT		0x8408
#define	CRC_START_16_KERMIT		0x0000
#define	CRC_XOR_16_KERMIT		0x0000

#define CRC_POLY_16_DNP			0xA6BC
#define	CRC_START_16_DNP		0x0000
#define	CRC_XOR_16_DNP			0xFFFF

#define CRC_POLY_16_SICK		0x8005
#define	CRC_START_16_SICK		0x0000

#define CRC_POLY_32		0xEDB88320ul
#define CRC_START_32	0xFFFFFFFFul
#define CRC_XOR_32		0xFFFFFFFFul

#define CRC_POLY_64			0x42F0E1EBA9EA3693ull
#define CRC_START_64_ECMA	0x0000000000000000ull
#define CRC_START_64_WE		0xFFFFFFFFFFFFFFFFull
#define CRC_XOR_64_ECMA		0xFFFFFFFFFFFFFFFFull
#define CRC_XOR_64_WE		0xFFFFFFFFFFFFFFFFull

uint8_t crc_8(const unsigned char* ptr, size_t num_bytes);
uint8_t update_crc_8(unsigned char crc, unsigned char val);

uint16_t crc_16(const unsigned char* ptr, size_t num_bytes);
uint16_t crc_16_modbus(const unsigned char* ptr, size_t num_bytes);
uint16_t update_crc_16(uint16_t crc, unsigned char c);

uint16_t crc_16_ccitt_ffff(const unsigned char* ptr, size_t num_bytes);
uint16_t crc_16_ccitt_1d0f(const unsigned char* ptr, size_t num_bytes);
uint16_t crc_16_xmodem(const unsigned char* ptr, size_t num_bytes);
uint16_t crc_16_ccitt(const unsigned char* ptr, size_t num_bytes, uint16_t start_value);
uint16_t update_crc_16_ccitt(uint16_t crc, unsigned char c);

uint16_t crc_16_kermit(const unsigned char* ptr, size_t num_bytes);
uint16_t update_crc_16_kermit(uint16_t crc, unsigned char c);
uint16_t crc_16_kermit_reverse(uint16_t crc);

uint16_t crc_16_dnp(const unsigned char* ptr, size_t num_bytes);
uint16_t update_crc_16_dnp(uint16_t crc, unsigned char c);
uint16_t crc_16_dnp_reverse(uint16_t crc);

uint16_t crc_16_sick(const unsigned char* ptr, size_t num_bytes);
uint16_t update_crc_16_sick(uint16_t crc, unsigned char c, unsigned char prev_byte);
uint16_t crc_16_sick_reverse(uint16_t crc);

uint32_t crc_32(const unsigned char* ptr, size_t num_bytes);
uint32_t update_crc_32(uint32_t crc, unsigned char c);

uint64_t crc_64_ecma(const unsigned char* ptr, size_t num_bytes);
uint64_t crc_64_we(const unsigned char* ptr, size_t num_bytes);
uint64_t update_crc_64(uint64_t crc, unsigned char c);

unsigned char* checksum_NMEA(const unsigned char* ptr, unsigned char* result);

#endif