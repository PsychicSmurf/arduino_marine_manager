// --------------------------------------------------------------------------------
#include "confirmation_handler.h"
#include "../tft/confirmation/draw_confirmation.h"
#include "../logger/logger.h"
// --------------------------------------------------------------------------------
void confirmationPageTick(const TouchPoint &touchPoint, const bool viewChanged)
{
    // TODO
    if (viewChanged)
    {
        drawConfirmation();
    }
}
// --------------------------------------------------------------------------------
