#ifndef CONFIRMATION_HANDLER_H
#define CONFIRMATION_HANDLER_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "../input/touch_screen_handler.h"
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
void confirmationPageTick(const TouchPoint &touchPoint, bool viewChanged);
// --------------------------------------------------------------------------------
#endif // CONFIRMATION_HANDLER_H
