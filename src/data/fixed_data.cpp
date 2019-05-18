// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "fixed_data.h"
#include "../logger/logger.h"
// --------------------------------------------------------------------------------
// Variables
// https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
// https://www.avrfreaks.net/forum/tut-c-gcc-and-progmem-attribute?name=PNphpBB2&file=viewtopic&t=38003
// https://stackoverflow.com/questions/37782154/reading-string-from-struct-in-arduino-progmem
// --------------------------------------------------------------------------------
static const EntryFixedData fixedData[NUMBER_OF_ENTRIES] PROGMEM =
{
    //  Type              Name                   Sym      Unit   DP  Typ    End Green              End Amber                  ZInd     TR    TY    TG    BG    BY    BR
    // Chores (14)
    { entryType_CHORE, "Auto-Feeder Check",   "",      "",    0,    0, { MINUTES_IN_A_DAY *  3, MINUTES_IN_A_DAY *  1 }, { true,     0,    0,    0,    0,    0,    0 } },
    { entryType_CHORE, "Auto-Topup Upkeep",   "",      "",    0,    0, { MINUTES_IN_A_DAY *  3, MINUTES_IN_A_DAY *  1 }, { true,     0,    0,    0,    0,    0,    0 } },
    { entryType_CHORE, "Protein Skimmer",     "",      "",    0,    0, { MINUTES_IN_A_DAY *  6, MINUTES_IN_A_DAY *  2 }, { true,     0,    0,    0,    0,    0,    0 } },
    { entryType_CHORE, "Target Feeding",      "",      "",    0,    0, { MINUTES_IN_A_DAY *  6, MINUTES_IN_A_DAY *  2 }, { true,     0,    0,    0,    0,    0,    0 } },
    { entryType_CHORE, "Filter Sock Clean",   "",      "",    0,    0, { MINUTES_IN_A_DAY *  9, MINUTES_IN_A_DAY *  3 }, { true,     0,    0,    0,    0,    0,    0 } },
    { entryType_CHORE, "Filter Floss Change", "",      "",    0,    0, { MINUTES_IN_A_DAY * 15, MINUTES_IN_A_DAY *  5 }, { true,     0,    0,    0,    0,    0,    0 } },
    { entryType_CHORE, "Water Change",        "",      "",    0,    0, { MINUTES_IN_A_DAY * 21, MINUTES_IN_A_DAY *  7 }, { true,     0,    0,    0,    0,    0,    0 } },
    { entryType_CHORE, "Rowaphos Reactor",    "",      "",    0,    0, { MINUTES_IN_A_DAY * 30, MINUTES_IN_A_DAY * 10 }, { true,     0,    0,    0,    0,    0,    0 } },
    { entryType_CHORE, "Activated Carbon",    "",      "",    0,    0, { MINUTES_IN_A_DAY * 30, MINUTES_IN_A_DAY * 10 }, { true,     0,    0,    0,    0,    0,    0 } },
    { entryType_CHORE, "Sump Clean",          "",      "",    0,    0, { MINUTES_IN_A_DAY * 39, MINUTES_IN_A_DAY * 13 }, { true,     0,    0,    0,    0,    0,    0 } },
    { entryType_CHORE, "Tank Pump Clean",     "",      "",    0,    0, { MINUTES_IN_A_DAY * 39, MINUTES_IN_A_DAY * 13 }, { true,     0,    0,    0,    0,    0,    0 } },
    { entryType_CHORE, "Add Coral Food",      "",      "",    0,    0, { MINUTES_IN_A_DAY *  7, MINUTES_IN_A_DAY *  7 }, { true,     0,    0,    0,    0,    0,    0 } },
    { entryType_CHORE, "Aiptasia Weeding",    "",      "",    0,    0, { MINUTES_IN_A_DAY *  7, MINUTES_IN_A_DAY *  7 }, { true,     0,    0,    0,    0,    0,    0 } },
    { entryType_CHORE, "Tank/Back Clean",     "",      "",    0,    0, { MINUTES_IN_A_DAY * 14, MINUTES_IN_A_DAY * 14 }, { true,     0,    0,    0,    0,    0,    0 } },
    { entryType_CHORE, "Test",                "",      "",    0,    0, { MINUTES_IN_A_DAY * 14, MINUTES_IN_A_DAY * 14 }, { true,     0,    0,    0,    0,    0,    0 } },
    { entryType_CHORE, "Test",                "",      "",    0,    0, { MINUTES_IN_A_DAY * 14, MINUTES_IN_A_DAY * 14 }, { true,     0,    0,    0,    0,    0,    0 } },
    // Readings (11)
    { entryType_PARAM, "Temperature",         "°C",    "°C",  1,  250, { MINUTES_IN_A_DAY *  3, MINUTES_IN_A_DAY *  1 }, { false,  235,  240,  245,  255,  260,  265 } },
    { entryType_PARAM, "Salinity",            "NaCl",  "sg",  3, 1025, { MINUTES_IN_A_DAY *  9, MINUTES_IN_A_DAY *  3 }, { false, 1023, 1024, 1025, 1026, 1027, 1028 } },
    { entryType_PARAM, "Phosphate",           "PO4",   "ppm", 2,    0, { MINUTES_IN_A_DAY *  9, MINUTES_IN_A_DAY *  3 }, { true,     0,    0,    0,    3,   10,   50 } },
    { entryType_PARAM, "Nitrate",             "NO3",   "ppm", 0,    0, { MINUTES_IN_A_DAY *  9, MINUTES_IN_A_DAY *  3 }, { true,     0,    0,    0,   25,   50,  200 } },
    { entryType_PARAM, "Nitrite",             "NO2",   "ppm", 2,    0, { MINUTES_IN_A_DAY *  9, MINUTES_IN_A_DAY *  3 }, { true,     0,    0,    0,   10,   25,   50 } },
    { entryType_PARAM, "Ammonia",             "NH3",   "ppm", 2,    0, { MINUTES_IN_A_DAY *  9, MINUTES_IN_A_DAY *  3 }, { true,     0,    0,    0,    5,   15,   25 } },
    { entryType_PARAM, "Hardness",            "CaCO3", "dKH", 1,   90, { MINUTES_IN_A_DAY * 15, MINUTES_IN_A_DAY *  5 }, { false,   70,   75,   80,  100,  105,  110 } },
    { entryType_PARAM, "Acidity",             "pH",    "pH",  2,  815, { MINUTES_IN_A_DAY * 15, MINUTES_IN_A_DAY *  5 }, { false,  740,  770,  800,  830,  860,  890 } },
    { entryType_PARAM, "Magnesium",           "Mg",    "ppm", 0, 1300, { MINUTES_IN_A_DAY * 21, MINUTES_IN_A_DAY *  7 }, { false, 1150, 1200, 1250, 1350, 1400, 1450 } },
    { entryType_PARAM, "Calcium",             "Ca",    "ppm", 0,  415, { MINUTES_IN_A_DAY * 21, MINUTES_IN_A_DAY *  7 }, { false,  320,  350,  380,  450,  480,  510 } },
    { entryType_PARAM, "Silica",              "SiO2",  "ppm", 2,    0, { MINUTES_IN_A_DAY * 21, MINUTES_IN_A_DAY *  7 }, { true,     0,    0,    0,   10,   25,  100 } }
};
// --------------------------------------------------------------------------------
static char tempName[MAX_NAME_SIZE];
char *getFixedEntryName(const uint8_t index)
{
    assert(index < NUMBER_OF_ENTRIES);

    PROGMEM_readAnything(&fixedData[index].name, tempName);

    return tempName;
}
// --------------------------------------------------------------------------------
static char tempSymbol[MAX_SYMBOL_SIZE];
char *getFixedEntrySymbol(const uint8_t index)
{
    assert(index < NUMBER_OF_ENTRIES);

    PROGMEM_readAnything(&fixedData[index].symbol, tempSymbol);

    return tempSymbol;
}
// --------------------------------------------------------------------------------
static char tempUnits[MAX_UNITS_SIZE];
char *getFixedEntryNameUnits(const uint8_t index)
{
    assert(index < NUMBER_OF_ENTRIES);

    PROGMEM_readAnything(&fixedData[index].units, tempUnits);

    return tempUnits;
}
// --------------------------------------------------------------------------------
EntryType getFixedEntryType(const uint8_t index)
{
    assert(index < NUMBER_OF_ENTRIES);

    EntryType tempEntryType;

    PROGMEM_readAnything(&fixedData[index].entryType, tempEntryType);

    return tempEntryType;
}
// --------------------------------------------------------------------------------
ActivityTimes getActivityTimes(const uint8_t index)
{
    assert(index < NUMBER_OF_ENTRIES);

    ActivityTimes tempActivityTimes;

    PROGMEM_readAnything(&fixedData[index].activityTimes, tempActivityTimes);

    return tempActivityTimes;
}
// --------------------------------------------------------------------------------
GraphRanges getGraphRanges(const uint8_t index)
{
    assert(index < NUMBER_OF_ENTRIES);

    GraphRanges tempGraphRanges;

    PROGMEM_readAnything(&fixedData[index].graphRange, tempGraphRanges);

    return tempGraphRanges;
}
// --------------------------------------------------------------------------------
uint8_t getFixedValueDecimalPlaces(const uint8_t index)
{
    assert(index < NUMBER_OF_ENTRIES);

    uint8_t tempValueDecimalPlaces;

    PROGMEM_readAnything(&fixedData[index].valueDecimalPlaces, tempValueDecimalPlaces);

    return tempValueDecimalPlaces;
}
// --------------------------------------------------------------------------------
uint16_t getFixedTypicalValue(const uint8_t index)
{
    assert(index < NUMBER_OF_ENTRIES);

    uint16_t tempTypicalValue;

    PROGMEM_readAnything(&fixedData[index].typicalValue, tempTypicalValue);

    return tempTypicalValue;
}
// --------------------------------------------------------------------------------
