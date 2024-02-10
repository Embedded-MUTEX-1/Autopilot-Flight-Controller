//
// Created by lenny on 15/01/24.
//

#include "altitudeModule.h"
#include "../../devices-interfaces/lidar/Lidar.h"
#include "../../config.h"
#include "../../resources/nodes.h"
#include "../../utils/utils.h"

void altitudeTask(void *args) {
    UartDevice uart;
    Lidar lidar(uart);
    struct altitudeData values;
    uint64_t timestamp = 0;

    uart.init(LIDAR_UART_PORT, LIDAR_UART_TX, LIDAR_UART_RX, LIDAR_UART_BAUD);
    if(lidar.init() != 0)
        while(1) { delay_milis(100); }

    while(1) {
        timestamp = get_ms_count();

        lidar.updateAndGetData(values);

        altitudeNode.set(values);

        values.loopPeriod = get_ms_count() - timestamp;
        wait(values.loopPeriod, ALTITUDE_LOOP_FREQ);
    }
}