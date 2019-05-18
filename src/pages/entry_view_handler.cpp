// --------------------------------------------------------------------------------
#include "entry_view_handler.h"
#include "../tft/single_entry/draw_single_entry.h"
#include "../logger/logger.h"
#include "../data/app_status.h"
#include "../data/live_data.h"
// --------------------------------------------------------------------------------
void viewPageTick(const TouchPoint &touchPoint, const bool viewChanged)
{
    uint8_t entryIndex = getSelectedEntryIndex();
    EntryType entryType = getFixedEntryType(entryIndex);

    if (viewChanged)
    {
        drawSingleEntry(entryIndex, entryType);
    } // else already drawn previously

    if (touchPoint.active)
    {
        if (isTouchInButton(touchPoint, BUTTON_NAV1))
        {
            setAppStatus(PAGE_TODO_1);
        }
        else if (isTouchInButton(touchPoint, BUTTON_NAV2))
        {
            switch (entryType)
            {
                case entryType_PARAM:
                    setCalculatorEntryIndex(entryIndex);
                    setAppStatus(PAGE_CALCULATOR);
                    break;

                case entryType_CHORE:
                    // TODO
                    break;

                default:
                    // ERROR
                    break;
            } // switch
        }
    } // else no user input
}
// --------------------------------------------------------------------------------
