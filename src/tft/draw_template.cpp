// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "draw_template.h"
#include "../logger/logger.h"
#include "../timer/time_manager.h"
#include "../data/flash_handler.h"
// --------------------------------------------------------------------------------
// https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts
// --------------------------------------------------------------------------------
static const uint8_t TEXT_BUFFER_SIZE = 20;
static char textBuffer[TEXT_BUFFER_SIZE];
// --------------------------------------------------------------------------------
void drawTemplate(const __FlashStringHelper *button1, const __FlashStringHelper *title,
                  const __FlashStringHelper *button2)
{
    tft.fillScreen(TFT_BLACK);

    drawHeader(button1, button2, title);
    drawTimerBar();
}
// --------------------------------------------------------------------------------
void rightAlignText(const char *text, const uint16_t textRightX, const uint16_t textY)
{
    assert(strnlen(text, 50) < 50);
    assert(strnlen(text, 50) > 0);
    assert(textRightX <= TFT_WIDTH);
    assert(textY <= TFT_HEIGHT);

    uint16_t stringWidth = getStringWidth(text, ALIGN_RIGHT);
    tft.setCursor(textRightX - stringWidth, textY);
    tft.print(text);
}
// --------------------------------------------------------------------------------
void leftAlignText(const char *text, const uint16_t textLeftX, const uint16_t textY)
{
    assert(strnlen(text, 50) < 50);
    assert(strnlen(text, 50) > 0);
    assert(textLeftX <= TFT_WIDTH);
    assert(textY <= TFT_HEIGHT);

    tft.setCursor(textLeftX, textY);
    tft.print(text);
}
// --------------------------------------------------------------------------------
void centreText(const char *text, const uint16_t textLeftX, const uint16_t textRightX,  const uint16_t textY)
{
    assert(strnlen(text, 50) < 50);
    assert(strnlen(text, 50) > 0);
    assert(textLeftX < textRightX);
    assert(textRightX <= TFT_WIDTH);
    assert(textY <= TFT_HEIGHT);

    uint16_t stringWidth = getStringWidth(text, ALIGN_CENTRE);
    uint16_t x = ((textRightX - textLeftX) / 2) + textLeftX - (stringWidth / 2);

    tft.setCursor(x, textY);
    tft.print(text);
}
// --------------------------------------------------------------------------------
uint16_t getStringWidth(const char *inString, const AlignType &alignType)
{
    assert(strnlen(inString, 50) < 50);
    assert(strnlen(inString, 50) > 0);

    uint16_t w, h;
    int16_t x1, y1;

    tft.getTextBounds(inString, 0, 0, &x1, &y1, &w, &h);

    char singleChr[2];
    memcpy(singleChr, &inString[strlen(inString) - 1], 1);

    if (singleChr[0] == '1')
    {
        switch (alignType)
        {
            case ALIGN_CENTRE:
                w += 3;
                break;

            case ALIGN_RIGHT:
                w += 2;
                break;

            case ALIGN_LEFT:
                break;
        } // switch
    } // else not a thin number at the end

    return (w + x1);
}
// --------------------------------------------------------------------------------
void drawHeader(const __FlashStringHelper *button1, const __FlashStringHelper *button2,
                const __FlashStringHelper *title)
{
    tft.setFont(&FreeSansBold9pt7b);
    tft.setTextColor(TFT_BLACK);

    // Nav Buttons
    drawIndividualButton(BUTTON_NAV1, button1);
    drawIndividualButton(BUTTON_NAV2, button2);

    // Title
    tft.setTextColor(TFT_YELLOW);
    setCharArrayWithF(textBuffer, TEXT_BUFFER_SIZE, title);
    centreText(textBuffer, TFT_LEFT + BUTTON_WIDTH, TFT_RIGHT - BUTTON_WIDTH, STRING_Y_OFFSET);
}
// --------------------------------------------------------------------------------
void drawTimerBar()
{
    const uint16_t BAR_HEIGHT = 6;
    const uint16_t BAR_TOP = 42;

    uint16_t secondsLeft = getTimeTillNextSdSave();
    uint32_t barWidth = TFT_WIDTH * secondsLeft / SD_SAVE_PERIOD_SECONDS;
    uint16_t barColour;
    tft.fillRect(barWidth, BAR_TOP, TFT_WIDTH - barWidth, BAR_HEIGHT, TFT_DARKGREY);

    switch (secondsLeft / SD_SAVE_PERIOD_FIFTH_SECONDS)
    {
        case 5: // 300
        case 4: // 299 - 240
            barColour = TFT_DARKGREEN;
            break;

        case 3: // 239 - 180
            barColour = getGradientColour(TFT_DARKGREEN, TFT_ORANGE, SD_SAVE_PERIOD_FIFTH_SECONDS,
                                          secondsLeft - (SD_SAVE_PERIOD_FIFTH_SECONDS * 3));
            break;

        case 2: // 179 - 120
            barColour = TFT_ORANGE;
            break;

        case 1: // 119 - 60
            barColour = getGradientColour(TFT_ORANGE, TFT_RED, SD_SAVE_PERIOD_FIFTH_SECONDS,
                                          secondsLeft - SD_SAVE_PERIOD_FIFTH_SECONDS);
            break;

        case 0: // 59 - 0
            barColour = TFT_RED;
            break;
    } // switch

    tft.fillRect(TFT_LEFT, BAR_TOP, barWidth, BAR_HEIGHT, barColour);
}
// --------------------------------------------------------------------------------
uint16_t getGradientColour(const uint16_t colourTop, const uint16_t colourBottom, const uint16_t range,
                           const uint16_t value)
{
    assert(range > 0);
    assert(value <= range);

    // Note: Colour is RGB565
    int16_t retColour = 0x0000;
    const uint8_t NUMBER_OF_BITS_TO_SHIFT[3] = { 0, 5, 11 };
    const uint8_t BIT_MASK[3] = { 31, 63, 31 };

    for (int8_t index = 0; index < 3; index++) // 3 Colours = RGB
    {
        int16_t rgb1 = (colourTop >> NUMBER_OF_BITS_TO_SHIFT[index]) & BIT_MASK[index];
        int16_t rgb2 = (colourBottom >> NUMBER_OF_BITS_TO_SHIFT[index]) & BIT_MASK[index];
        int32_t diffScaled = abs(rgb1 - rgb2) * value / range;

        if (rgb1 > rgb2)
        {
            retColour |= ((rgb2 + diffScaled) << NUMBER_OF_BITS_TO_SHIFT[index]);
        }
        else
        {
            retColour |= ((rgb2 - diffScaled) << NUMBER_OF_BITS_TO_SHIFT[index]);
        }
    } // for index

    return retColour;
}
// --------------------------------------------------------------------------------
void drawButton(const ButtonType btype)
{
    switch (btype)
    {
        case BUTTON_TYPE_NEXT:
            drawIndividualButton(BUTTON_NEXT, F("Next"));
            break;

        case BUTTON_TYPE_PREVIOUS:
            drawIndividualButton(BUTTON_PREV, F("Previous"));
            break;
    } // switch
}
// --------------------------------------------------------------------------------
void drawIndividualButton(const ButtonCoords coords, const __FlashStringHelper *text)
{
    setCharArrayWithF(textBuffer, TEXT_BUFFER_SIZE, text);

    if (strlen(textBuffer) != 0)
    {
        tft.fillRect(coords.topLeftX, coords.topLeftY, coords.bottomRightX - coords.topLeftX,
                     coords.bottomRightY - coords.topLeftY, TFT_DARKGREY);
        tft.drawRect(coords.topLeftX, coords.topLeftY, coords.bottomRightX - coords.topLeftX,
                     coords.bottomRightY - coords.topLeftY, TFT_LIGHTGREY);
        centreText(textBuffer, coords.topLeftX, coords.bottomRightX, coords.topLeftY + STRING_Y_OFFSET);
    } // else empty button so don't draw
}
// --------------------------------------------------------------------------------
