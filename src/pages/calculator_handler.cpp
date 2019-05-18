// --------------------------------------------------------------------------------
#include "calculator_handler.h"
#include "../logger/logger.h"
#include "../data/app_status.h"
#include "../data/live_data.h"
// --------------------------------------------------------------------------------
void calculatorPageTick(const TouchPoint &touchPoint, const bool viewChanged, const bool calculatorUpdated)
{
    if (viewChanged)
    {
        drawCalculator();
    }

    if (touchPoint.active)
    {
        if (isTouchInButton(touchPoint, BUTTON_NAV1))
        {
            setAppStatus(PAGE_TODO_1);
        }

        for (uint8_t column = 0; column < 3; column++)
        {
            for (uint8_t row = 0; row < 4; row++)
            {
                if (isTouchInButton(touchPoint, buttonCoords[column][row]))
                {
                    switch (calcChars[row * 3 + column])
                    {
                        case 'C':
                            setCalculatorValue(0);
                            drawCalcValue();
                            break;

                        case '>':
                            // TODO                     addParameterValue(current_application_option, get_calculator_value());
                            setAppStatus(PAGE_TODO_1);
                            break;

                        default:
                            if (getCalculatorValue() < 1000) // Only 1-3 characters out of a maximum of 4
                            {
                                setCalculatorValue(getCalculatorValue() * 10); // Make space for the new digit to go into the units column
                            }
                            else // 4 numbers
                            {
                                uint8_t x = getCalculatorValue() % 1000; // remove the thousands
                                setCalculatorValue(x * 10); // Now we can make space for the new digit to go into the units column
                            }

                            setCalculatorValue(getCalculatorValue() + (calcChars[row * 3 + column] - 48)); // Ascii to Int
                            drawCalcValue();
                            break;
                    } // switch
                }
            } // for row
        } // for column
    }
}
// --------------------------------------------------------------------------------
