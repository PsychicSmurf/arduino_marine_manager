// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "draw_calculator.h"
#include "../../data/live_data.h"
#include "../../data/fixed_data.h"
#include "../tft_handler.h"
#include "../../logger/logger.h"
// --------------------------------------------------------------------------------
static const uint16_t CALC_BORDER = 2;

static const uint16_t CALC_TITLE_Y = 50;

static const uint16_t CALC_VALUE_X = 31;
static const uint16_t CALC_VALUE_Y = 91;
static const uint16_t CALC_VALUE_W = 256;
static const uint16_t CALC_VALUE_H = 66;
static const uint16_t CALC_VALUE_TEXT_Y_OFFSET = 49;
static const uint16_t CALC_VALUE_TEXT_X_OFFSET = 16;

static const uint16_t CALC_TYPICAL_Y = 159;

static const uint16_t CALC_BUTTON_topY = 200;
static const uint16_t CALC_BUTTON_LEFT_X = 31;
static const uint16_t CALC_BUTTON_WIDTH = 85;
static const uint16_t CALC_BUTTON_SPACING = 4;
static const uint16_t CALC_BUTTON_HEIGHT = 66;

static const uint8_t CALC_BUFFER_SIZE = 32;
char calcBufferOne[CALC_BUFFER_SIZE];
char calcBufferTwo[CALC_BUFFER_SIZE];

static const uint16_t TFT_DARK_RED    = 0x6800;
static const uint16_t TFT_DARK_GREEN  = 0x1B40;
static const uint16_t TFT_DARK_YELLOW = 0x6B40;
static const uint16_t TFT_VALUE_COL   = 0x1042;

ButtonCoords buttonCoords[BUTTON_COLUMNS][BUTTON_ROWS];
// --------------------------------------------------------------------------------
void setupCalculator()
{
    for (uint8_t indexX = 0; indexX < BUTTON_COLUMNS; indexX++)
    {
        for (uint8_t indexY = 0; indexY < BUTTON_ROWS; indexY++)
        {
            buttonCoords[indexX][indexY].topLeftX = (indexX * (CALC_BUTTON_WIDTH + CALC_BUTTON_SPACING)) + CALC_BUTTON_LEFT_X;
            buttonCoords[indexX][indexY].topLeftY = (indexY * (CALC_BUTTON_HEIGHT + CALC_BUTTON_SPACING)) + CALC_BUTTON_topY;
            buttonCoords[indexX][indexY].bottomRightX = buttonCoords[indexX][indexY].topLeftX + CALC_BUTTON_WIDTH;
            buttonCoords[indexX][indexY].bottomRightY = buttonCoords[indexX][indexY].topLeftY + CALC_BUTTON_HEIGHT;
        } // for indindexYx_y
    } // for indexX
}
// --------------------------------------------------------------------------------
void drawCalculator()
{
    drawTemplate(F("Cancel"), F("Calculator"), F(""));

    drawCalcText();
    drawCalcValue();

    drawCalcButtons();
}
// --------------------------------------------------------------------------------
void drawCalcText()
{
    tft.setFont(&FreeSans12pt7b);
    tft.setTextColor(TFT_WHITE);

    sprintf(calcBufferOne, "%s (%s)", getFixedEntryName(getCalculatorEntryIndex()),
            getFixedEntrySymbol(getCalculatorEntryIndex()));
    centreText(calcBufferOne, TFT_LEFT, TFT_RIGHT, CALC_TITLE_Y + STRING_Y_OFFSET);

    getFormattedValue(getFixedTypicalValue(getCalculatorEntryIndex()),
                      getFixedValueDecimalPlaces(getCalculatorEntryIndex()), calcBufferOne, CALC_BUFFER_SIZE);

    sprintf(calcBufferTwo, "Typical: %s %s", calcBufferOne, getFixedEntryNameUnits(getCalculatorEntryIndex()));
    centreText(calcBufferTwo, TFT_LEFT, TFT_RIGHT, CALC_TYPICAL_Y + STRING_Y_OFFSET);
}
// --------------------------------------------------------------------------------
void drawCalcValue()
{
    const GraphRanges graphData = getGraphRanges(getCalculatorEntryIndex());
    const uint8_t dp = getFixedValueDecimalPlaces(getCalculatorEntryIndex());

    tft.setFont(&FreeSans24pt7b);

    tft.fillRect(CALC_VALUE_X, CALC_VALUE_Y, CALC_VALUE_W, CALC_VALUE_H, TFT_VALUE_COL);
    tft.drawRect(CALC_VALUE_X - 1, CALC_VALUE_Y - 1, CALC_VALUE_W + 2, CALC_VALUE_H + 2, TFT_WHITE);

    uint16_t valueColour = TFT_GREEN;

    if ((getCalculatorValue() < graphData.bottomAmber) || (getCalculatorValue() > graphData.topAmber))
    {
        valueColour = TFT_RED;
    }
    else if ((getCalculatorValue() < graphData.bottomGreen) || (getCalculatorValue() > graphData.topGreen))
    {
        valueColour = TFT_YELLOW;
    }

    tft.setTextColor(valueColour);
    getFormattedValue(getCalculatorValue(), dp, calcBufferOne, CALC_BUFFER_SIZE);
    rightAlignText(calcBufferOne, CALC_VALUE_X + CALC_VALUE_W - CALC_VALUE_TEXT_X_OFFSET,
                   CALC_VALUE_Y + CALC_VALUE_TEXT_Y_OFFSET);
}
// --------------------------------------------------------------------------------
void drawCalcButtons()
{
    tft.setFont(&FreeSans24pt7b);
    tft.setTextColor(TFT_WHITE);

    for (uint8_t column = 0; column < 3; column++)
    {
        for (uint8_t row = 0; row < 4; row++)
        {
            uint16_t bc = TFT_DARK_YELLOW;

            if (row == 3)
            {
                if (column == 0)
                {
                    bc = TFT_DARK_RED;
                }
                else if (column == 2)
                {
                    bc = TFT_DARK_GREEN;
                }
            } // else not the bottom row

            tft.fillRect(buttonCoords[column][row].topLeftX,
                         buttonCoords[column][row].topLeftY,
                         buttonCoords[column][row].bottomRightX - buttonCoords[column][row].topLeftX,
                         buttonCoords[column][row].bottomRightY - buttonCoords[column][row].topLeftY,
                         bc);

            tft.drawRect(buttonCoords[column][row].topLeftX,
                         buttonCoords[column][row].topLeftY,
                         buttonCoords[column][row].bottomRightX - buttonCoords[column][row].topLeftX,
                         buttonCoords[column][row].bottomRightY - buttonCoords[column][row].topLeftY,
                         TFT_WHITE);

            char cs[2] = { 0, 0 };

            cs[0] = calcChars[row * 3 + column];
            uint8_t cw = getStringWidth(cs, ALIGN_CENTRE);

            tft.setCursor(buttonCoords[column][row].topLeftX + ((CALC_BUTTON_WIDTH - cw) / 2),
                          buttonCoords[column][row].topLeftY + 48);
            tft.print(cs);
        } // for row
    } // for column
}
// --------------------------------------------------------------------------------
