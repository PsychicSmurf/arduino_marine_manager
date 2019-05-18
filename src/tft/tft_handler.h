#ifndef TFT_HANDLER_H
#define TFT_HANDLER_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
//#include <Fonts/FreeSans14pt7b.h>
//#include <Fonts/FreeSans15pt7b.h>
//#include <Fonts/FreeSans16pt7b.h>
//#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
extern MCUFRIEND_kbv tft;
const uint32_t TFT_HEIGHT = 480;
const uint32_t TFT_WIDTH = 320;
const uint16_t TFT_TOP = 0;
const uint16_t TFT_LEFT = 0;
const uint16_t TFT_RIGHT = 319;
// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
void setupTft();
// --------------------------------------------------------------------------------
#endif // TFT_HANDLER_H

/*
#define TFT_BLACK       0x0000
#define TFT_NAVY        0x000F
#define TFT_DARKGREEN   0x03E0
#define TFT_DARKCYAN    0x03EF
#define TFT_MAROON      0x7800
#define TFT_PURPLE      0x780F
#define TFT_OLIVE       0x7BE0
#define TFT_LIGHTGREY   0xC618
#define TFT_DARKGREY    0x7BEF
#define TFT_BLUE        0x001F
#define TFT_GREEN       0x07E0
#define TFT_CYAN        0x07FF
#define TFT_RED         0xF800
#define TFT_MAGENTA     0xF81F
#define TFT_YELLOW      0xFFE0
#define TFT_WHITE       0xFFFF
#define TFT_ORANGE      0xFD20
#define TFT_GREENYELLOW 0xAFE5
#define TFT_PINK        0xF81F
*/