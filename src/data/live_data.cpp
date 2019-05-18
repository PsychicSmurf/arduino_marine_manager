// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "live_data.h"
#include "../logger/logger.h"
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
static EntryLiveData liveData[NUMBER_OF_ENTRIES] =
{
    //    Values                                                                             Timer Minutes                                                                    Count
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 },
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, COLOUR_CATEGORY_GREEN, COLOUR_CATEGORY_GREEN, 0 }
};
static uint8_t sortedLiveDataTimeIndex[NUMBER_OF_ENTRIES] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };
static bool orderOrEntryColourChanged = false;
static const uint8_t LIVE_DATA_TEXT_SIZE = 16;
static char liveDataText[LIVE_DATA_TEXT_SIZE];
static uint16_t currentCalculatorValue = 0;
static uint16_t currentCalculatorEntryIndex = 0;
// --------------------------------------------------------------------------------
void oneMinuteUpdateForLiveData()
{
    for (uint8_t index = 0; index < NUMBER_OF_ENTRIES; index++)
    {
        liveData[index].timerMinutes[liveData[index].numberOfValues]++;
    } // for index

    updateCurrentColourCategoryAndTimerValues();
    sortLiveDataByTimerValues();
}
// --------------------------------------------------------------------------------
void getLiveDataCurrentTimeAsText(const uint8_t dataIndex, char *charArray, const uint8_t arraySize)
{
    assert(arraySize > 0);
    assert(dataIndex < NUMBER_OF_ENTRIES);

    convertTimeToText(getLiveDataCurrentTimerMinutesColour(dataIndex), charArray, arraySize);
}
// --------------------------------------------------------------------------------
void getLiveDataCurrentRawTimeAsText(const uint8_t dataIndex, char *charArray, const uint8_t arraySize)
{
    assert(arraySize > 0);
    assert(dataIndex < NUMBER_OF_ENTRIES);

    convertTimeToText(liveData[dataIndex].timerMinutes[liveData[dataIndex].numberOfValues], charArray, arraySize);
}
// --------------------------------------------------------------------------------
void convertTimeToText(const uint32_t timeValue, char *timeText, const uint8_t arraySize)
{
    assert(arraySize > 0);

    getTimeAsText(timeValue, timeText, arraySize);
}
// --------------------------------------------------------------------------------
void getTimeAsText(uint32_t timeValue, char *charArray, const uint8_t arraySize)
{
    assert(arraySize > 0);

    if (arraySize >= LIVE_DATA_TEXT_SIZE)
    {
        uint8_t days = timeValue / MINUTES_IN_A_DAY;
        timeValue -= (days * MINUTES_IN_A_DAY);

        uint8_t hours = timeValue / MINUTES_IN_AN_HOUR;
        timeValue -= (hours * MINUTES_IN_AN_HOUR);

        uint8_t minutes = timeValue;

        assert(days < 1000);

        sprintf(liveDataText, "%3dd %2d:%02d", days, hours, minutes);

        strncpy(charArray, liveDataText, arraySize);
    }
    else
    {
        charArray[0] = 0;
    }
}
// --------------------------------------------------------------------------------
uint16_t getLiveDataValue(const uint8_t entryIndex, const uint8_t valueIndex)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);
    assert(valueIndex < MAX_HISTORY_VALUES_TO_KEEP);

    return liveData[entryIndex].values[valueIndex];
}
// --------------------------------------------------------------------------------
uint32_t getLiveDataTimerMinutes(const uint8_t entryIndex, const uint8_t valueIndex)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);
    assert(valueIndex < MAX_HISTORY_VALUES_TO_KEEP);

    return liveData[entryIndex].timerMinutes[valueIndex];
}
// --------------------------------------------------------------------------------
uint8_t getLiveDataNumberOfValues(const uint8_t entryIndex)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    return liveData[entryIndex].numberOfValues;
}
// --------------------------------------------------------------------------------
ColourCategory getLiveDataCurrentTimeColour(const uint8_t entryIndex)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    return liveData[entryIndex].currentTimeColour;
}
// --------------------------------------------------------------------------------
ColourCategory getLiveDataCurrentValueColour(const uint8_t entryIndex)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    return liveData[entryIndex].currentValueColour;
}
// --------------------------------------------------------------------------------
void setLiveDataCurrentTimeColour(const uint8_t entryIndex, const ColourCategory col)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    liveData[entryIndex].currentTimeColour = col;
}
// --------------------------------------------------------------------------------
void setLiveDataCurrentValueColour(const uint8_t entryIndex, const ColourCategory col)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    liveData[entryIndex].currentValueColour = col;
}
// --------------------------------------------------------------------------------
void setLiveDataValue(const uint8_t entryIndex, const uint8_t valueIndex, const uint16_t newValue)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);
    assert(valueIndex < MAX_HISTORY_VALUES_TO_KEEP);
    assert(newValue < 10000);

    liveData[entryIndex].values[valueIndex] = newValue;

    GraphRanges range = getGraphRanges(entryIndex);

    if ((newValue >= range.topRed) && (newValue < range.topAmber))
    {
        liveData[entryIndex].currentValueColour = COLOUR_CATEGORY_RED;
    }
    else if ((newValue >= range.topAmber) && (newValue < range.topGreen))
    {
        liveData[entryIndex].currentValueColour = COLOUR_CATEGORY_AMBER;
    }
    else if ((newValue >= range.topGreen) && (newValue <= range.bottomGreen))
    {
        liveData[entryIndex].currentValueColour = COLOUR_CATEGORY_GREEN;
    }
    else if ((newValue > range.bottomGreen) && (newValue <= range.bottomAmber))
    {
        liveData[entryIndex].currentValueColour = COLOUR_CATEGORY_AMBER;
    }
    else if ((newValue > range.bottomAmber) && (newValue <= range.bottomRed))
    {
        liveData[entryIndex].currentValueColour = COLOUR_CATEGORY_RED;
    }
    else
    {
        liveData[entryIndex].currentValueColour = COLOUR_CATEGORY_RED;
    }
}
// --------------------------------------------------------------------------------
void setLiveDataTimerMinutes(const uint8_t entryIndex, const uint8_t valueIndex, const uint32_t newValue)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);
    assert(valueIndex < MAX_HISTORY_VALUES_TO_KEEP);

    liveData[entryIndex].timerMinutes[valueIndex] = newValue;
}
// --------------------------------------------------------------------------------
void setLiveDataNumberOfValues(const uint8_t entryIndex, const uint8_t newValue)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);
    assert(newValue < MAX_HISTORY_VALUES_TO_KEEP);

    liveData[entryIndex].numberOfValues = newValue;
}
// --------------------------------------------------------------------------------
uint32_t getLiveDataCurrentTimerMinutes(const uint8_t entryIndex)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    return getLiveDataTimerMinutes(entryIndex, liveData[entryIndex].numberOfValues);
}
// --------------------------------------------------------------------------------
uint32_t getLiveDataCurrentTimerMinutesColour(const uint8_t entryIndex)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    return liveData[entryIndex].currentTimerMinutesInColour;
}
// --------------------------------------------------------------------------------
void setLiveDataCurrentTimerMinutesColour(const uint8_t entryIndex, const uint32_t value)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    liveData[entryIndex].currentTimerMinutesInColour = value;
}
// --------------------------------------------------------------------------------
uint16_t getLiveDataCurrentValue(const uint8_t entryIndex)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    return getLiveDataValue(entryIndex, liveData[entryIndex].numberOfValues);
}
// --------------------------------------------------------------------------------
void getLiveDataCurrentFormattedValue(const uint8_t entryIndex, char *charArray, const uint8_t arraySize)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);
    assert(arraySize > 0);

    getFormattedValue((double)getLiveDataCurrentValue(entryIndex), getFixedValueDecimalPlaces(entryIndex), charArray,
                      arraySize);
}
// --------------------------------------------------------------------------------
void getFormattedValue(const uint32_t value, const uint16_t decimalPlaces, char *charArray, const uint8_t arraySize)
{
    assert(decimalPlaces < 6);
    assert(arraySize > 0);
    assert(value < 10000);

    if (arraySize >= LIVE_DATA_TEXT_SIZE)
    {
        uint16_t mask = ceil(pow(10, decimalPlaces));
        uint32_t prefix = value / mask;
        uint32_t suffix = value - (prefix * mask);

        switch (decimalPlaces)
        {
            default:
            case 0:
                sprintf(charArray, "%lu", value);
                break;

            case 1:
                sprintf(charArray, "%lu.%1lu", prefix, suffix);
                break;

            case 2:
                sprintf(charArray, "%lu.%02lu", prefix, suffix);
                break;

            case 3:
                sprintf(charArray, "%lu.%03lu", prefix, suffix);
                break;

            case 4:
                sprintf(charArray, "%lu.%04lu", prefix, suffix);
                break;

            case 5:
                sprintf(charArray, "%lu.%05lu", prefix, suffix);
                break;
        } // switch
    }
    else
    {
        charArray[0] = 0x00;
    }
}
// --------------------------------------------------------------------------------
void sortLiveDataByTimerValues()
{
    // Bubble sort for small footprint
    for (uint8_t indexA = 0; indexA < (NUMBER_OF_ENTRIES - 1); indexA++)
    {
        for (uint8_t indexB = indexA + 1; indexB < NUMBER_OF_ENTRIES; indexB++)
        {
            ColourCategory colA = getLiveDataCurrentTimeColour(sortedLiveDataTimeIndex[indexA]);
            ColourCategory colB = getLiveDataCurrentTimeColour(sortedLiveDataTimeIndex[indexB]);

            if (colB > colA)
            {
                // Swap due to colour banding
                swapInt8(sortedLiveDataTimeIndex[indexA], sortedLiveDataTimeIndex[indexB]);
                setOrderOrEntryColourChanged(true);
            }
            else if (colB == colA)
            {
                // Colours the same so check times instead
                uint32_t timeA = getLiveDataCurrentTimerMinutesColour(sortedLiveDataTimeIndex[indexA]);
                uint32_t timeB = getLiveDataCurrentTimerMinutesColour(sortedLiveDataTimeIndex[indexB]);

                switch (colA)
                {
                    case COLOUR_CATEGORY_GREEN:
                    case COLOUR_CATEGORY_AMBER:
                        if (timeB < timeA)
                        {
                            // Swap due to green/Amber time
                            swapInt8(sortedLiveDataTimeIndex[indexA], sortedLiveDataTimeIndex[indexB]);
                            setOrderOrEntryColourChanged(true);
                        }

                        break;

                    case COLOUR_CATEGORY_RED:
                        if (timeB > timeA)
                        {
                            // Swap due to red time
                            swapInt8(sortedLiveDataTimeIndex[indexA], sortedLiveDataTimeIndex[indexB]);
                            setOrderOrEntryColourChanged(true);
                        }

                        break;
                } // switch
            }
            else
            {
                // Colour banding means do not swap
            }
        } // for indexB
    } // for indexA
}
// --------------------------------------------------------------------------------
void swapInt8(uint8_t &valueA, uint8_t &valueB)
{
    int valueC = valueA;

    valueA = valueB;
    valueB = valueC;
}
// --------------------------------------------------------------------------------
void updateCurrentColourCategoryAndTimerValues()
{
    for (uint8_t dataIndex = 0; dataIndex < NUMBER_OF_ENTRIES; dataIndex++)
    {
        ActivityTimes activityTimes = getActivityTimes(dataIndex);
        uint32_t timeValue = getLiveDataCurrentTimerMinutes(dataIndex);

        if (timeValue < activityTimes.timerGreenEndsMinutes)
        {
            setLiveDataCurrentTimeColour(dataIndex, COLOUR_CATEGORY_GREEN);
            setLiveDataCurrentTimerMinutesColour(dataIndex, activityTimes.timerGreenEndsMinutes - timeValue);
        }
        else
        {
            timeValue -= activityTimes.timerGreenEndsMinutes;

            if (timeValue < activityTimes.timerAmberEndsMinutes)
            {
                if (getLiveDataCurrentTimeColour(dataIndex) != COLOUR_CATEGORY_AMBER)
                {
                    setOrderOrEntryColourChanged(true);
                } // else no change

                setLiveDataCurrentTimeColour(dataIndex, COLOUR_CATEGORY_AMBER);
                setLiveDataCurrentTimerMinutesColour(dataIndex, activityTimes.timerAmberEndsMinutes - timeValue);
            }
            else
            {
                timeValue -= activityTimes.timerAmberEndsMinutes;

                if (getLiveDataCurrentTimeColour(dataIndex) != COLOUR_CATEGORY_RED)
                {
                    setOrderOrEntryColourChanged(true);
                } // else no change

                setLiveDataCurrentTimeColour(dataIndex, COLOUR_CATEGORY_RED);
                setLiveDataCurrentTimerMinutesColour(dataIndex, timeValue);
            }
        }
    } // for dataIndex
}
// --------------------------------------------------------------------------------
uint8_t getSortedLiveDataTimeIndex(const uint8_t entryIndex)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    return sortedLiveDataTimeIndex[entryIndex];
}
// --------------------------------------------------------------------------------
bool getOrderOrEntryColourChanged()
{
    return orderOrEntryColourChanged;
}
// --------------------------------------------------------------------------------
void setOrderOrEntryColourChanged(const bool value)
{
    orderOrEntryColourChanged = value;
}
// --------------------------------------------------------------------------------
void resetLiveData()
{
    for (uint8_t dataIndex = 0; dataIndex < NUMBER_OF_ENTRIES; dataIndex++)
    {
        liveData[dataIndex].numberOfValues = 0;
        liveData[dataIndex].currentTimeColour = COLOUR_CATEGORY_GREEN;
        liveData[dataIndex].currentValueColour = COLOUR_CATEGORY_GREEN;
        liveData[dataIndex].currentTimerMinutesInColour = 0;

        for (uint8_t index = 0; index < MAX_HISTORY_VALUES_TO_KEEP; index++)
        {
            liveData[dataIndex].values[index] = 0;
            liveData[dataIndex].timerMinutes[index] = 0;
        } // for index
    } // for dataIndex

    updateCurrentColourCategoryAndTimerValues();
}
// --------------------------------------------------------------------------------
void setCurrentTimesToZero()
{
    for (uint8_t dataIndex = 0; dataIndex < NUMBER_OF_ENTRIES; dataIndex++)
    {
        liveData[dataIndex].timerMinutes[liveData[dataIndex].numberOfValues] = 0;
    } // for dataIndex

    updateCurrentColourCategoryAndTimerValues();
}
// --------------------------------------------------------------------------------
void advanceOneHour()
{
    for (uint8_t dataIndex = 0; dataIndex < NUMBER_OF_ENTRIES; dataIndex++)
    {
        liveData[dataIndex].timerMinutes[liveData[dataIndex].numberOfValues] += MINUTES_IN_AN_HOUR;
    } // for dataIndex

    updateCurrentColourCategoryAndTimerValues();
}
// --------------------------------------------------------------------------------
void setCalculatorValue(uint16_t value)
{
    assert(value < 10000);

    currentCalculatorValue = value;
}
// --------------------------------------------------------------------------------
uint16_t getCalculatorValue()
{
    return currentCalculatorValue;
}
// --------------------------------------------------------------------------------
void setCalculatorEntryIndex(uint16_t entryEndex)
{
    assert(entryEndex < NUMBER_OF_ENTRIES);

    currentCalculatorEntryIndex = entryEndex;
}
// --------------------------------------------------------------------------------
uint16_t getCalculatorEntryIndex()
{
    return currentCalculatorEntryIndex;
}
// --------------------------------------------------------------------------------
uint16_t getMinRecordedParam(const uint16_t entryEndex)
{
    assert(entryEndex < NUMBER_OF_ENTRIES);

    uint16_t retVal = 9999;

    for (uint8_t dataIndex = 0; dataIndex < liveData[entryEndex].numberOfValues; dataIndex++)
    {
        if (liveData[entryEndex].values[dataIndex] < retVal)
        {
            retVal = liveData[entryEndex].values[dataIndex];
        }
    } // for dataIndex

    return retVal;
}
// --------------------------------------------------------------------------------
uint16_t getMaxRecordedParam(const uint16_t entryEndex)
{
    assert(entryEndex < NUMBER_OF_ENTRIES);

    uint16_t retVal = 0;

    for (uint8_t dataIndex = 0; dataIndex < liveData[entryEndex].numberOfValues; dataIndex++)
    {
        if (liveData[entryEndex].values[dataIndex] > retVal)
        {
            retVal = liveData[entryEndex].values[dataIndex];
        }
    } // for dataIndex

    return retVal;
}
// --------------------------------------------------------------------------------
