// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "touch_screen_handler.h"
#include "../logger/logger.h"
#include <TouchScreen.h>
#include "../timer/time_manager.h"
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

// P = Lower number is harder press
#define MINPRESSURE 100
#define MAXPRESSURE 1000

static const uint16_t TS_WIDTH = 320;
static const uint16_t TS_HEIGHT = 480;

// Length = X = 70 (top) to 960 (bottom) 890 for 480 pixels
// Now confine numbers to actual screen which is smaller
#define TS_MINX 80
#define TS_MAXX 940

// Width = y = 915 (left) to 115 (right) = 810 for 320 pixels
// Now confine numbers to actual screen which is smaller
#define TS_MINY 130
#define TS_MAXY 900
// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
const uint16_t X_PLATE_OHMS = 300;
static TouchScreen touchScreen = TouchScreen(XP, YP, XM, YM, X_PLATE_OHMS);
// --------------------------------------------------------------------------------
void setupTouchscreen()
{
    //  Empty
}
// --------------------------------------------------------------------------------
void getAnyTouch(TouchPoint &touchPoint)
{
    touchPoint.active = false;

    digitalWrite(13, HIGH);
    TSPoint p = touchScreen.getPoint();
    digitalWrite(13, LOW);

    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if ((p.z > MINPRESSURE && p.z < MAXPRESSURE) && (!isDebouncing()))
    {
        if ((p.x >= TS_MINX) && (p.x <= TS_MAXX) && (p.y >= TS_MINY) && (p.y <= TS_MAXY))
        {
            touchPoint.ty = p.x - TS_MINX;
            touchPoint.ty *= (TS_HEIGHT);
            touchPoint.ty /= (TS_MAXX - TS_MINX);

            touchPoint.tx = p.y - TS_MINY;
            touchPoint.tx *= (TS_WIDTH);
            touchPoint.tx /= (TS_MAXY - TS_MINY);
            touchPoint.tx = (TS_WIDTH - touchPoint.tx);

            touchPoint.active = true;

            activateDebounceTimer();
            screenTimeoutKick();
        } // else invalid coordinates
    } // else no touch
}
// --------------------------------------------------------------------------------
bool isTouchInButton(const TouchPoint &touchPoint, const ButtonCoords &button)
{
    bool retVal = false;

    if ((touchPoint.tx > button.topLeftX) &&
            (touchPoint.tx < button.bottomRightX) &&
            (touchPoint.ty > button.topLeftY) &&
            (touchPoint.ty < button.bottomRightY))
    {
        retVal = true;
    }

    return retVal;
}
// --------------------------------------------------------------------------------
