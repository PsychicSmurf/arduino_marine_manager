// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "timer_interrupt.h"
#include "time_manager.h"
#include "../logger/logger.h"
// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
static volatile uint16_t timer2Ms;
static const uint16_t ONE_SECOND_IN_MS = 1000;
// --------------------------------------------------------------------------------
// 8-bit Timer 2 Initialisation
// --------------------------------------------------------------------------------
// CPU Frequency = 16Mhz = 16,000,000
// Prescaler    1 (CS20)               = 16Mhz /    1 = 16,000,000
// Prescaler    8 (CS21)               = 16Mhz /    8 =  2,000,000
// Prescaler   32 (CS20 + CS21)        = 16Mhz /   32 =    500,000
// Prescaler   64 (CS22)               = 16Mhz /   64 =    250,000
// Prescaler  128 (CS22 + CS20)        = 16Mhz /  128 =    125,000
// Prescaler  256 (CS22 + CS21)        = 16Mhz /  256 =     62,500
// Prescaler 1024 (CS20 + CS21 + CS22) = 16Mhz / 1024 =     15,625
// Divide by frequency / second = 1,000
// Timer count = (16Mhz / prescaler / ticks_per_second) - 1
// = (16,000,000 / 128 / 1000) - 1 = 124
// Result must be < 256
// --------------------------------------------------------------------------------
void setupTimer2()
{
    TCCR2A = 0;     // Set entire TCCR1A register to 0
    TCCR2B = 0;     // Same for TCCR1B

    // Set compare match register to desired timer count
    OCR2A = 125 - 1;

    // Turn on CTC mode
    TCCR2A |= (1 << WGM21);

    // Set CS11 bit for 128 prescaler
    TCCR2B |= (1 << CS20);
    TCCR2B |= (1 << CS22);

    // Enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A);
}
// --------------------------------------------------------------------------------
// Timer 2 Interrupt Service Routine - 1ms
// --------------------------------------------------------------------------------
ISR(TIMER2_COMPA_vect)
{
    timer2Ms++;

    if (timer2Ms == ONE_SECOND_IN_MS)
    {
        timer2Ms = 0;
        secondTick();
    } // else no update yet

    advanceDebounce();
}
// --------------------------------------------------------------------------------
