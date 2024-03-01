#ifndef SRC_POSITIONING_MAG_IST8310_REGISTERS_H_
#define SRC_POSITIONING_MAG_IST8310_REGISTERS_H_

#include "stdint.h"

enum class Register : uint8_t {
	WAI        = 0x00, // Who Am I Register

	STAT1      = 0x02, // Status Register 1
	DATAXL     = 0x03,
	DATAXH     = 0x04,
	DATAYL     = 0x05,
	DATAYH     = 0x06,
	DATAZL     = 0x07,
	DATAZH     = 0x08,
	STAT2      = 0x09, // Status Register 2
	CNTL1      = 0x0A, // Control Setting Register 1
	CNTL2      = 0x0B, // Control Setting Register 2
	STR        = 0x0C, // Self-Test Register
	CNTL3      = 0x0D, // Control Setting Register 3

	TEMPL      = 0x1C, // Temperature Sensor Output Register (Low Byte)
	TEMPH      = 0x1D, // Temperature Sensor Output Register (High Byte)

	TCCNTL     = 0x40, // Temperature Compensation Control register
	AVGCNTL    = 0x41, // Average Control Register
	PDCNTL     = 0x42, // Pulse Duration Control Register

	XX_CROSS_L = 0x9C, // cross axis xx low byte
	XX_CROSS_H = 0x9D, // cross axis xx high byte
	XY_CROSS_L = 0x9E, // cross axis xy low byte
	XY_CROSS_H = 0x9F, // cross axis xy high byte
	XZ_CROSS_L = 0xA0, // cross axis xz low byte
	XZ_CROSS_H = 0xA1, // cross axis xz high byte
	YX_CROSS_L = 0xA2, // cross axis yx low byte
	YX_CROSS_H = 0xA3, // cross axis yx high byte
	YY_CROSS_L = 0xA4, // cross axis yy low byte
	YY_CROSS_H = 0xA5, // cross axis yy high byte
	YZ_CROSS_L = 0xA6, // cross axis yz low byte
	YZ_CROSS_H = 0xA7, // cross axis yz high byte
	ZX_CROSS_L = 0xA8, // cross axis zx low byte
	ZX_CROSS_H = 0xA9, // cross axis zx high byte
	ZY_CROSS_L = 0xAA, // cross axis zy low byte
	ZY_CROSS_H = 0xAB, // cross axis zy high byte
	ZZ_CROSS_L = 0xAC, // cross axis zz low byte
	ZZ_CROSS_H = 0xAD, // cross axis zz high byte
};

#endif
