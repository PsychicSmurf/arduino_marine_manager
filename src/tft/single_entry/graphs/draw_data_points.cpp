// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "draw_data_points.h"
#include "../../../logger/logger.h"
#include "../../../data/live_data.h"
#include "../../../data/fixed_data.h"
#include "../../draw_template.h"
// --------------------------------------------------------------------------------
void plotDataPoints(const uint8_t entryIndex)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    uint16_t lastX = 0;
    uint16_t lastY = 0;
    uint16_t currentX = 0;
    uint16_t currentY = 0;

    const GraphRanges graphData = getGraphRanges(entryIndex);
    const ActivityTimes activityTimes = getActivityTimes(entryIndex);
    const EntryType entryType = getFixedEntryType(entryIndex);

    for (uint8_t index = 0; index < getLiveDataNumberOfValues(entryIndex); index++)
    {
        switch (entryType)
        {
            case entryType_PARAM:
                currentY = scaleParameterValue(getLiveDataValue(entryType, index), graphData);
                break;

            case entryType_CHORE:
                currentY = scaleChoreTime(getLiveDataTimerMinutes(entryType, index), activityTimes);
                break;

            default: // Can't get here
                break;
        } // switch

        currentX = 310 - index * 12;

        if (index > 0)
        {
            tft.drawLine(currentX, currentY, lastX, lastY, TFT_WHITE);
        } // else no previous entry to draw from

        tft.fillCircle(currentX, currentY, 3, TFT_WHITE);

        lastX = currentX;
        lastY = currentY;
    } // for index
}
// --------------------------------------------------------------------------------
uint32_t scaleParameterValue(const uint32_t paramValue, const GraphRanges &paramRanges)
{
    assert(paramValue < 10000);

    uint32_t ret_val;
    uint32_t topY, bottomY;

    if (paramRanges.zeroIndexed) // Red - Amber - Green
    {
        // GREEN
        if (paramValue <= paramRanges.bottomGreen)
        {
            bottomY = GRAPH_BOTTOM - GRAPH_BORDER;
            topY    = GRAPH_BOTTOM - RYG_GREEN - (RYG_GRADIENT_COLOUR_COUNT / 2);
            ret_val  = convertTimeToScale(paramValue, topY, bottomY, 0, paramRanges.bottomGreen);
        }
        // AMBER
        else if (paramValue <= paramRanges.bottomAmber)
        {
            bottomY = GRAPH_BOTTOM - RYG_GREEN - (RYG_GRADIENT_COLOUR_COUNT / 2);
            topY    = GRAPH_TOP + RYG_RED - (RYG_GRADIENT_COLOUR_COUNT / 2);
            ret_val  = convertTimeToScale(paramValue - paramRanges.bottomGreen, topY, bottomY, paramRanges.bottomGreen,
                                          paramRanges.bottomAmber);
        }
        // RED
        else
        {
            bottomY = GRAPH_TOP + RYG_RED - (RYG_GRADIENT_COLOUR_COUNT / 2);
            topY    = GRAPH_TOP + GRAPH_BORDER;
            ret_val  = convertTimeToScale(paramValue - paramRanges.bottomAmber, topY, bottomY, paramRanges.bottomAmber,
                                          paramRanges.bottomRed);
        }
    }
    else // Red - Amber - Green Amber - Red
    {
        // RED
        bottomY = GRAPH_BOTTOM - GRAPH_BORDER;
        topY    = GRAPH_BOTTOM - RGR_GREEN - (RGR_GRADIENT_COLOUR_COUNT / 2);
        ret_val  = convertTimeToScale(paramValue, topY, bottomY, paramRanges.bottomRed, paramRanges.bottomAmber);
        // AMBER
        bottomY = GRAPH_BOTTOM - RGR_GREEN - (RGR_GRADIENT_COLOUR_COUNT / 2);
        topY    = GRAPH_BOTTOM - RYG_GREEN - RYG_AMBER - RYG_GRADIENT_COLOUR_COUNT;
        ret_val  = convertTimeToScale(paramValue, topY, bottomY, paramRanges.bottomAmber, paramRanges.bottomGreen);
        // GREEN
        bottomY = GRAPH_BOTTOM - RYG_GREEN - RYG_AMBER - RYG_GRADIENT_COLOUR_COUNT;
        topY    = GRAPH_TOP + RYG_GREEN - RYG_AMBER - RYG_GRADIENT_COLOUR_COUNT;
        ret_val  = convertTimeToScale(paramValue, topY, bottomY, paramRanges.bottomGreen, paramRanges.topGreen);
        // AMBER
        bottomY = GRAPH_TOP + RYG_GREEN + RYG_AMBER + RYG_GRADIENT_COLOUR_COUNT;
        topY    = GRAPH_TOP + RGR_GREEN + (RGR_GRADIENT_COLOUR_COUNT / 2);
        ret_val  = convertTimeToScale(paramValue, topY, bottomY, paramRanges.topGreen, paramRanges.topAmber);
        // RED
        bottomY = GRAPH_TOP + RGR_GREEN + (RGR_GRADIENT_COLOUR_COUNT / 2);
        topY    = GRAPH_TOP + GRAPH_BORDER;
        ret_val  = convertTimeToScale(paramValue, topY, bottomY, paramRanges.topAmber, paramRanges.topRed);
    }

    return ret_val;
}
// --------------------------------------------------------------------------------
uint32_t convertTimeToScale(const uint32_t choreTime, const uint32_t topY, const uint32_t bottomY,
                            const uint32_t rangeStart, const uint32_t rangeEnd)
{
    assert(topY > bottomY);
    assert(topY <= TFT_HEIGHT);
    assert(rangeEnd != rangeStart);

    return ((bottomY - topY) * choreTime) / (rangeEnd - rangeStart);
}
// --------------------------------------------------------------------------------
uint32_t scaleChoreTime(uint16_t choreTime, const ActivityTimes choreRanges)
{
    uint32_t ret_val;
    uint32_t topY, bottomY;
    const uint32_t MAX_RED_TIME = 999;

    // GREEN
    if (choreTime <= choreRanges.timerGreenEndsMinutes)
    {
        bottomY = GRAPH_BOTTOM - GRAPH_BORDER;
        topY    = GRAPH_BOTTOM - RYG_GREEN - (RYG_GRADIENT_COLOUR_COUNT / 2);
        ret_val  = convertTimeToScale(choreTime, topY, bottomY, 0, choreRanges.timerGreenEndsMinutes);
    }
    // AMBER
    else if (choreTime <= choreRanges.timerAmberEndsMinutes)
    {
        choreTime -= choreRanges.timerGreenEndsMinutes;
        bottomY = GRAPH_BOTTOM - RYG_GREEN - (RYG_GRADIENT_COLOUR_COUNT / 2);
        topY    = GRAPH_TOP + RYG_RED - (RYG_GRADIENT_COLOUR_COUNT / 2);
        ret_val  = convertTimeToScale(choreTime, topY, bottomY, 0, choreRanges.timerAmberEndsMinutes);
    }
    // RED
    else
    {
        choreTime -= choreRanges.timerAmberEndsMinutes;
        bottomY = GRAPH_TOP + RYG_RED - (RYG_GRADIENT_COLOUR_COUNT / 2);
        topY    = GRAPH_TOP + GRAPH_BORDER;
        ret_val  = convertTimeToScale(choreTime, topY, bottomY, 0, MAX_RED_TIME);
    }

    return ret_val;
}
// --------------------------------------------------------------------------------
