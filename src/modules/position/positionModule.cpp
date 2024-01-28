//
// Created by lenny on 28/01/24.
//

#include "positionModule.h"
#include "../../devices-interfaces/low-level/UartDevice.h"
#include "../../devices-interfaces/gps/Gps.h"
#include "../../resources/nodes.h"
#include "../../utils/utils.h"

void positionTask(void *args) {
    UartDevice uart;
    Gps gps(&uart);
    struct positionData values;
    struct commanderState state;
    uint64_t timestamp = 0;

    uart.init(GPS_UART_PORT, GPS_UART_TX, GPS_UART_RX, GPS_UART_BAUD);
    gps.init();

    while(1) {
        timestamp = get_ms_count();

        commanderStateNode.get(state);
        gps.updateAndGetData(values);

        positionNode.set(values);

        values.loopPeriod = get_ms_count() - timestamp;
    }
}