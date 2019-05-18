#ifndef DRAW_DATA_POINTS_H
#define DRAW_DATA_POINTS_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------
#include "../../../data/app_status.h"
#include "../../../data/fixed_data.h"
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
void plotDataPoints(uint8_t entryIndex);
uint32_t scaleParameterValue(uint32_t paramValue, const GraphRanges &paramRanges);
uint32_t scaleChoreTime(uint16_t choreTime, ActivityTimes chore_ranges);
uint32_t convertTimeToScale(uint32_t choreTime, uint32_t topY, uint32_t bottomY, uint32_t rangeStart,
                            uint32_t rangeEnd);
// --------------------------------------------------------------------------------
#endif // DRAW_DATA_POINTS_H
