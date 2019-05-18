// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "sd_card_handler.h"
#include "../../logger/logger.h"
#include "live_data_saver.h"
#include <SPI.h>
#include <SdFat.h>
// --------------------------------------------------------------------------------
// https://learn.adafruit.com/adafruit-micro-sd-breakout-board-card-tutorial/arduino-library
// ICSP PINS
// ---------
// MEGA  UNO
//  50    12 = MISO
//  51    11 = MOSI
//  52    13 = SCK
//  53    10 = SS
// --------------------------------------------------------------------------------
// Init the SD Card
// --------------------------------------------------------------------------------
static bool sdcardInitOk;
static uint8_t sdSecondCounter;
static SdFat sd;
static SdFile logFile;
static const uint16_t SD_SECONDS_IN_A_MINUTE = 60;
extern const uint8_t MAX_FILE_NAME_LENGTH;
#define SD_CHIP_SELECT_PIN 53
#define WRITE_ENABLE_PIN 38
// --------------------------------------------------------------------------------
// Setup the Serial Port
// --------------------------------------------------------------------------------
void setupSdcard()
{
    // UNO SPI - Hard wires connecting from Mega
    pinMode(10, INPUT);
    pinMode(11, INPUT);
    pinMode(12, INPUT);
    pinMode(13, INPUT);

    pinMode(SD_CHIP_SELECT_PIN, OUTPUT);
    digitalWrite(SD_CHIP_SELECT_PIN, HIGH);
    pinMode(WRITE_ENABLE_PIN, INPUT_PULLUP);

    sdcardInitOk = true;

    if (!sd.begin(SD_CHIP_SELECT_PIN, SD_SCK_MHZ(50)))
    {
        logString(F("SD Card initialization failed."));
        sdcardInitOk = false;
        return;
    } // else all ok
    else
    {
        logString(F("SD Card Setup."));
    }
}
// --------------------------------------------------------------------------------
// Returns true if the SD card initialised correctly
// --------------------------------------------------------------------------------
bool isSdcardWorking()
{
    return sdcardInitOk;
}
// --------------------------------------------------------------------------------
RemoveFileStatus removeFile(const char *filename)
{
    assert(strnlen(filename, MAX_FILE_NAME_LENGTH) < MAX_FILE_NAME_LENGTH);
    assert(strnlen(filename, MAX_FILE_NAME_LENGTH) > 0);

    RemoveFileStatus retVal = REMOVE_FILE_REMOVED;

    if (isSdcardWorking())
    {
        if (sd.exists(filename))
        {
            if (!sd.remove(filename))
            {
                retVal = REMOVE_FILE_NOT_REMOVED;
                sdcardInitOk = false;
            }
        }
        else
        {
            retVal = REMOVE_FILE_NOT_EXIST;
        }
    }
    else
    {
        retVal = REMOVE_SD_FAULT;
    }

    return retVal;
}
// --------------------------------------------------------------------------------
RenameFileStatus renameFile(const char *nameFrom, const char *nameTo)
{
    assert(strnlen(nameFrom, MAX_FILE_NAME_LENGTH) < MAX_FILE_NAME_LENGTH);
    assert(strnlen(nameTo, MAX_FILE_NAME_LENGTH) < MAX_FILE_NAME_LENGTH);
    assert(strnlen(nameFrom, MAX_FILE_NAME_LENGTH) > 0);
    assert(strnlen(nameTo, MAX_FILE_NAME_LENGTH) > 0);

    RenameFileStatus retVal = RENAME_FILE_RENAMED;

    if (isSdcardWorking())
    {
        if (sd.exists(nameTo))
        {
            retVal = RENAME_TARGET_EXIST;
        }
        else
        {
            if (!sd.exists(nameFrom))
            {
                retVal = RENAME_SOURCE_NOT_EXIST;
            }
            else
            {
                if (!sd.rename(nameFrom, nameTo))
                {
                    retVal = RENAME_NOT_RENAMED;
                }
            }
        }
    }
    else
    {
        retVal = RENAME_SD_FAULT;
    }

    return retVal;
}
// --------------------------------------------------------------------------------
FileOpen openFile(const char *filename, const FileOpen rw)
{
    assert(strnlen(filename, MAX_FILE_NAME_LENGTH) < MAX_FILE_NAME_LENGTH);
    assert(strnlen(filename, MAX_FILE_NAME_LENGTH) > 0);

    FileOpen retVal = rw;

    if (isSdcardWorking())
    {
        if (rw == FILEOPEN_READ)
        {
            if (!logFile.open(filename, O_READ))
            {
                retVal = FILEOPEN_NOT_OPENED;
            } // else opened
        }
        else if (rw == FILEOPEN_WRITE)
        {
            if (!logFile.open(filename, O_CREAT | O_WRITE))
            {
                retVal = FILEOPEN_NOT_OPENED;
            } // else opened
        }
    }
    else
    {
        retVal = FILEOPEN_SD_FAULT;
    }

    return retVal;
}
// --------------------------------------------------------------------------------
FileClose closeFile()
{
    FileClose retVal = FILECLOSE_CLOSED;

    if (isSdcardWorking())
    {
        if (logFile.isOpen())
        {
            logFile.close();

            if (logFile.isOpen())
            {
                retVal = FILECLOSE_NOT_CLOSED;
            }
        }
        else
        {
            retVal = FILECLOSE_NOT_OPEN;
        }
    }
    else
    {
        retVal = FILECLOSE_SD_FAULT;
    }

    return retVal;
}
// --------------------------------------------------------------------------------
bool initialiseSdcard()
{
    sdcardInitOk = true;

    if (!sd.begin(SD_CHIP_SELECT_PIN, SD_SCK_MHZ(50)))
    {
        sdcardInitOk = false;
    } // else all ok

    return sdcardInitOk;
}
// --------------------------------------------------------------------------------
bool writeString(const char *entry)
{
    bool retVal = true;

    if (isSdcardWorking())
    {
        logFile.print(entry);
    }
    else
    {
        retVal = false;
    }

    return retVal;
}
// --------------------------------------------------------------------------------
bool writeStringWithLineEnding(const char *entry)
{
    bool retVal = true;

    if (isSdcardWorking())
    {
        logFile.println(entry);
    }
    else
    {
        retVal = false;
    }

    return retVal;
}
// --------------------------------------------------------------------------------
void sdcardTickSecond()
{
    sdSecondCounter++;

    if (sdSecondCounter >= SD_SECONDS_IN_A_MINUTE)
    {
        sdSecondCounter = 0;

        if (!isSdcardWorking())
        {
            if (!initialiseSdcard())
            {
                logString(F("SD Re-Init Failed"));
            } // else all fine now
            else
            {
                logString(F("SD Recovered!"));
            }
        }
    } // else don't spam restarts
}
// --------------------------------------------------------------------------------
bool isFileAvailable()
{
    return logFile.available();
}
// --------------------------------------------------------------------------------
bool getCharFromFile(char &ch)
{
    return (logFile.read(&ch, 1) != 1);
}
// --------------------------------------------------------------------------------
