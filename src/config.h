//
// Created by lenny on 05/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_CONFIG_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_CONFIG_H

#define P_NAV 0.25 
#define I_NAV 0
#define D_NAV 0.5

#define P_ROLL_PITCH 1.4 
#define I_ROLL_PITCH 0.001
#define D_ROLL_PITCH 0

#define P_YAW 4
#define I_YAW 0
#define D_YAW 0

#define P_ALT 0
#define I_ALT 0
#define D_ALT 0

#define OFFSET_ROLL  0
#define OFFSET_PITCH 0
#define OFFSET_YAW   0

#define PARAM_1 0.3
#define PARAM_2 0.001

#define NUMBER_OF_MOTORS 4 // 4 or 6
#define ESC1_PIN 40
#define ESC2_PIN 39
#define ESC3_PIN 38
#define ESC4_PIN 12
#define ESC5_PIN 11
#define ESC6_PIN 10
#define PWM_FREQ 400
#define NUMBER_OF_CHANNELS 14
#define ENABLE_MAG_CALIBRATION 0
#define MAG_CALIBRATION_DURATION 200  // x 100 ms
#define IMU_CALIBRATION_DURATION 1000 // 1000 tours

#define VBAT_PIN 7
#define LED_PIN 15

#define COEFF_ROLL_FRONT_REAR  1.25
#define COEFF_ROLL_LEFT_RIGHT  1.5
#define C_PITCH_FRONT_REAR  1.5
#define C_YAW  1.333

#define THROTTLE_CHAN         2
#define ROLL_CHAN             0
#define PITCH_CHAN            1
#define YAW_CHAN              3
#define MODE_SELECTION_CHAN   4
#define DISARMED_CHAN         5

#define MAX_YAW_CHAN_THRESHOLD 1550
#define MIN_YAW_CHAN_THRESHOLD 1450

#define DIRECT_CONNECTION 1
#define UDP_PORT 5000
#define WIFI_CONNECTING_TIMEOUT 10000 // 10 sec
#define WIFI_AP_SSID    "Autopilot Drone"
#define WIFI_AP_PASSWD  "12345678"
#define WIFI_STA_SSID   "Galaxy A22"
#define WIFI_STA_PASSWD "12345678"

#define SCL_PIN 9
#define SDA_PIN 8

#define ATTITUDE_LOOP_FREQ   250 // Hz
#define PID_LOOP_FREQ        250 // Hz
#define MOTORS_LOOP_FREQ     250 // Hz
#define ALTITUDE_LOOP_FREQ    50 // Hz
#define NAVIGATION_LOOP_FREQ  50 // Hz
#define COMMANDER_LOOP_FREQ   50 // Hz
#define RECEIVER_LOOP_FREQ   100 // Hz
#define TELEMETRY_LOOP_FREQ   10 // Hz

#define MAGNETIC_DECLINATION  1 // deg

#define LIDAR_UART_PORT           0
#define LIDAR_UART_TX            43
#define LIDAR_UART_RX            44
#define LIDAR_UART_BAUD      115200

#define GPS_UART_PORT             2
#define GPS_UART_TX              47
#define GPS_UART_RX              21
#define GPS_UART_BAUD        115200

#define RECEIVER_UART_PORT        1
#define RECEIVER_UART_TX         17
#define RECEIVER_UART_RX         18
#define RECEIVER_UART_BAUD   115200

#define MAX_ANGLE_RATE 164 // deg/sec
#define MAX_ANGLE     32.8 // deg
#define MAX_NAV_ANGLE 20.4 // deg

#define LAT_LON_PRECISION 1e6 // = 10cm

#define MAX_CHANNEL_VALUE     2000
#define MIN_CHANNEL_VALUE     1000
#define MIN_THROTTLE_VALUE    1000
#define MIN_THROTTLE_THRESOLD 1100
#define MAX_CHANNEL_THRESOLD  1550
#define MIN_CHANNEL_THRESOLD  1450
#define POS_HOLD_CHAN_5_VALUE 1500

#define ALTITUDE_ATTENUATOR_THRESOLD 15 // cm
#define ALTITUDE_ATTENUATOR_VALUE     2

//#define MQTT_CONNECT_RETRY_COUNT 10


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_CONFIG_H
