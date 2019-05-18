#ifndef UNIT_TEST
// --------------------------------------------------------------------------------
#include <Arduino.h>
#include <avr/pgmspace.h>

#include "logger/logger.h"

#include "timer/time_manager.h"

#include "data/app_status.h"
#include "data/storage/live_data_loader.h"
#include "data/storage/live_data_saver.h"
#include "data/storage/sd_card_handler.h"
#include "data/live_data.h"

#include "input/touch_screen_handler.h"

#include "pages/calculator_handler.h"
#include "pages/confirmation_handler.h"
#include "pages/entry_view_handler.h"
#include "pages/summary_handler.h"
#include "pages/todo_list_handler.h"
#include "pages/about_handler.h"

#include "tft/tft_handler.h"
#include "tft/draw_template.h"

#ifdef DEBUG
#include "debug/memdebug.h"
#endif
// --------------------------------------------------------------------------------
// https://docs.platformio.org/en/latest/plus/unit-testing.html
// --------------------------------------------------------------------------------
// Initialisation
// --------------------------------------------------------------------------------
void setup()
{
    setupLogger();
    logString(F("System Startup"));

    setupSdcard();
    setupTime();
    appStatusSetup();
    loadLiveData();
    setupTouchscreen();
    setupTft();
    setupCalculator();

    oneMinuteUpdateForLiveData();
    updateCurrentColourCategoryAndTimerValues();

    logString(F("Starting Operation"));

#ifdef DEBUG
    logString("Used memory = " + String(getMemoryUsed()));
    logString("Free memory = " + String(getFreeMemory()));
#endif
}
// --------------------------------------------------------------------------------
// Main Loop
// This loop may take longer that 1ms to cycle through so cannot be relied upon for timing
// --------------------------------------------------------------------------------
void loop()
{
    TouchPoint touchPoint;
    touchPoint.active = false;

    bool viewChanged = hasViewChanged();
    CurrentPage currentPage = getAppStatus();

    if (viewChanged == true)
    {
        setViewChanged(false);
        screenTimeoutKick();
    } // else view is still the same

    if (!viewChanged)
    {
        getAnyTouch(touchPoint);
    } // else on page transitions we don't want to process a duplicate touch

    switch (currentPage)
    {
        case PAGE_TODO_1:
        case PAGE_TODO_2:
        case PAGE_TODO_3:
            todoPageTick(touchPoint, viewChanged, hasTimeUpdated());
            setTimeUpdated(false);
            break;

        case PAGE_PARAMETER_STATUS:
        case PAGE_CHORE_STATUS_1:
        case PAGE_CHORE_STATUS_2:
            summaryPageTick(touchPoint, viewChanged);
            break;

        case PAGE_CALCULATOR:
            calculatorPageTick(touchPoint, viewChanged, hasCalculatorUpdated());
            setCalculatorUpdated(false);
            break;

        case PAGE_CONFIRMATION:
            confirmationPageTick(touchPoint, viewChanged);
            break;

        case PAGE_ABOUT:
            aboutPageTick(touchPoint, viewChanged);
            break;

        case PAGE_PARAMETER_VIEW:
        case PAGE_CHORE_VIEW:
            viewPageTick(touchPoint, viewChanged);
            break;
    } // switch

    if (getSdDataSaveRequested())
    {
        saveLiveData();
        setRequestSdDataSave(false);
    } // else not yet

    if (getSecondTick())
    {
        drawTimerBar();
        clearSecondTick();
    } // else second not changed yet

    if (getOneMinuteTick())
    {
        oneMinuteUpdateForLiveData();
        setTimeUpdated(true);
        clearOneMinuteTick();
    } // else not one minute yet
}
// --------------------------------------------------------------------------------
#endif