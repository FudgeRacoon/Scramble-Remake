#ifndef LOCAL_TIME_DATE_HPP
#define LOCAL_TIME_DATE_HPP

#include <time.h>
#include <string>

#include "DateTimeFormat.hpp"
#include "../Common/Types.hpp"

namespace Scramble
{
    class LocalTimeDate
    {
    private:
        tm rawTimeInfo;

    private:
        U32 seconds;
        U32 minutes;
        U32 hours;
        U32 day;
        U32 month;
        U32 year;

    private:
        LocalTimeDate(tm rawTimeInfo, U32 year, U32 month, U32 day);
        LocalTimeDate(tm rawTimeInfo, U32 year, U32 month, U32 day, U32 hours);
        LocalTimeDate(tm rawTimeInfo, U32 year, U32 month, U32 day, U32 hours, U32 minutes);
        LocalTimeDate(tm rawTimeInfo, U32 year, U32 month, U32 day, U32 hours, U32 minutes, U32 seconds);
    
    public:
        U32 GetSeconds();
        U32 GetMinutes();
        U32 GetHours();
        U32 GetDay();
        U32 GetMonth();
        U32 GetYear();

    public:
        static LocalTimeDate GetCurrentDate();
        static LocalTimeDate GetCustomDate(U32 year, U32 month, U32 day);
        static LocalTimeDate GetCustomDate(U32 year, U32 month, U32 day, U32 hours);
        static LocalTimeDate GetCustomDate(U32 year, U32 month, U32 day, U32 hours, U32 minutes);
        static LocalTimeDate GetCustomDate(U32 year, U32 month, U32 day, U32 hours, U32 minutes, U32 seconds);

    public:
        const char* Format(DateTimeFormat format);
    };
}

#endif