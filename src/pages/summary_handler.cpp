// --------------------------------------------------------------------------------
#include "summary_handler.h"
#include "../data/app_status.h"
#include "../tft/summary/draw_chores_summary.h"
#include "../tft/summary/draw_params_summary.h"
#include "../logger/logger.h"
// --------------------------------------------------------------------------------
void summaryPageTick(const TouchPoint &touchPoint, const bool viewChanged)
{
    CurrentPage page = getAppStatus();

    if (viewChanged)
    {
        if (page == PAGE_PARAMETER_STATUS)
        {
            drawParamSummary();
        }
        else
        {
            drawChoresSummary();
        }
    } // else no drawing needed

    if (touchPoint.active)
    {
        switch (page)
        {
            default:
            case PAGE_PARAMETER_STATUS:
                if (isTouchInButton(touchPoint, BUTTON_NAV1))
                {
                    setAppStatus(PAGE_TODO_1);
                } // else not first menu button
                else if (isTouchInButton(touchPoint, BUTTON_NAV2))
                {
                    setAppStatus(PAGE_CHORE_STATUS_1);
                } // else not first menu button

                break;

            case PAGE_CHORE_STATUS_1:
                if (isTouchInButton(touchPoint, BUTTON_NAV1))
                {
                    setAppStatus(PAGE_PARAMETER_STATUS);
                }
                else if (isTouchInButton(touchPoint, BUTTON_NAV2))
                {
                    setAppStatus(PAGE_TODO_1);
                } // else not first menu button
                else if (isTouchInButton(touchPoint, BUTTON_NEXT))
                {
                    setAppStatus(PAGE_CHORE_STATUS_2);
                }

                break;

            case PAGE_CHORE_STATUS_2:
                if (isTouchInButton(touchPoint, BUTTON_NAV1))
                {
                    setAppStatus(PAGE_PARAMETER_STATUS);
                }
                else if (isTouchInButton(touchPoint, BUTTON_NAV2))
                {
                    setAppStatus(PAGE_TODO_1);
                } // else not first menu button
                else if (isTouchInButton(touchPoint, BUTTON_PREV))
                {
                    setAppStatus(PAGE_CHORE_STATUS_1);
                }

                break;
        } // switch
    } // else no touch action
}
// --------------------------------------------------------------------------------
