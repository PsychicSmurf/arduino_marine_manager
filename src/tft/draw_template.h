#ifndef DRAW_TEMPLATE_H
#define DRAW_TEMPLATE_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------
#include "tft_handler.h"
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
enum AlignType
{
    ALIGN_LEFT,
    ALIGN_RIGHT,
    ALIGN_CENTRE
};
enum ButtonType
{
    BUTTON_TYPE_NEXT,
    BUTTON_TYPE_PREVIOUS
};
const uint16_t STRING_Y_OFFSET = 25;
const uint16_t STRING_X_PADDING = 6;
const uint16_t FIRST_ROW_TOP = 50;
const uint16_t ROW_SPACING = 39;
const uint16_t ROW_HEIGHT = 38;
const uint16_t COL_1_LEFT = 0;
const uint16_t COL_1_RIGHT = 41;
const uint16_t COL_2_LEFT = 42;
const uint16_t COL_2_RIGHT = 216;
const uint16_t COL_3_LEFT = 217;
const uint16_t COL_3_RIGHT = 319;

const uint16_t HEADER_HEIGHT = 40;
const uint16_t BUTTON_WIDTH = 70;
struct ButtonCoords
{
    uint16_t topLeftX;
    uint16_t topLeftY;
    uint16_t bottomRightX;
    uint16_t bottomRightY;
};
const ButtonCoords BUTTON_NAV1 =   { TFT_LEFT, TFT_TOP,
                                     TFT_LEFT + BUTTON_WIDTH, TFT_TOP + HEADER_HEIGHT
                                   };
const ButtonCoords BUTTON_NAV2 =   { TFT_WIDTH - BUTTON_WIDTH, TFT_TOP,
                                     TFT_WIDTH, TFT_TOP + HEADER_HEIGHT
                                   };
const ButtonCoords BUTTON_PREV =   { TFT_LEFT + BUTTON_WIDTH, FIRST_ROW_TOP,
                                     TFT_WIDTH - BUTTON_WIDTH,  FIRST_ROW_TOP + ROW_HEIGHT
                                   };
const ButtonCoords BUTTON_NEXT =   { TFT_LEFT + BUTTON_WIDTH, (10 * ROW_SPACING) + FIRST_ROW_TOP,
                                     TFT_WIDTH - BUTTON_WIDTH, (10 * ROW_SPACING) + ROW_HEIGHT + FIRST_ROW_TOP
                                   };

const uint32_t GRAPH_TOP = 268;
const uint32_t GRAPH_HEIGHT = 212;
const uint32_t GRAPH_BOTTOM = GRAPH_TOP + GRAPH_HEIGHT;
const uint32_t GRAPH_BORDER = 10;

const uint32_t RGR_RED = 39;
const uint32_t RGR_AMBER = 25;
const uint32_t RGR_GREEN = 36;
const uint32_t RGR_GRADIENT_COLOUR_COUNT = 12;

const uint32_t RYG_RED = 45;
const uint32_t RYG_AMBER = 35;
const uint32_t RYG_GREEN = 62;
const uint32_t RYG_GRADIENT_COLOUR_COUNT = 35;
// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
void drawTemplate(const __FlashStringHelper *button1, const __FlashStringHelper *button2,
                  const __FlashStringHelper *title);
void leftAlignText(const char *text, uint16_t textLeftX, uint16_t textY);
void rightAlignText(const char *text, uint16_t textRightX, uint16_t textY);
void centreText(const char *text, uint16_t textLeftX, uint16_t textRightX, uint16_t textY);
uint16_t getGradientColour(uint16_t colour_top, uint16_t colour_bottom, uint16_t range, uint16_t value);
uint16_t getStringWidth(const char *inString, const AlignType &alignType);
void drawHeader(const __FlashStringHelper *button1, const __FlashStringHelper *button2,
                const __FlashStringHelper *title);
void drawTimerBar();
void drawButton(ButtonType btype);
void drawIndividualButton(ButtonCoords coords, const __FlashStringHelper *text);
// --------------------------------------------------------------------------------
#endif // DRAW_TEMPLATE_H

