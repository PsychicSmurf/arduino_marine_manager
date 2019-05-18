// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "draw_params_summary.h"
#include "../tft_handler.h"
#include "../draw_template.h"
#include "../../data/app_status.h"
#include "../../logger/logger.h"
#include "../../data/live_data.h"
#include "../../data/fixed_data.h"
// --------------------------------------------------------------------------------
const uint8_t PARAMS_TEXT_BUFFER_SIZE = 30;
char paramsTextBuffer[PARAMS_TEXT_BUFFER_SIZE];
// --------------------------------------------------------------------------------
void drawParamSummary()
{
    drawTemplate(F("Home"), F("Parameter Summary"), F("Chore"));
    drawParamsRows(11, 0, 14);
}
// --------------------------------------------------------------------------------
void drawParamsRows(const uint8_t numberOfRows, const uint8_t startingRow, const uint8_t startingDataIndex)
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

        drawParamsRow(dataIndex, rowTop);

        dataIndex++;
    } // for index
}
// --------------------------------------------------------------------------------
void drawParamsRow(const uint8_t dataIndex, const uint16_t rowTop)
{
    assert(rowTop <= TFT_HEIGHT);
    assert(dataIndex < NUMBER_OF_ENTRIES);

    uint16_t rowCol = TFT_WHITE;

    switch (getLiveDataCurrentValueColour(dataIndex))
    {
        case COLOUR_CATEGORY_GREEN:
            rowCol = TFT_DARKGREEN;
            break;

        case COLOUR_CATEGORY_AMBER:
            rowCol = TFT_ORANGE;
            break;

        case COLOUR_CATEGORY_RED:
            rowCol = TFT_RED;
            break;
    } // switch

    tft.fillRect(COL_1_LEFT, rowTop, COL_1_RIGHT - COL_1_LEFT, ROW_HEIGHT, rowCol);
    tft.fillRect(COL_2_LEFT, rowTop, COL_2_RIGHT - COL_2_LEFT, ROW_HEIGHT, rowCol);
    tft.fillRect(COL_3_LEFT, rowTop, COL_3_RIGHT - COL_3_LEFT, ROW_HEIGHT, rowCol);

    sprintf(paramsTextBuffer, "%d", (dataIndex - 13));
    centreText(paramsTextBuffer, COL_1_LEFT, COL_1_RIGHT, rowTop + STRING_Y_OFFSET);

    sprintf(paramsTextBuffer, "%s (%s)", getFixedEntryName(dataIndex), getFixedEntrySymbol(dataIndex));
    leftAlignText(paramsTextBuffer, COL_2_LEFT + STRING_X_PADDING, rowTop + STRING_Y_OFFSET);

    getLiveDataCurrentFormattedValue(dataIndex, paramsTextBuffer, PARAMS_TEXT_BUFFER_SIZE);
    sprintf(paramsTextBuffer, "%s %s", paramsTextBuffer, getFixedEntryNameUnits(dataIndex));
    rightAlignText(paramsTextBuffer, COL_3_RIGHT - STRING_X_PADDING, rowTop + STRING_Y_OFFSET);
}
// --------------------------------------------------------------------------------
