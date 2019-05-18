#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
extern const uint16_t SD_SAVE_PERIOD_SECONDS;
extern const uint16_t SD_SAVE_PERIOD_FIFTH_SECONDS;
// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
void setupTime();
void secondTick();
void disableScreenTimeout();
uint16_t getTimeTillNextSdSave();
bool getSecondTick();
void clearSecondTick();
bool getOneMinuteTick();
void clearOneMinuteTick();
void screenTimeoutKick();
void activateDebounceTimer();
bool isDebouncing();
void advanceDebounce();
// --------------------------------------------------------------------------------
#endif // TIMER_MANAGER_H
