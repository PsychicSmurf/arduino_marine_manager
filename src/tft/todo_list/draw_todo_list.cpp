// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "draw_todo_list.h"
#include "../tft_handler.h"
#include "../draw_template.h"
#include "../../data/app_status.h"
#include "../../logger/logger.h"
#include "../../data/live_data.h"
#include "../../data/fixed_data.h"
#include "../../pages/todo_list_handler.h"
// --------------------------------------------------------------------------------
const uint8_t TODO_TEXT_BUFFER_SIZE = 20;
const uint8_t LEFT_RIGHT_BORDER = 4;
const uint8_t TOP_BOTTOM_BORDER = 12;
char todoTextBuffer[TODO_TEXT_BUFFER_SIZE];
const uint8_t PAGE_ONE_ENTRY_COUNT = 10;
const uint8_t PAGE_TWO_ENTRY_COUNT = 9;
const uint8_t PAGE_THREE_ENTRY_COUNT = 10;
// --------------------------------------------------------------------------------
void drawTodoList(const bool viewChanged)
{
    if (viewChanged)
    {
        drawTemplate(F("About"), F("ToDo List"), F("Param"));
    } // else already drawn

    switch (getAppStatus())
    {
        case PAGE_TODO_1: // 1-10 NEXT
            drawToDoRows(PAGE_ONE_ENTRY_COUNT, 0, PAGE_ONE_TODO_OFFSET, viewChanged);

            if (viewChanged)
            {
                drawButton(BUTTON_TYPE_NEXT);
            } // else already drawn

            break;

        case PAGE_TODO_2: // PREVIOUS 9-17 NEXT
            drawToDoRows(PAGE_TWO_ENTRY_COUNT, 1, PAGE_TWO_TODO_OFFSET, viewChanged);

            if (viewChanged)
            {
                drawButton(BUTTON_TYPE_PREVIOUS);
                drawButton(BUTTON_TYPE_NEXT);
            } // else already drawn

            break;

        case PAGE_TODO_3: // PREVIOUS 16-25
            drawToDoRows(PAGE_THREE_ENTRY_COUNT, 1, PAGE_THREE_TODO_OFFSET, viewChanged);

            if (viewChanged)
            {
                drawButton(BUTTON_TYPE_PREVIOUS);
            } // else already drawn

            break;

        default: // Error
            logString(F("TODO ERROR"));
            break;
    } // switch
}
// --------------------------------------------------------------------------------
void drawToDoRows(const uint8_t numberOfRows, const uint8_t startingRow, const uint8_t startingDataIndex,
                  const bool viewChanged)
{
    assert(numberOfRows < 12);
    assert(startingRow < 2);
    assert(startingDataIndex + numberOfRows - 1 < NUMBER_OF_ENTRIES);

    tft.setFont(&FreeSans9pt7b);
    tft.setTextColor(TFT_WHITE);

    uint8_t dataIndex = startingDataIndex;

    for (uint16_t index = startingRow; index < (startingRow + numberOfRows); index++)
    {
        uint16_t rowTop = (index * ROW_SPACING) + FIRST_ROW_TOP;

        drawToDoRow(dataIndex, rowTop, viewChanged);

        dataIndex++;
    } // for index

    setOrderOrEntryColourChanged(false);
}
// --------------------------------------------------------------------------------
void drawToDoRow(const uint8_t dataIndex, const uint16_t rowTop, const bool viewChanged)
{
    assert(rowTop <= TFT_HEIGHT);
    assert(dataIndex < NUMBER_OF_ENTRIES);

    uint8_t sortedDataIndex = getSortedLiveDataTimeIndex(dataIndex);
    bool orderOrColourChanged = getOrderOrEntryColourChanged();

    uint16_t row_col = TFT_WHITE;

    switch (getLiveDataCurrentTimeColour(sortedDataIndex))
    {
        case COLOUR_CATEGORY_GREEN:
            row_col = TFT_DARKGREEN;
            break;

        case COLOUR_CATEGORY_AMBER:
            row_col = TFT_ORANGE;
            break;

        case COLOUR_CATEGORY_RED:
            row_col = TFT_RED;
            break;
    } // switch

    if ((viewChanged == true) || (orderOrColourChanged == true))
    {
        tft.fillRect(COL_1_LEFT, rowTop, COL_1_RIGHT - COL_1_LEFT, ROW_HEIGHT, row_col);
        tft.fillRect(COL_2_LEFT, rowTop, COL_2_RIGHT - COL_2_LEFT, ROW_HEIGHT, row_col);

        sprintf(todoTextBuffer, "%d", (dataIndex + 1));
        centreText(todoTextBuffer, COL_1_LEFT, COL_1_RIGHT, rowTop + STRING_Y_OFFSET);

        leftAlignText(getFixedEntryName(sortedDataIndex), COL_2_LEFT + STRING_X_PADDING, rowTop + STRING_Y_OFFSET);
    } // else no need to draw backgrounds

    if ((viewChanged == true) || (orderOrColourChanged == true))
    {
        tft.fillRect(COL_3_LEFT, rowTop, COL_3_RIGHT - COL_3_LEFT, ROW_HEIGHT, row_col);
    }
    else
    {
        tft.fillRect(COL_3_LEFT + LEFT_RIGHT_BORDER, rowTop + TOP_BOTTOM_BORDER,
                     COL_3_RIGHT - COL_3_LEFT - (2 * LEFT_RIGHT_BORDER), ROW_HEIGHT - (2 * TOP_BOTTOM_BORDER), row_col);
    }

    getLiveDataCurrentTimeAsText(sortedDataIndex, todoTextBuffer, TODO_TEXT_BUFFER_SIZE);
    rightAlignText(todoTextBuffer, COL_3_RIGHT - STRING_X_PADDING, rowTop + STRING_Y_OFFSET);
}
// --------------------------------------------------------------------------------
