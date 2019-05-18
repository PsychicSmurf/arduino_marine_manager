// --------------------------------------------------------------------------------
#include <Arduino.h>
#include "assert_handler.h"
#include "logger.h"
#include <stdio.h>
#include <stdint.h>
#include <avr/pgmspace.h>
// --------------------------------------------------------------------------------
const uint8_t MAX_LOG_SIZE = 100;
// --------------------------------------------------------------------------------
// handle diagnostic informations given by assertion and abort program execution:
void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp)
{
    // THIS FUNCTION IS RAM INTENSIVE AS IT CAUSES THE ASSERT() MACRO TO STORE
    // THE PAREMTERS IN EACH ASSERT STATEMENT.
    // Transmit diagnostic informations through serial link.

    //logString(__func);
    logString(__file);
    logString((uint16_t)__lineno);
    //logString(__sexp);

    // Stop program execution.
    noInterrupts();

    while (true)
    {
        // Do Nothing
    }
}
// --------------------------------------------------------------------------------
