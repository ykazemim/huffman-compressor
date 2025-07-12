#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "config.hpp"
#include <iostream>

#define DEBUG_PRINT(x)                   \
    do                                   \
    {                                    \
        if (DEBUG_MODE)                  \
            std::cout << x << std::endl; \
    } while (0)

#endif // DEBUG_HPP
