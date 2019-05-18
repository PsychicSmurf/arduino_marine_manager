#ifndef DRAW_CALCULATOR_H
#define DRAW_CALCULATOR_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------
#include "../draw_template.h"
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
const uint8_t BUTTON_COLUMNS = 3;
const uint8_t BUTTON_ROWS = 4;
extern ButtonCoords buttonCoords[BUTTON_COLUMNS][BUTTON_ROWS];
const uint8_t CALC_BUTTON_COUNT = 12;
const char calcChars[CALC_BUTTON_COUNT] = { '7', '8', '9', '4', '5', '6', '1', '2', '3', 'C', '0', '>' };
// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
void setupCalculator();
void drawCalculator();
void drawCalcButtons();
void drawCalcText();
void drawCalcValue();
// --------------------------------------------------------------------------------
#endif // DRAW_CALCULATOR_H
