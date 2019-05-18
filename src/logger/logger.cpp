// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "logger.h"
#include "serial_handler.h"
// --------------------------------------------------------------------------------
void setupLogger()
{
    setupSerial();
}
// --------------------------------------------------------------------------------
void logString(const char *logTxt)
{
    Serial.println(logTxt);
    Serial.flush();
}
// --------------------------------------------------------------------------------
void logString(const __FlashStringHelper *logTxt)
{
    Serial.println(logTxt);
    Serial.flush();
}
// --------------------------------------------------------------------------------
void logString(const uint8_t value)
{
    logString((uint32_t)value);
}
// --------------------------------------------------------------------------------
void logString(const uint16_t value)
{
    logString((uint32_t)value);
}
// --------------------------------------------------------------------------------
void logString(const uint32_t value)
{
    char tmp[10];

    sprintf(tmp, "%lu", value);

    logString(tmp);
}
// --------------------------------------------------------------------------------
void logString(const bool value)
{
    logString(value ? F("True") : F("False"));
}
// --------------------------------------------------------------------------------
