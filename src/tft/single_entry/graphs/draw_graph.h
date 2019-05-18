#ifndef DRAW_GRAPH_H
#define DRAW_GRAPH_H
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
void drawGraph(uint8_t entryIndex);
void drawRYGGraph(uint8_t entryIndex);
void drawRYGYRGraph(uint8_t entryIndex);
uint16_t drawGradient(uint16_t topColour, uint16_t bottomColour, uint16_t topY, uint16_t heightY);
// --------------------------------------------------------------------------------
#endif // DRAW_GRAPH_H
