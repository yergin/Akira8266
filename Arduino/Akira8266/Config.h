#pragma once

#define SERIAL_DEBUG

#ifdef SERIAL_DEBUG
constexpr int SERIAL_BAUD = 115200;
#define SERIAL_INIT() Serial.begin(SERIAL_BAUD);
#define SERIAL_PRINT(_x) Serial.print(_x);
#define SERIAL_PRINTLN(_x) Serial.println(_x);
#else
#define SERIAL_INIT() ;
#define SERIAL_PRINT(_x) ;
#define SERIAL_PRINTLN(_x) ;
#endif

constexpr int STATUS_LED_PIN = 2;
constexpr int LED_STRIP_COUNT = 76;
constexpr int LED_STRIP_DATA_PIN = 5;
constexpr int LED_STRIP_CLOCK_PIN = 4;
constexpr int LED_STRIP_MHZ = 10;

constexpr int FPS = 50;
