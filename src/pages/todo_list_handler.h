#ifndef TODO_LIST_HANDLER_H
#define TODO_LIST_HANDLER_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "../input/touch_screen_handler.h"
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
extern const uint8_t PAGE_ONE_TODO_OFFSET;
extern const uint8_t PAGE_TWO_TODO_OFFSET;
extern const uint8_t PAGE_THREE_TODO_OFFSET;
// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
void todoPageTick(const TouchPoint &touchPoint, bool viewChanged, bool time_updated);
// --------------------------------------------------------------------------------
#endif // TODO_LIST_HANDLER_H
