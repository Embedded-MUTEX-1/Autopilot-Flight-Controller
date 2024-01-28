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
    lidar.init();

    while(1) {
        timestamp = get_ms_count();

        delay_milis((1 / ATTITUDE_LOOP_FREQ) * 1000);

        lidar.updateAndGetData(values);

        altitudeNode.set(values);

        values.loopPeriod = get_ms_count() - timestamp;
    }
}