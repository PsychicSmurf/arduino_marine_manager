#ifndef LIVE_DATA_H
#define LIVE_DATA_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------
#include "fixed_data.h"
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
const uint8_t MAX_HISTORY_VALUES_TO_KEEP = 26;
enum ColourCategory
{
    COLOUR_CATEGORY_GREEN   = 0,
    COLOUR_CATEGORY_AMBER   = 1,
    COLOUR_CATEGORY_RED     = 2
};
struct EntryLiveData
{
    uint16_t        values[MAX_HISTORY_VALUES_TO_KEEP];
    uint32_t        timerMinutes[MAX_HISTORY_VALUES_TO_KEEP];
    uint8_t         numberOfValues;
    ColourCategory  currentTimeColour;
    ColourCategory  currentValueColour;
    uint32_t        currentTimerMinutesInColour;
};
// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
void oneMinuteUpdateForLiveData();
void getLiveDataCurrentTimeAsText(uint8_t dataIndex, char *charArray, uint8_t arraySize);
void convertTimeToText(uint32_t timeValue, char *timeText, uint8_t arraySize);
void getTimeAsText(uint32_t timeValue, char *charArray, uint8_t arraySize);
void sortLiveDataByTimerValues();
void swapInt8(uint8_t &valueA, uint8_t &valueB);
void updateCurrentColourCategoryAndTimerValues();
void resetLiveData();
void setCurrentTimesToZero();
void advanceOneHour();
void getLiveDataCurrentFormattedValue(uint8_t entryIndex, char *charArray, uint8_t arraySize);
void getFormattedValue(uint32_t value, uint16_t decimalPlaces, char *charArray, uint8_t arraySize);
void getLiveDataCurrentRawTimeAsText(uint8_t dataIndex, char *charArray, uint8_t arraySize);
uint16_t getMinRecordedParam(uint16_t entryIndex);
uint16_t getMaxRecordedParam(uint16_t entryIndex);

uint16_t getLiveDataValue(uint8_t entryIndex, uint8_t valueIndex);
uint32_t getLiveDataTimerMinutes(uint8_t entryIndex, uint8_t valueIndex);
uint8_t getLiveDataNumberOfValues(uint8_t entryIndex);
ColourCategory getLiveDataCurrentTimeColour(uint8_t entryIndex);
ColourCategory getLiveDataCurrentValueColour(uint8_t entryIndex);
uint32_t getLiveDataCurrentTimerMinutesColour(uint8_t entryIndex);
uint8_t getSortedLiveDataTimeIndex(uint8_t entryIndex);
bool getOrderOrEntryColourChanged();
uint16_t getCalculatorValue();
uint16_t getCalculatorEntryIndex();

uint32_t getLiveDataCurrentTimerMinutes(uint8_t entryIndex);
uint16_t getLiveDataCurrentValue(uint8_t entryIndex);

void setLiveDataValue(uint8_t entryIndex, uint8_t valueIndex, uint16_t value);
void setLiveDataTimerMinutes(uint8_t entryIndex, uint8_t valueIndex, uint32_t value);
void setLiveDataNumberOfValues(uint8_t entryIndex, uint8_t value);
void setLiveDataCurrentTimeColour(uint8_t entryIndex, ColourCategory col);
void setLiveDataCurrentValueColour(uint8_t entryIndex, ColourCategory col);
void setLiveDataCurrentTimerMinutesColour(uint8_t entryIndex, uint32_t value);
void setOrderOrEntryColourChanged(bool value);
void setCalculatorValue(uint16_t value);
void setCalculatorEntryIndex(uint16_t entryEndex);
// --------------------------------------------------------------------------------
#endif // LIVE_DATA_H
