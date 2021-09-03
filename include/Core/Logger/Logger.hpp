#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "LoggerPriority.hpp"

#include "../Time/LocalTimeDate.hpp"
#include "../Time/DateTimeFormat.hpp"

namespace Scramble
{
    class Logger
    {
    private:
        template <typename... Args>
        static void PrintString(LoggerPriority priority, const char* message, Args... args)
        {
            switch(priority)
            {
                case LOGGER_INFO :    
                {
                    LocalTimeDate date = LocalTimeDate::GetCurrentDate();
                    const char* buffer = date.Format(DateTimeFormat::HH_MM_SS_24);
                       
                    printf("\033[34m");
                    printf("[INFO][%s]: ", buffer);
                    printf(message, args...);
                    printf("\n");  
                    printf("\033[0m");

                    delete[] buffer;

                    break;
                }
                case LOGGER_DEBUG :   
                {
                    LocalTimeDate date = LocalTimeDate::GetCurrentDate();

                    const char* buffer = date.Format(DateTimeFormat::HH_MM_SS_24);
                    printf("\033[33m");
                    printf("[DEBUG][%s]: ", buffer);
                    printf(message, args...);
                    printf("\n");  
                    printf("\033[0m");
                    
                    delete[] buffer;
                    
                    break;
                }
                case LOGGER_WARNING : 
                {
                    LocalTimeDate date = LocalTimeDate::GetCurrentDate();
                    const char* buffer = date.Format(DateTimeFormat::HH_MM_SS_24);

                    printf("\033[32m");
                    printf("[WARNING][%s]: ", buffer);
                    printf(message, args...);
                    printf("\n");  
                    printf("\033[0m");
                    
                    delete[] buffer;
                    
                    break;
                }
                case LOGGER_ERROR :   
                {
                    LocalTimeDate date = LocalTimeDate::GetCurrentDate();
                    const char* buffer = date.Format(DateTimeFormat::HH_MM_SS_24);

                    printf("\033[91m");
                    printf("[ERROR][%s]: ", buffer);
                    printf(message, args...);
                    printf("\n");  
                    printf("\033[0m");

                    delete[] buffer;
                    
                    break;
                }
                case LOGGER_FATAL :   
                {
                    LocalTimeDate date = LocalTimeDate::GetCurrentDate();
                    const char* buffer = date.Format(DateTimeFormat::HH_MM_SS_24);

                    printf("\033[31m");
                    printf("[FATAL][%s]: ", buffer);
                    printf(message, args...);
                    printf("\n");  
                    printf("\033[0m");
                
                    delete[] buffer;
                    
                    break;
                }
            }
        }

    public:
        template <typename... Args>
        static void LogInfo(const char* message, Args... args)
        {
            PrintString(LoggerPriority::LOGGER_INFO, message, args...);   
        }
        template <typename... Args>
        static void LogDebug(const char* message, Args... args)
        {
            PrintString(LoggerPriority::LOGGER_DEBUG, message, args...);
        }
        template <typename... Args>
        static void LogWarning(const char* message, Args... args)
        {
            PrintString(LoggerPriority::LOGGER_WARNING, message, args...);    
        }
        template <typename... Args>
        static void LogError(const char* message, Args... args)
        {
            PrintString(LoggerPriority::LOGGER_ERROR, message, args...);
        }   
        template <typename... Args>
        static void LogFatal(const char* message, Args... args)
        {
            PrintString(LoggerPriority::LOGGER_FATAL, message, args...);
        }
    };
}

#endif