#include "Core/Time/LocalTimeDate.hpp"
using namespace Scramble;

LocalTimeDate::LocalTimeDate(tm rawTimeInfo, U32 year, U32 month, U32 day)
    :rawTimeInfo(rawTimeInfo), year(year), month(month), day(day)
{
    this->seconds = rawTimeInfo.tm_sec;
    this->minutes = rawTimeInfo.tm_min;
    this->hours = rawTimeInfo.tm_hour;
}
LocalTimeDate::LocalTimeDate(tm rawTimeInfo, U32 year, U32 month, U32 day, U32 hours)
    :rawTimeInfo(rawTimeInfo), year(year), month(month), day(day), hours(hours)
{
    this->seconds = rawTimeInfo.tm_sec;
    this->minutes = rawTimeInfo.tm_min;
}
LocalTimeDate::LocalTimeDate(tm rawTimeInfo, U32 year, U32 month, U32 day, U32 hours, U32 minutes)
    :rawTimeInfo(rawTimeInfo), year(year), month(month), day(day), hours(hours), minutes(minutes)
{
    this->seconds = rawTimeInfo.tm_sec;
}
LocalTimeDate::LocalTimeDate(tm rawTimeInfo, U32 year, U32 month, U32 day, U32 hours, U32 minutes, U32 seconds)
    :rawTimeInfo(rawTimeInfo), year(year), month(month), day(day), hours(hours), minutes(minutes), seconds(seconds) {}

U32 LocalTimeDate::GetSeconds()
{
    return this->seconds;
}
U32 LocalTimeDate::GetMinutes()
{
    return this->minutes;
}
U32 LocalTimeDate::GetHours()
{
    return this->hours;
}
U32 LocalTimeDate::GetDay()
{
    return this->day;
}
U32 LocalTimeDate::GetMonth()
{
    return this->month;
}
U32 LocalTimeDate::GetYear()
{
    return this->year;
}

LocalTimeDate LocalTimeDate::GetCurrentDate()
{
    time_t rawTime;
    tm* rawTimeInfo;

    time(&rawTime);
    rawTimeInfo = localtime(&rawTime);
 
    return LocalTimeDate(
        *rawTimeInfo,
        rawTimeInfo->tm_year + 1900,
        rawTimeInfo->tm_mon + 1,
        rawTimeInfo->tm_mday
    );
}
LocalTimeDate LocalTimeDate::GetCustomDate(U32 year, U32 month, U32 day)
{
    time_t rawTime;
    tm* rawTimeInfo;

    time(&rawTime);
    rawTimeInfo = localtime(&rawTime);

    rawTimeInfo->tm_year = year;
    rawTimeInfo->tm_mon = month;
    rawTimeInfo->tm_mday = day;

    LocalTimeDate date(
        *rawTimeInfo,
        rawTimeInfo->tm_year,
        rawTimeInfo->tm_mon,
        rawTimeInfo->tm_mday
    );

    return date;
}
LocalTimeDate LocalTimeDate::GetCustomDate(U32 year, U32 month, U32 day, U32 hours)
{
    time_t rawTime;
    tm* rawTimeInfo;

    time(&rawTime);
    rawTimeInfo = localtime(&rawTime);

    rawTimeInfo->tm_year = year;
    rawTimeInfo->tm_mon = month;
    rawTimeInfo->tm_mday = day;
    rawTimeInfo->tm_hour = hours;

    LocalTimeDate date(
        *rawTimeInfo,
        rawTimeInfo->tm_year,
        rawTimeInfo->tm_mon,
        rawTimeInfo->tm_mday,
        rawTimeInfo->tm_hour
    );

    return date;
}
LocalTimeDate LocalTimeDate::GetCustomDate(U32 year, U32 month, U32 day, U32 hours, U32 minutes)
{
    time_t rawTime;
    tm* rawTimeInfo;

    time(&rawTime);
    rawTimeInfo = localtime(&rawTime);

    rawTimeInfo->tm_year = year;
    rawTimeInfo->tm_mon = month;
    rawTimeInfo->tm_mday = day;
    rawTimeInfo->tm_hour = hours;
    rawTimeInfo->tm_min = minutes;

    LocalTimeDate date(
        *rawTimeInfo,
        rawTimeInfo->tm_year,
        rawTimeInfo->tm_mon,
        rawTimeInfo->tm_mday,
        rawTimeInfo->tm_hour,
        rawTimeInfo->tm_min 
    );

    return date;
}
LocalTimeDate LocalTimeDate::GetCustomDate(U32 year, U32 month, U32 day, U32 hours, U32 minutes, U32 seconds)
{
    time_t rawTime;
    tm* rawTimeInfo;

    time(&rawTime);
    rawTimeInfo = localtime(&rawTime);

    rawTimeInfo->tm_year = year;
    rawTimeInfo->tm_mon = month;
    rawTimeInfo->tm_mday = day;
    rawTimeInfo->tm_hour = hours;
    rawTimeInfo->tm_min = minutes;
    rawTimeInfo->tm_sec = seconds;

    LocalTimeDate date(
        *rawTimeInfo,
        rawTimeInfo->tm_year,
        rawTimeInfo->tm_mon,
        rawTimeInfo->tm_mday,
        rawTimeInfo->tm_hour,
        rawTimeInfo->tm_min,
        rawTimeInfo->tm_sec 
    );

    return date;
}

const char* LocalTimeDate::Format(DateTimeFormat format)
{
    const char* specifier;
    switch(format)
    {
        case HH_MM_SS_12:       specifier = "%I:%M:%S %p"; break;
        case HH_MM_24:          specifier = "%H:%M"; break;
        case HH_MM_SS_24:       specifier = "%H:%M:%S"; break;

        case MM_DD_YY:          specifier = "%m/%d/%y"; break;
        case YYYY_MM_DD:        specifier = "%Y-%m-%d"; break;
        
        case FULL_WEEK:         specifier = "%A"; break;
        case ABBREVIATED_WEEK:  specifier = "%a"; break;
        
        case FULL_MONTH:        specifier = "%B"; break;
        case ABBREVIATED_MONTH: specifier = "%b"; break;
        
        case FULL_DATE_TIME:    specifier = "%c"; break;
    }

    char* buffer = new char[32];
    buffer[31] = '\0';

    strftime(buffer, 32, specifier, &this->rawTimeInfo);
    return buffer;
}