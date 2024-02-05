/**
 * @file LogManager.hpp
 * @author Jeekun Park (jeekunp@naver.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <sys/stat.h>

#if !defined(__clang__) && !defined(__GNUC__)
    #define __PRETTY_FUNCTION__ ("not supported")
#endif

#define LOG_ERROR(msg)      LogManager::getInstance().log((msg), LogManager::ERROR, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define LOG_WARNING(msg)    LogManager::getInstance().log((msg), LogManager::WARNING, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define LOG_INFO(msg)       LogManager::getInstance().log((msg), LogManager::INFO, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define LOG_DEBUG(msg)      LogManager::getInstance().log((msg), LogManager::DEBUG, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define LOG_FATAL(msg)      LogManager::getInstance().log((msg), LogManager::FATAL, __FILE__, __LINE__, __PRETTY_FUNCTION__)

/* #define PRINT_ERROR(msg)
#define PRINT_WARNING(msg)
#define PRINT_INFO(msg)
#define PRINT_DEBUG(msg)
#define PRINT_FATAL(msg) */

class LogManager
{
public:
    enum LogLevel
    {
        ERROR = 0,
        WARNING,
        INFO,
        DEBUG,
        FATAL
    };

    static LogManager& getInstance()
    {
        static LogManager instance;
        return instance;
    }

    void log(const std::string& message, LogLevel level, const char *file, int line, const char *function)
    {
        std::lock_guard<std::mutex> lock(mu_);
        switch (level)
        {
        case ERROR:
            mLogFile << formattedStr(currentTimeStr(), "ERROR", file, line, function, message);
            break;
        case WARNING:
            mLogFile << formattedStr(currentTimeStr(), "WARN", file, line, function, message);
            break;
        case INFO:
            mLogFile << formattedStr(currentTimeStr(), "INFO", file, line, function, message);
            break;
        case DEBUG:
            mLogFile << formattedStr(currentTimeStr(), "DEBUG", file, line, function, message);
            break;
        case FATAL:
            mLogFile << formattedStr(currentTimeStr(), "FATAL", file, line, function, message);
            break;
        default:
            break;
        }
    }


private:
    std::ofstream mLogFile;
    std::mutex mu_;
private:
    LogManager()
    {
        createLogFolder();
        std::ostringstream fileName;
        fileName << "log/log_" << currentTimeStr() << ".txt";
        mLogFile.open(fileName.str().c_str(), std::ios::app);
    }
    LogManager(const LogManager&);
    LogManager& operator=(const LogManager&);
    ~LogManager()
    {
        if (mLogFile.is_open())
            mLogFile.close();
    }

    void createLogFolder()
    {
        struct stat st;
        if (stat("log", &st) != 0)
            mkdir("log", 0777);
    }
    
    std::string currentTimeStr()
    {
        std::time_t now = std::time(0);
        std::tm* localTime = std::localtime(&now);
        std::ostringstream time;
        time << (localTime->tm_year + 1900) << '-'
             << (localTime->tm_mon + 1) << '-'
             << localTime->tm_mday << '_'
             << localTime->tm_hour << '-'
             << localTime->tm_min << '-'
             << localTime->tm_sec;
        return time.str();
    }

    std::string formattedStr(const std::string& timeStamp, const std::string& level,
                             const char* file, int line, const char* function,
                             const std::string& message)
    {
        std::ostringstream res;

        if (level == "DEBUG")
        {
            res << timeStamp << ": "
                << file << ":" << line << ":" << function << ": ["
                << level << "] " << message;
        }
        else
            res << timeStamp << ": [" << level << "] " << message;
        
        return res.str();
    }
};