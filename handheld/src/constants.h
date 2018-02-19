#ifndef INCLUDE_STAULU_CONSTANTS_H
#define INCLUDE_STAULU_CONSTANTS_H

#define HT16K33_ADDRESS           0x70
#define HT16K33_BLINK_CMD         0x80
#define HT16K33_BLINK_DISPLAYON   0x01
#define HT16K33_CMD_BRIGHTNESS    0xE0
#define HT16K33_DISP_REGISTER     0x00
#define HT16K33_KEYINT_REGISTER   0x60
#define HT16K33_KEYS_REGISTER     0x40

#define MATRIX_STATIC         0
#define MATRIX_BLINK_2HZ      1
#define MATRIX_BLINK_1HZ      2
#define MATRIX_BLINK_HALFHZ   3

#define TRAFFIC_STATUS_FLUENT    '-'
#define TRAFFIC_STATUS_JAM1      '1'
#define TRAFFIC_STATUS_JAM2      '2'
#define TRAFFIC_STATUS_JAM3      '3'
#define TRAFFIC_STATUS_UNKNOWN   '?' // any character that is not any of the above is considered to match TRAFFIC_STATUS_UNKNOWN

#define TIMING_BUTTON_UPDATE        50  // milliseconds after which button state is updated
#define TIMING_MQTT_RECONNECT      500  // milliseconds between connection retries of the MQTT client
#define TIMING_ANIMATION_SPEED_0   300  // milliseconds between animation frames for default traffic type (TRAFFIC_STATUS_FLUENT and TRAFFIC_STATUS_UNKNOWN)
#define TIMING_ANIMATION_SPEED_1   300  // milliseconds between animation frames for traffic type TRAFFIC_STATUS_JAM1
#define TIMING_ANIMATION_SPEED_2   500  // milliseconds between animation frames for traffic type TRAFFIC_STATUS_JAM2
#define TIMING_ANIMATION_SPEED_3   800  // milliseconds between animation frames for traffic type TRAFFIC_STATUS_JAM3

#define LIMIT_MQTT_NUMRECONNECT    3
#define LIMIT_TRAFFIC_MAXID       16

#endif // INCLUDE_STAULU_CONSTANTS_H
