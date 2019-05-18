#ifndef FIXED_DATA_H
#define FIXED_DATA_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
enum EntryType
{
    entryType_PARAM = 1,
    entryType_CHORE = 2
};
const uint8_t NUMBER_OF_ENTRIES = 27;
const uint32_t MINUTES_IN_AN_HOUR = 60;
const uint32_t MINUTES_IN_A_DAY = 24 * MINUTES_IN_AN_HOUR;

struct ActivityTimes
{
    uint32_t    timerGreenEndsMinutes;
    uint32_t    timerAmberEndsMinutes;
};

struct GraphRanges
{
    bool        zeroIndexed; // True for “0 is good” entries (GYR Graph instead of RYGYR)
    // Entries can be compared against minutes (32-bit) as well as values (16-bit)
    uint32_t    topRed; // Maximum value allowed (capped)
    uint32_t    topAmber; // The Red/Amber boundary
    uint32_t    topGreen; // The Amber/Green boundary
    uint32_t    bottomGreen; // The Green/Amber boundary
    uint32_t    bottomAmber; // If not value_zero_indexed
    uint32_t    bottomRed; // If not value_zero_indexed
};

const uint8_t MAX_NAME_SIZE = 20;
const uint8_t MAX_SYMBOL_SIZE = 6;
const uint8_t MAX_UNITS_SIZE = 4;
struct EntryFixedData
{
    EntryType       entryType; // What type of entry is this
    char            name[MAX_NAME_SIZE]; // Text displayed to identify this entry
    char            symbol[MAX_SYMBOL_SIZE]; // Chemical symbol, if any, of this entry, if applicable
    char            units[MAX_UNITS_SIZE]; // What this entry is measured in, if applicable
    uint8_t         valueDecimalPlaces; // How many decimal places to add, if applicable
    uint16_t        typicalValue; // Perfect value for this entry, if applicable
    ActivityTimes   activityTimes; // When the entries should happen
    GraphRanges     graphRange; // Colour boundaries for entries
};
// --------------------------------------------------------------------------------
template <typename T> void PROGMEM_readAnything(const T *sce, T &dest)
{
    memcpy_P(&dest, sce, sizeof(T));
}
// --------------------------------------------------------------------------------
template <typename T> T PROGMEM_getAnything(const T *sce)
{
    static T temp;
    memcpy_P(&temp, sce, sizeof(T));
    return temp;
}
// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
char *getFixedEntryName(uint8_t index);
char *getFixedEntrySymbol(uint8_t index);
char *getFixedEntryNameUnits(uint8_t index);
EntryType getFixedEntryType(uint8_t index);
ActivityTimes getActivityTimes(uint8_t index);
GraphRanges getGraphRanges(uint8_t index);
uint8_t getFixedValueDecimalPlaces(uint8_t index);
uint16_t getFixedTypicalValue(uint8_t index);
// --------------------------------------------------------------------------------
#endif // FIXED_DATA_H
