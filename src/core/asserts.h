#ifndef ASSERTS_H 
#define ASSERTS_H

#define GASSERTIONS_ENABLED

#ifdef GASSERTIONS_ENABLED 
//NOTE: works only on gcc
//TODO: ad other cases
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else 
#include <signal.h>     //ci sono altri modi??
#define debugBreak() raise(SIGTRAP)  //ci sono altri modi??
#endif

void reportAsserionFaliure(const char* expression, const char* message, const char* file, int line);

//NOTE: better check true statment then (!expr) becouse in some situation it doesn't works
#define GASSERT(expr) {                                         \
        if (expr) {                                             \
        } else {                                                \
        reportAsserionFaliure(#expr, "", __FILE__, __LINE__);   \
        debugBreak();                                           \
        }                                                       \
    }                                                           \



#define GASSERT_MSG(expr, message) {                                \
        if (expr) {                                                 \
        } else {                                                    \
        reportAsserionFaliure(#expr, message, __FILE__, __LINE__);  \
        debugBreak();                                               \
        }                                                           \
    }                                                               \

#ifdef DEBUG
#define GASSERT_DEBUG(expr, message) {                              \
        if (expr) {                                                 \
        } else {                                                    \
        reportAsserionFaliure(#expr, message, __FILE__, __LINE__);  \
        debugBreak();                                               \
        }                                                           \
    }                                                               \
#else
#define GASSERT_DEBUG(expr)
#endif

#else
#define GASSERT(expr)
#define GASSERT_MSG(expr, message)
#define GASSERT_DEBUG(expr)
#endif 

#endif 
