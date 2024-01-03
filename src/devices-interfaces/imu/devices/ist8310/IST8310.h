/*
 * IST8310.h
 *
 *  Created on: 9 nov. 2023
 *      Author: lenny
 */

#ifndef SRC_POSITIONING_MAG_IST8310_H_
#define SRC_POSITIONING_MAG_IST8310_H_

#include <cstdint>
#include <cstddef>
#include "IST8310_Registers.h"
#include "../../../low-level/I2cDevice.h"
#include "../../../../utils/utils.h"

class IST8310 {
public:
	IST8310();
	void setI2cInterface(I2cDevice* w);
	bool isConnected();
	int  init();
	void dataRequest();
	bool isDataRdy();
	int8_t read(int16_t* axisX, int16_t* axisY, int16_t* axisZ);
private:
    I2cDevice* w;
	const uint8_t DEVICE_ADDR = 0x0E;
	int8_t write_regs(uint8_t reg_addr,uint8_t *data, uint16_t len);
	int8_t read_regs(uint8_t reg_addr,uint8_t *data, uint16_t len);
};

#endif /* SRC_POSITIONING_MAG_IST8310_H_ */
