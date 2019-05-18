#ifndef APP_STATUS_H
#define APP_STATUS_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
enum CurrentPage
{
    PAGE_TODO_1             = 0,
    PAGE_TODO_2             = 1,
    PAGE_TODO_3             = 2,
    PAGE_PARAMETER_STATUS   = 3,
    PAGE_CHORE_STATUS_1     = 4,
    PAGE_CHORE_STATUS_2     = 5,
    PAGE_CALCULATOR         = 6,
    PAGE_CONFIRMATION       = 7,
    PAGE_ABOUT              = 8,
    PAGE_PARAMETER_VIEW     = 9,
    PAGE_CHORE_VIEW         = 10
};
// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
void appStatusSetup();
CurrentPage getAppStatus();
void setAppStatus(const CurrentPage &page);
void setAppStatus(const CurrentPage &page, uint8_t index);
bool hasViewChanged();
void setScreenTimedOut();
bool hasTimeUpdated();
void setTimeUpdated(bool updated);
bool hasCalculatorUpdated();
void setCalculatorUpdated(bool updated);
void setViewChanged(bool changed);
void setRequestSdDataSave(bool saveWanted);
bool getSdDataSaveRequested();
uint8_t getSelectedEntryIndex();
// --------------------------------------------------------------------------------
#endif // APP_STATUS_H
