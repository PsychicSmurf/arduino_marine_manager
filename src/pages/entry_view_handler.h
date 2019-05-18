#ifndef ENTRY_VIEW_HANDLER_H
#define ENTRY_VIEW_HANDLER_H
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
void viewPageTick(const TouchPoint &touchPoint, bool viewChanged);
// --------------------------------------------------------------------------------
#endif // ENTRY_VIEW_HANDLER_H
