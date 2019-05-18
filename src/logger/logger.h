#ifndef LOGGER_H
#define LOGGER_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------
#include "assert_handler.h"
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
#define BLANK_LINE ""
// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
void setupLogger();
void logString(const char *log_txt);
void logString(const __FlashStringHelper *string);
void logString(uint8_t value);
void logString(uint16_t value);
void logString(uint32_t value);
void logString(const bool value);
// --------------------------------------------------------------------------------
#endif // LOGGER_H
