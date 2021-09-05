#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <stdio.h>

#include "../Logger/Logger.hpp"

#ifdef SCRAMBLE_NO_DEBUG
    #define SCRAMBLE_CORE_ASSERT(_EXPR)
    #define SCRAMBLE_CORE_ASSERT_LOG(_EXPR, ...)
#else
    #define SCRAMBLE_CORE_ASSERT(_EXPR)\
        if(!(_EXPR))\
        {\
            printf("Assertion Failed: %s | File %s | Line %d\n", #_EXPR, __FILE__, __LINE__);\
            exit(EXIT_FAILURE);\
        }

    #define SCRAMBLE_CORE_ASSERT_LOG(_EXPR, ...)\
        if(!(_EXPR))\
        {\
            printf("Assertion Failed: %s | File %s | Line %d\n", #_EXPR, __FILE__, __LINE__);\
            S_FATAL("%s", ##__VA_ARGS__);\
            exit(EXIT_FAILURE);\
        }
#endif

#endif