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

class LogManager
{
public:
    enum class LogLevel
    {
        ERROR,
        WARNING,
        INFO,
        DEBUG
    };

    static LogManager& getInstance()
    {
        static LogManager instance;
        return instance;
    }

    void log(const std::string& message, LogLevel level)
    {
        std::lock_guard<std::mutex> lock(mu_);
        switch (level)
        {
        case LogLevel::ERROR:
            break;
        case LogLevel::WARNING:
            break;
        case LogLevel::INFO:
            break;
        case LogLevel::DEBUG:
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
};