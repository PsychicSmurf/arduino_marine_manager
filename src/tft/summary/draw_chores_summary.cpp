// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "draw_chores_summary.h"
#include "../tft_handler.h"
#include "../draw_template.h"
#include "../../data/app_status.h"
#include "../../logger/logger.h"
#include "../../data/live_data.h"
#include "../../data/fixed_data.h"
// --------------------------------------------------------------------------------
const uint8_t CHORES_TEXT_BUFFER_SIZE = 30;
char chores_text_buffer[CHORES_TEXT_BUFFER_SIZE];
// --------------------------------------------------------------------------------
void drawChoresSummary()
{
    drawTemplate(F("Param"), F("Chore Summary "), F("Home"));

    switch (getAppStatus())
    {
        case PAGE_CHORE_STATUS_1: // 1-10 NEXT
            drawChoresRows(10, 0, 0);
            drawButton(BUTTON_TYPE_NEXT);
            break;

        case PAGE_CHORE_STATUS_2: // PREV 5-14
            drawChoresRows(10, 1, 6);
            drawButton(BUTTON_TYPE_PREVIOUS);
            break;

        default: // Error
            logString(F("TODO ERROR"));
            break;
    } // switch
}
// --------------------------------------------------------------------------------
void drawChoresRows(const uint8_t numberOfRows, const uint8_t startingRow, const uint8_t startingDataIndex)
{
    assert(numberOfRows < 12);
    assert(startingDataIndex + numberOfRows <= TFT_HEIGHT);

    tft.setFont(&FreeSans9pt7b);
    tft.setTextColor(TFT_WHITE);

    uint8_t dataIndex = startingDataIndex;

    for (uint16_t index = startingRow; index < (startingRow + numberOfRows); index++)
    {
        uint16_t rowTop = (index * ROW_SPACING) + FIRST_ROW_TOP;

        drawChoresRow(dataIndex, rowTop);

        dataIndex++;
    } // for index
}
// --------------------------------------------------------------------------------
void drawChoresRow(const uint8_t dataIndex, const uint16_t rowTop)
{
    assert(dataIndex < NUMBER_OF_ENTRIES);
    assert(rowTop <= TFT_HEIGHT);

    uint16_t row_col = TFT_WHITE;

    switch (getLiveDataCurrentTimeColour(dataIndex))
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

    tft.fillRect(COL_1_LEFT, rowTop, COL_1_RIGHT - COL_1_LEFT, ROW_HEIGHT, row_col);
    tft.fillRect(COL_2_LEFT, rowTop, COL_2_RIGHT - COL_2_LEFT, ROW_HEIGHT, row_col);

    sprintf(chores_text_buffer, "%d", (dataIndex + 1));
    centreText(chores_text_buffer, COL_1_LEFT, COL_1_RIGHT, rowTop + STRING_Y_OFFSET);

    leftAlignText(getFixedEntryName(dataIndex), COL_2_LEFT + STRING_X_PADDING, rowTop + STRING_Y_OFFSET);

    tft.fillRect(COL_3_LEFT, rowTop, COL_3_RIGHT - COL_3_LEFT, ROW_HEIGHT, row_col);
    getLiveDataCurrentRawTimeAsText(dataIndex, chores_text_buffer, CHORES_TEXT_BUFFER_SIZE);
    rightAlignText(chores_text_buffer, COL_3_RIGHT - STRING_X_PADDING, rowTop + STRING_Y_OFFSET);
}
// --------------------------------------------------------------------------------
