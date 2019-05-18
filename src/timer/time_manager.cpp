// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "time_manager.h"
#include "timer_interrupt.h"
#include "../logger/logger.h"
#include "../data/app_status.h"
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
static volatile uint16_t screenTimeoutValueSeconds;
static volatile uint16_t timeBeforeNextSdSaveSeconds;
static const uint16_t SCREEN_TIMEOUT_SECONDS = 10;
static const uint16_t ONE_MINUTE_IN_SECONDS = 60;
const uint16_t SD_SAVE_PERIOD_SECONDS = 300;
const uint16_t SD_SAVE_PERIOD_FIFTH_SECONDS = SD_SAVE_PERIOD_SECONDS / 5;
static volatile bool secondTickFlag;
static volatile uint16_t secondCount;
static volatile bool oneMinuteTick;
static const uint16_t DEBOUNCE_TIMEOUT_MS = 1000;
static volatile uint16_t debounceTimeout;
// --------------------------------------------------------------------------------
void setupTime()
{
    setupTimer2();

    disableScreenTimeout();
    timeBeforeNextSdSaveSeconds = SD_SAVE_PERIOD_SECONDS;
    secondCount = ONE_MINUTE_IN_SECONDS;
    secondTickFlag = false;
    oneMinuteTick = false;
    debounceTimeout = 0;
}
// --------------------------------------------------------------------------------
void activateDebounceTimer()
{
    debounceTimeout = DEBOUNCE_TIMEOUT_MS;
}
// --------------------------------------------------------------------------------
bool isDebouncing()
{
    return (debounceTimeout > 0);
}
// --------------------------------------------------------------------------------
void advanceDebounce()
{
    if (debounceTimeout > 0)
    {
        debounceTimeout--;
    } // else already timed out
}
// --------------------------------------------------------------------------------
void secondTick()
{
    if (screenTimeoutValueSeconds > 0)
    {
        screenTimeoutValueSeconds--;

        if (screenTimeoutValueSeconds == 0)
        {
            setScreenTimedOut();
        } // else still counting
    } // else not timing out

    timeBeforeNextSdSaveSeconds--;

    if (timeBeforeNextSdSaveSeconds == 0)
    {
        setRequestSdDataSave(true);
        timeBeforeNextSdSaveSeconds = SD_SAVE_PERIOD_SECONDS;
    } // else still waiting

    secondTickFlag = true;

    secondCount--;

    if (secondCount == 0)
    {
        secondCount = ONE_MINUTE_IN_SECONDS;
        oneMinuteTick = true;
    } // else not one minute yet
}
// --------------------------------------------------------------------------------
void screenTimeoutKick()
{
    screenTimeoutValueSeconds = SCREEN_TIMEOUT_SECONDS;
}
// --------------------------------------------------------------------------------
void disableScreenTimeout()
{
    screenTimeoutValueSeconds = 0;
}
// --------------------------------------------------------------------------------
uint16_t getTimeTillNextSdSave()
{
    return timeBeforeNextSdSaveSeconds;
}
// --------------------------------------------------------------------------------
bool getSecondTick()
{
    return secondTickFlag;
}
// --------------------------------------------------------------------------------
void clearSecondTick()
{
    secondTickFlag = false;
}
// --------------------------------------------------------------------------------
bool getOneMinuteTick()
{
    return oneMinuteTick;
}
// --------------------------------------------------------------------------------
void clearOneMinuteTick()
{
    oneMinuteTick = false;
}
// --------------------------------------------------------------------------------
