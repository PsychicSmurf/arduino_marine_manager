#ifndef CALCULATOR_HANDLER_H
#define CALCULATOR_HANDLER_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "../tft/calculator/draw_calculator.h"
#include "../input/touch_screen_handler.h"
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
extern ButtonCoords buttonCoords[3][4];
// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
void calculatorPageTick(const TouchPoint &touchPoint, bool viewChanged, bool calculatorUpdated);
// --------------------------------------------------------------------------------
#endif // CALCULATOR_HANDLER_H
