// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "flash_handler.h"
#include "../logger/logger.h"
// --------------------------------------------------------------------------------
// Variables
// \arduino_marine_manager\documents\progmem.c
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
void setCharArrayWithF(char *charArray, const uint8_t arraySize, const __FlashStringHelper *flashString)
{
    assert(arraySize > 0);

    charArray[0] = 0;

    if (flashString != NULL)
    {
        strlcpy_P(charArray, (const char PROGMEM *)flashString, arraySize);
    } // else leave empty
}
// --------------------------------------------------------------------------------
void setCharArrayWithProgmem(char *charArray, const uint8_t arraySize, const char *flashString)
{
    assert(arraySize > 0);

    charArray[0] = 0;

    if (flashString != NULL)
    {
        strlcpy_P(charArray, (const char PROGMEM *)flashString, arraySize);
    } // else leave empty
}
// --------------------------------------------------------------------------------
