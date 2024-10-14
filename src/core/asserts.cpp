#include "asserts.h"
#include "logger.h"

void reportAsserionFaliure(const char* expression, const char* message, const char* file, int line) {
    GFATAL("Assertion Faliure: %s, message: '%s', in file: %s, line %d", expression, message, file, line);
}
