#ifndef LOGGERPRIORITY_HPP
#define LOGGERPRIORITY_HPP

namespace Scramble
{
    enum LoggerPriority
    {
        LOGGER_INFO    = 0,
        LOGGER_DEBUG   = 1,
        LOGGER_WARNING = 2,
        LOGGER_ERROR   = 3,
        LOGGER_FATAL   = 4
    };
}

#endif