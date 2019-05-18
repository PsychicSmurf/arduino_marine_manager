// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "live_data_loader.h"
#include "live_data_saver.h"
#include "sd_card_handler.h"
#include "../../logger/logger.h"
#include "../live_data.h"
#include "../fixed_data.h"
#include "../flash_handler.h"
// --------------------------------------------------------------------------------
void loadLiveData()
{
    if (!isSdcardWorking())
    {
        logString(F("ERR: SD Init"));
        return;
    } // else SD card working

    if (openFile(CURRENT_FILE_NAME, FILEOPEN_READ) != FILEOPEN_READ)
    {
        logString(F("ERR: Cannot Load Data"));
        return;
    } // else file opened

    for (uint8_t entryIndex = 0; entryIndex < NUMBER_OF_ENTRIES; entryIndex++)
    {
        getValueFromFile(); // Header Text - Ignore

        for (uint8_t valueIndex = 0; valueIndex < MAX_HISTORY_VALUES_TO_KEEP; valueIndex++)
        {
            setLiveDataValue(entryIndex, valueIndex, atoi(getValueFromFile()));
        } // for valueIndex

        for (uint8_t valueIndex = 0; valueIndex < MAX_HISTORY_VALUES_TO_KEEP; valueIndex++)
        {
            setLiveDataTimerMinutes(entryIndex, valueIndex, atoi(getValueFromFile()));
        } // for valueIndex

        setLiveDataNumberOfValues(entryIndex, atoi(getValueFromFile()));
    } // for entryIndex

    closeFile();

    logString(F("Data Loaded from SD"));
}
// --------------------------------------------------------------------------------
char *getValueFromFile()
{
    char *retVal = 0;
    char *ch;

    while (true)
    {
        if (!isFileAvailable())
        {
            break;
        }

        if (getCharFromFile(*ch))
        {
            break;
        }

        // Delete CR.
        if (*ch == '\r')
        {
            continue;
        }

        if ((*ch == ',') || (*ch == '\n'))
        {
            break;
        }

        strcat(retVal, ch);
    } // while

    return retVal;
}
// --------------------------------------------------------------------------------
