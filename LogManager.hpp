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
    std::mutex mu_;
};