// --------------------------------------------------------------------------------
#include "todo_list_handler.h"
#include "../data/app_status.h"
#include "../data/fixed_data.h"
#include "../tft/todo_list/draw_todo_list.h"
#include "../logger/logger.h"
#include "../data/live_data.h"
// --------------------------------------------------------------------------------
const uint8_t PAGE_ONE_TODO_OFFSET = 0;
const uint8_t PAGE_TWO_TODO_OFFSET = 9;
const uint8_t PAGE_THREE_TODO_OFFSET = 17;
// --------------------------------------------------------------------------------
void todoPageTick(const TouchPoint &touchPoint, const bool viewChanged, const bool timeUpdated)
{
    if ((viewChanged == true) || (timeUpdated == true))
    {
        drawTodoList(viewChanged);
    } // else no drawing needed

    if (touchPoint.active)
    {
        CurrentPage page = getAppStatus();

        if (isTouchInButton(touchPoint, BUTTON_NAV1))
        {
            setAppStatus(PAGE_ABOUT);
        }
        else if (isTouchInButton(touchPoint, BUTTON_NAV2))
        {
            setAppStatus(PAGE_PARAMETER_STATUS);
        }
        else if (isTouchInButton(touchPoint, BUTTON_PREV) && ((page == PAGE_TODO_2) || (page == PAGE_TODO_3)))
        {
            setAppStatus((CurrentPage)(page - 1));
        }
        else if (isTouchInButton(touchPoint, BUTTON_NEXT) && ((page == PAGE_TODO_1) || (page == PAGE_TODO_2)))
        {
            setAppStatus((CurrentPage)(page + 1));
        }
        else
        {
            for (uint8_t index = 0; index < 11; index++)
            {
                uint16_t rowTop = (index * ROW_SPACING) + FIRST_ROW_TOP;

                if ((touchPoint.ty > rowTop) && (touchPoint.ty < rowTop + ROW_SPACING))
                {
                    uint8_t selectedIndex = index;

                    if (page == PAGE_TODO_2)
                    {
                        selectedIndex += PAGE_TWO_TODO_OFFSET - 1; // 1 = Previous Button
                    }
                    else if (page == PAGE_TODO_3)
                    {
                        selectedIndex += PAGE_THREE_TODO_OFFSET - 1; // 1 = Previous Button
                    }

                    if (getFixedEntryType(selectedIndex) == entryType_PARAM)
                    {
                        setAppStatus(PAGE_PARAMETER_VIEW, getSortedLiveDataTimeIndex(selectedIndex));
                    }
                    else
                    {
                        setAppStatus(PAGE_CHORE_VIEW, getSortedLiveDataTimeIndex(selectedIndex));
                    }
                } // else not this row
            } // for index
        }
    } // else no touch action
}
// --------------------------------------------------------------------------------
