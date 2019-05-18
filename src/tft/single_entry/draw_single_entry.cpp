// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "draw_single_entry.h"
#include "../tft_handler.h"
#include "../draw_template.h"
#include "../../data/live_data.h"
#include "../../logger/logger.h"
#include "graphs/draw_graph.h"
// --------------------------------------------------------------------------------
char singleEntryTmp[20];
const uint8_t BUFFER_SIZE = 16;
char bufferOne[BUFFER_SIZE];
char bufferTwo[BUFFER_SIZE];
char bufferThree[BUFFER_SIZE];
const uint16_t TITLE_TEXT_Y = 80;
const uint16_t VALUE_TEXT_Y = 108;
const uint16_t TIME_TEXT_Y = 136;
const uint16_t RED_TEXT_Y = 204;
const uint16_t AMBER_TEXT_Y = 230;
const uint16_t GREEN_TEXT_Y = 256;
// --------------------------------------------------------------------------------
void drawSingleEntry(const uint8_t entryIndex, const EntryType entryType)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    switch (entryType)
    {
        case entryType_PARAM:
            drawTemplate(F("Home"), F("Parameter View"), F("Add"));
            drawParam(entryIndex);
            break;

        case entryType_CHORE:
            drawTemplate(F("Home"), F("Chore View"), F("Add"));
            drawChore(entryIndex);
            break;

        default:
            drawTemplate(F("Home"), F("Error"), F("Add"));
            break;
    } // switch
}
// --------------------------------------------------------------------------------
void drawParam(const uint8_t entryIndex)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    const GraphRanges graphData = getGraphRanges(entryIndex);
    const uint8_t dp = getFixedValueDecimalPlaces(entryIndex);

    // Param Name
    tft.setTextColor(TFT_YELLOW);
    sprintf(singleEntryTmp, "%s (%s)", getFixedEntryName(entryIndex), getFixedEntrySymbol(entryIndex));
    centreText(singleEntryTmp, TFT_LEFT, TFT_RIGHT, TITLE_TEXT_Y);
    // Current Reading
    tft.setTextColor(TFT_WHITE);
    getFormattedValue(getMinRecordedParam(entryIndex), dp, bufferOne, BUFFER_SIZE);
    getFormattedValue(getMaxRecordedParam(entryIndex), dp, bufferTwo, BUFFER_SIZE);
    getLiveDataCurrentFormattedValue(entryIndex, bufferThree, BUFFER_SIZE);
    sprintf(singleEntryTmp, "%s < %s %s < %s", bufferOne, bufferThree, getFixedEntryNameUnits(entryIndex), bufferTwo);
    centreText(singleEntryTmp, TFT_LEFT, TFT_RIGHT, VALUE_TEXT_Y);
    // Last Date
    getLiveDataCurrentRawTimeAsText(entryIndex, bufferOne, BUFFER_SIZE);
    sprintf(singleEntryTmp, "Last Read: %s", bufferOne);
    centreText(singleEntryTmp, TFT_LEFT, TFT_RIGHT, TIME_TEXT_Y);

    if (graphData.zeroIndexed) // RYG
    {
        // Red Range
        tft.setTextColor(TFT_RED);
        getFormattedValue(graphData.bottomRed, dp, bufferOne, BUFFER_SIZE);
        getFormattedValue(graphData.bottomAmber, dp, bufferTwo, BUFFER_SIZE);
        sprintf(singleEntryTmp, "%s - %s", bufferOne, bufferTwo);
        centreText(singleEntryTmp, TFT_LEFT, TFT_RIGHT, RED_TEXT_Y);
        // Amber Range
        tft.setTextColor(TFT_YELLOW);
        getFormattedValue(graphData.bottomAmber, dp, bufferOne, BUFFER_SIZE);
        getFormattedValue(graphData.bottomGreen, dp, bufferTwo, BUFFER_SIZE);
        sprintf(singleEntryTmp, "%s - %s", bufferOne, bufferTwo);
        centreText(singleEntryTmp, TFT_LEFT, TFT_RIGHT, AMBER_TEXT_Y);
        // Green
        tft.setTextColor(TFT_GREEN);
        getFormattedValue(graphData.bottomGreen, dp, bufferOne, BUFFER_SIZE);
        getFormattedValue(graphData.topGreen, dp, bufferTwo, BUFFER_SIZE);
        sprintf(singleEntryTmp, "%s - %s", bufferOne, bufferTwo);
        centreText(singleEntryTmp, TFT_LEFT, TFT_RIGHT, GREEN_TEXT_Y);
    }
    else // RGR
    {
        // Red Range
        tft.setTextColor(TFT_RED);
        getFormattedValue(graphData.bottomRed, dp, bufferOne, BUFFER_SIZE);
        getFormattedValue(graphData.bottomAmber, dp, bufferTwo, BUFFER_SIZE);
        sprintf(singleEntryTmp, "%s - %s", bufferOne, bufferTwo);
        centreText(singleEntryTmp, TFT_LEFT, TFT_RIGHT / 2, RED_TEXT_Y);

        getFormattedValue(graphData.topRed, dp, bufferOne, BUFFER_SIZE);
        getFormattedValue(graphData.topAmber, dp, bufferTwo, BUFFER_SIZE);
        sprintf(singleEntryTmp, "%s - %s", bufferOne, bufferTwo);
        centreText(singleEntryTmp, TFT_RIGHT / 2, TFT_RIGHT, RED_TEXT_Y);
        // Amber Range
        tft.setTextColor(TFT_YELLOW);
        getFormattedValue(graphData.bottomAmber, dp, bufferOne, BUFFER_SIZE);
        getFormattedValue(graphData.bottomGreen, dp, bufferTwo, BUFFER_SIZE);
        sprintf(singleEntryTmp, "%s - %s", bufferOne, bufferTwo);
        centreText(singleEntryTmp, TFT_LEFT, TFT_RIGHT / 2, AMBER_TEXT_Y);

        getFormattedValue(graphData.topAmber, dp, bufferOne, BUFFER_SIZE);
        getFormattedValue(graphData.topGreen, dp, bufferTwo, BUFFER_SIZE);
        sprintf(singleEntryTmp, "%s - %s", bufferOne, bufferTwo);
        centreText(singleEntryTmp, TFT_RIGHT / 2, TFT_RIGHT, AMBER_TEXT_Y);
        // Green
        tft.setTextColor(TFT_GREEN);
        getFormattedValue(graphData.bottomGreen, dp, bufferOne, BUFFER_SIZE);
        getFormattedValue(graphData.topGreen, dp, bufferTwo, BUFFER_SIZE);
        sprintf(singleEntryTmp, "%s - %s", bufferOne, bufferTwo);
        centreText(singleEntryTmp, TFT_LEFT, TFT_RIGHT, GREEN_TEXT_Y);
    }

    drawGraph(entryIndex);
}
// --------------------------------------------------------------------------------
void drawChore(const uint8_t entryIndex)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    const ActivityTimes activityTimes = getActivityTimes(entryIndex);

    // Chore Name
    tft.setTextColor(TFT_YELLOW);
    sprintf(singleEntryTmp, "%s", getFixedEntryName(entryIndex));
    centreText(singleEntryTmp, TFT_LEFT, TFT_RIGHT, TITLE_TEXT_Y);
    // Current Reading
    // Chores don't have values (1 * ROW_SPACING)
    // Last Date
    tft.setTextColor(TFT_WHITE);
    getLiveDataCurrentRawTimeAsText(entryIndex, bufferOne, BUFFER_SIZE);
    sprintf(singleEntryTmp, "Last Done: %s", bufferOne);
    centreText(singleEntryTmp, TFT_LEFT, TFT_RIGHT, TIME_TEXT_Y);
    // Red Range
    tft.setTextColor(TFT_RED);
    getTimeAsText(activityTimes.timerAmberEndsMinutes + activityTimes.timerGreenEndsMinutes, bufferOne, BUFFER_SIZE);
    sprintf(singleEntryTmp, "> %s", bufferOne);
    centreText(singleEntryTmp, TFT_LEFT, TFT_RIGHT, RED_TEXT_Y);
    // Amber Range
    tft.setTextColor(TFT_YELLOW);
    getTimeAsText(activityTimes.timerGreenEndsMinutes, bufferOne, BUFFER_SIZE);
    getTimeAsText(activityTimes.timerAmberEndsMinutes + activityTimes.timerGreenEndsMinutes, bufferTwo, BUFFER_SIZE);
    sprintf(singleEntryTmp, "%s - %s", bufferOne, bufferTwo);
    centreText(singleEntryTmp, TFT_LEFT, TFT_RIGHT, AMBER_TEXT_Y);
    // Green
    tft.setTextColor(TFT_GREEN);
    getTimeAsText(activityTimes.timerGreenEndsMinutes, bufferOne, BUFFER_SIZE);
    sprintf(singleEntryTmp, "< %s", bufferOne);
    centreText(singleEntryTmp, TFT_LEFT, TFT_RIGHT, GREEN_TEXT_Y);

    drawGraph(entryIndex);
}
// --------------------------------------------------------------------------------
