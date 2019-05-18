// --------------------------------------------------------------------------------
#include "./about_handler.h"
#include "../data/app_status.h"
#include "../tft/about/draw_about.h"
#include "../logger/logger.h"
#include "../data/live_data.h"
#include "../timer/time_manager.h"
// --------------------------------------------------------------------------------
void aboutPageTick(const TouchPoint &touchPoint, const bool viewChanged)
{
    if (viewChanged)
    {
        drawAbout();
    } // else no drawing needed

    if (touchPoint.active)
    {
        if (isTouchInButton(touchPoint, BUTTON_NAV1))
        {
            setAppStatus(PAGE_TODO_1);
        }
        else if (isTouchInButton(touchPoint, BUTTON_ABOUT_1))
        {
            advanceOneHour();
        }
        else if (isTouchInButton(touchPoint, BUTTON_ABOUT_2))
        {
            setCurrentTimesToZero();
        }
        else if (isTouchInButton(touchPoint, BUTTON_ABOUT_3))
        {
            resetLiveData();
        }
    } // else no touch action
}
// --------------------------------------------------------------------------------
