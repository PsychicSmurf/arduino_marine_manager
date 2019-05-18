// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "draw_confirmation.h"
#include "../tft_handler.h"
#include "../draw_template.h"
#include "../../logger/logger.h"
// --------------------------------------------------------------------------------
void drawConfirmation()
{
    drawTemplate(F("Cancel"), F(""), F("Confirmation"));
}
// --------------------------------------------------------------------------------
