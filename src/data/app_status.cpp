// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "app_status.h"
#include "../logger/logger.h"
#include "../data/fixed_data.h"
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
static CurrentPage currentPage;
static bool flagViewChange;
static bool flagTimeUpdated;
static bool flagCalculatorUpdated;
static bool flagSaveSdData;
static uint8_t selectedEntryIndex;
// --------------------------------------------------------------------------------
void appStatusSetup()
{
    currentPage = PAGE_TODO_1;
    flagViewChange = true;
    flagCalculatorUpdated = false;
    flagTimeUpdated = false;
    flagSaveSdData = false;
    selectedEntryIndex = 0;
}
// --------------------------------------------------------------------------------
CurrentPage getAppStatus()
{
    return currentPage;
}
// --------------------------------------------------------------------------------
void setAppStatus(const CurrentPage &page, const uint8_t index)
{
    assert(index < NUMBER_OF_ENTRIES);

    selectedEntryIndex = index;
    setAppStatus(page);
}
// --------------------------------------------------------------------------------
void setAppStatus(const CurrentPage &page)
{
    if (currentPage != page)
    {
        currentPage = page;
        flagViewChange = true;
    } // else no change
}
// --------------------------------------------------------------------------------
uint8_t getSelectedEntryIndex()
{
    return selectedEntryIndex;
}
// --------------------------------------------------------------------------------
bool hasViewChanged()
{
    return flagViewChange;
}
// --------------------------------------------------------------------------------
void setViewChanged(const bool changed)
{
    flagViewChange = changed;
}
// --------------------------------------------------------------------------------
void setScreenTimedOut()
{
    setAppStatus(PAGE_TODO_1);
}
// --------------------------------------------------------------------------------
bool hasTimeUpdated()
{
    return flagTimeUpdated;
}
// --------------------------------------------------------------------------------
void setTimeUpdated(const bool updated)
{
    flagTimeUpdated = updated;
}
// --------------------------------------------------------------------------------
bool hasCalculatorUpdated()
{
    return flagCalculatorUpdated;
}
// --------------------------------------------------------------------------------
void setCalculatorUpdated(const bool updated)
{
    flagCalculatorUpdated = updated;
}
// --------------------------------------------------------------------------------
void setRequestSdDataSave(const bool saveWanted)
{
    flagSaveSdData = saveWanted;
}
// --------------------------------------------------------------------------------
bool getSdDataSaveRequested()
{
    return flagSaveSdData;
}
// --------------------------------------------------------------------------------
