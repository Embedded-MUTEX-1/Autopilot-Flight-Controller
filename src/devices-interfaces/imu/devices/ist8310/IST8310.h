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
#include "../../../Device.h"
#include "../../../../structs.h"

#define DEVICE_ADDR 0x0E

class IST8310 : public Device<struct attitudeData> {
public:
    IST8310() {}
	IST8310(I2cDevice* w);
	void setI2cInterface(I2cDevice* w);
	bool isConnected();
	int8_t init() override;
	int8_t deinit() override;
	int8_t updateAndGetData(struct attitudeData &values) override;
	void dataRequest();
	bool isDataRdy();
	int8_t read(int16_t* axisX, int16_t* axisY, int16_t* axisZ);
private:
    I2cDevice* w;
	int8_t write_regs(uint8_t reg_addr,uint8_t *data, uint16_t len);
	int8_t read_regs(uint8_t reg_addr,uint8_t *data, uint16_t len);
	bool isDataRequested;
};

#endif /* SRC_POSITIONING_MAG_IST8310_H_ */
