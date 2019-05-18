#ifndef DRAW_ABOUT_H
#define DRAW_ABOUT_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------
#include "../draw_template.h"
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
const ButtonCoords BUTTON_ABOUT_1 = { TFT_LEFT + BUTTON_WIDTH, (1 * ROW_SPACING) + FIRST_ROW_TOP,
                                      TFT_WIDTH - BUTTON_WIDTH, (1 * ROW_SPACING) + ROW_HEIGHT + FIRST_ROW_TOP
                                    };
const ButtonCoords BUTTON_ABOUT_2 = { TFT_LEFT + BUTTON_WIDTH, (5 * ROW_SPACING) + FIRST_ROW_TOP,
                                      TFT_WIDTH - BUTTON_WIDTH, (5 * ROW_SPACING) + ROW_HEIGHT + FIRST_ROW_TOP
                                    };
const ButtonCoords BUTTON_ABOUT_3 = { TFT_LEFT + BUTTON_WIDTH, (9 * ROW_SPACING) + FIRST_ROW_TOP,
                                      TFT_WIDTH - BUTTON_WIDTH, (9 * ROW_SPACING) + ROW_HEIGHT + FIRST_ROW_TOP
                                    };

// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
void drawAbout();
// --------------------------------------------------------------------------------
#endif // DRAW_ABOUT_H
