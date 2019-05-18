// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "draw_graph.h"
#include "draw_data_points.h"
#include "../../../logger/logger.h"
#include "../../../data/live_data.h"
#include "../../draw_template.h"
// --------------------------------------------------------------------------------
void drawGraph(const uint8_t entryIndex)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    GraphRanges graphData = getGraphRanges(entryIndex);

    if (graphData.zeroIndexed)
    {
        drawRYGGraph(entryIndex);
    }
    else
    {
        drawRYGYRGraph(entryIndex);
    }

    // Frame Outline
    tft.drawRect(TFT_LEFT, GRAPH_TOP, TFT_WIDTH, GRAPH_HEIGHT, TFT_WHITE);

    plotDataPoints(entryIndex);
}
// --------------------------------------------------------------------------------
void drawRYGGraph(const uint8_t entryIndex)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    uint16_t imageTop = GRAPH_TOP;

    // Red
    tft.fillRect(TFT_LEFT, imageTop, TFT_WIDTH, RYG_RED, TFT_RED);
    imageTop += RYG_RED;
    // Red to Yellow
    imageTop += drawGradient(TFT_RED, TFT_YELLOW, imageTop, RYG_GRADIENT_COLOUR_COUNT);
    // Yellow
    tft.fillRect(TFT_LEFT, imageTop, TFT_WIDTH, RYG_AMBER, TFT_YELLOW);
    imageTop += RYG_AMBER;
    // Yellow to Green
    imageTop += drawGradient(TFT_YELLOW, TFT_GREEN, imageTop, RYG_GRADIENT_COLOUR_COUNT);
    // Green
    tft.fillRect(TFT_LEFT, imageTop, TFT_WIDTH, RYG_GREEN, TFT_GREEN);
    imageTop += RYG_GREEN;
}
// --------------------------------------------------------------------------------
void drawRYGYRGraph(const uint8_t entryIndex)
{
    assert(entryIndex < NUMBER_OF_ENTRIES);

    uint16_t imageTop = GRAPH_TOP;

    // Red
    tft.fillRect(TFT_LEFT, imageTop, TFT_WIDTH, RGR_RED, TFT_RED);
    imageTop += RGR_RED;
    // Red to Yellow
    imageTop += drawGradient(TFT_RED, TFT_YELLOW, imageTop, RGR_GRADIENT_COLOUR_COUNT);
    // Yellow
    tft.fillRect(TFT_LEFT, imageTop, TFT_WIDTH, RGR_AMBER, TFT_YELLOW);
    imageTop += RGR_AMBER;
    // Yellow to Green
    imageTop += drawGradient(TFT_YELLOW, TFT_GREEN, imageTop, RGR_GRADIENT_COLOUR_COUNT);
    // Green
    tft.fillRect(TFT_LEFT, imageTop, TFT_WIDTH, RGR_GREEN, TFT_GREEN);
    imageTop += RGR_GREEN;
    // Green to Yellow
    imageTop += drawGradient(TFT_GREEN, TFT_YELLOW, imageTop, RGR_GRADIENT_COLOUR_COUNT);
    // Yellow
    tft.fillRect(TFT_LEFT, imageTop, TFT_WIDTH, RGR_AMBER, TFT_YELLOW);
    imageTop += RGR_AMBER;
    // Yellow to Red
    imageTop += drawGradient(TFT_YELLOW, TFT_RED, imageTop, RGR_GRADIENT_COLOUR_COUNT);
    // Red
    tft.fillRect(TFT_LEFT, imageTop, TFT_WIDTH, RGR_RED, TFT_RED);
    imageTop += RGR_RED;
}
// --------------------------------------------------------------------------------
uint16_t drawGradient(const uint16_t topColour, const uint16_t bottomColour, const uint16_t topY,
                      const uint16_t heightY)
{
    assert((topY + heightY) <= TFT_HEIGHT);
    assert(heightY > 0);

    for (uint16_t py = 0; py < heightY; py++)
    {
        uint16_t gradient_colour = getGradientColour(topColour, bottomColour, heightY, heightY - py);
        tft.drawLine(TFT_LEFT, topY + py, TFT_WIDTH, topY + py, gradient_colour);
    } // for py

    return heightY;
}
// --------------------------------------------------------------------------------
