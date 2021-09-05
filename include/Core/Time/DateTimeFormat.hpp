#ifndef DATE_TIME_FORMAT_HPP
#define DATE_TIME_FORMAT_HPP

namespace Scramble
{
    enum DateTimeFormat
    {
        HH_MM_SS_12,
        HH_MM_24,
        HH_MM_SS_24,

        MM_DD_YY,
        YYYY_MM_DD,
    
        FULL_WEEK,
        ABBREVIATED_WEEK,
    
        FULL_MONTH,
        ABBREVIATED_MONTH,
    
        FULL_DATE_TIME
    };
}

#endif