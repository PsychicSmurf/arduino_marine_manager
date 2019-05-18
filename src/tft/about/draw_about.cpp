// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "draw_about.h"
#include "../../data/app_status.h"
#include "../tft_handler.h"
#include "../../logger/logger.h"
// --------------------------------------------------------------------------------
void drawAbout()
{
    drawTemplate(F("Home"), F("About"), F(""));

    drawIndividualButton(BUTTON_ABOUT_1, F("Advance One Hour"));
    drawIndividualButton(BUTTON_ABOUT_2, F("Set Times to ZERO"));
    drawIndividualButton(BUTTON_ABOUT_3, F("Reset ALL Data"));

    centreText("Marine Manager V0.02", TFT_LEFT, TFT_RIGHT, (2.5 * ROW_SPACING) + ROW_HEIGHT + FIRST_ROW_TOP);
    centreText("(c) 2019 David Lewis", TFT_LEFT, TFT_RIGHT, (6.5 * ROW_SPACING) + ROW_HEIGHT + FIRST_ROW_TOP);
}
// --------------------------------------------------------------------------------

