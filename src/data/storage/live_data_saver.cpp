// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "live_data_saver.h"
#include "sd_card_handler.h"
#include "../live_data.h"
#include "../fixed_data.h"
#include "../../logger/logger.h"
#include "../flash_handler.h"
// --------------------------------------------------------------------------------
const char BACKUP_FILE_NAME[MAX_FILE_NAME_LENGTH]  = "MarineData.bak";
const char OLD_FILE_NAME[MAX_FILE_NAME_LENGTH]     = "MarineData.old";
const char CURRENT_FILE_NAME[MAX_FILE_NAME_LENGTH] = "MarineData.txt";
// --------------------------------------------------------------------------------
void saveLiveData()
{
    if (!isSdcardWorking())
    {
        logString(F("ERR: SD Init"));
        return;
    } // else SD card working

    removeFile(BACKUP_FILE_NAME);

    renameFile(OLD_FILE_NAME, BACKUP_FILE_NAME);

    renameFile(CURRENT_FILE_NAME, OLD_FILE_NAME);

    if (openFile(CURRENT_FILE_NAME, FILEOPEN_WRITE) != FILEOPEN_NOT_OPENED)
    {
        const uint8_t MAX_CHAR_SIZE_FOR_VALUE = 10;
        char tmp[MAX_CHAR_SIZE_FOR_VALUE];

        for (uint8_t entryIndex = 0; entryIndex < NUMBER_OF_ENTRIES; entryIndex++)
        {
            writeStringWithLineEnding(getFixedEntryName(entryIndex));

            for (uint8_t valueIndex = 0; valueIndex < MAX_HISTORY_VALUES_TO_KEEP; valueIndex++)
            {
                if (valueIndex > 0)
                {
                    writeString(",");
                } // else first value

                sprintf(tmp, "%d", getLiveDataValue(entryIndex, valueIndex));
                writeString(tmp);
            } // for valueIndex

            writeStringWithLineEnding("");

            for (uint8_t valueIndex = 0; valueIndex < MAX_HISTORY_VALUES_TO_KEEP; valueIndex++)
            {
                if (valueIndex > 0)
                {
                    writeString(",");
                } // else first value

                sprintf(tmp, "%lu", (unsigned long)getLiveDataTimerMinutes(entryIndex, valueIndex));
                writeString(tmp);
            } // for valueIndex

            writeStringWithLineEnding("");

            sprintf(tmp, "%d", getLiveDataNumberOfValues(entryIndex));
            writeStringWithLineEnding(tmp);
        } // for entryIndex

        closeFile();
    } // else file didn't open - can't save

    logString(F("Data Saved To SD"));
}
// --------------------------------------------------------------------------------
