#ifndef FLASH_HANDLER_H
#define FLASH_HANDLER_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------
#include <Arduino.h>
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
void setCharArrayWithF(char *charArray, uint8_t arraySize, const __FlashStringHelper *flashString);
void setCharArrayWithProgmem(char *charArray, uint8_t arraySize, const char *flashString);
// --------------------------------------------------------------------------------
#endif // FLASH_HANDLER_H