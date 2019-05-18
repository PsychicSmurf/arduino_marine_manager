#ifndef TOUCH_SCREEN_HANDLER_H
#define TOUCH_SCREEN_HANDLER_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------
#include "../tft/draw_template.h"
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
struct TouchPoint
{
    bool active;
    uint32_t tx;
    uint32_t ty;
};
// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
void setupTouchscreen();
void getAnyTouch(TouchPoint &touchPoint);
bool isTouchInButton(const TouchPoint &touchPoint, const ButtonCoords &button);
// --------------------------------------------------------------------------------
#endif // TOUCH_SCREEN_HANDLER_H
