#pragma once

#include "zynpch.h"

namespace Zyn {

    static const char* ANSI_RESET = "\033[0m";

    static const char* ANSI_RED = "\033[0;31m";
    static const char* ANSI_RED_BOLD = "\033[1;31m";

    static const char* ANSI_YELLOW = "\033[0;33m";
    static const char* ANSI_YELLOW_BOLD = "\033[1;33m";

    static const char* ANSI_BLUE_BOLD = "\033[38;5;153;1m";
    static const char* ANSI_BLUE = "\033[0;38;5;153m";

    static const char* ANSI_GREEN = "\033[0;32m";
    static const char* ANSI_GREEN_BOLD = "\033[1;32m";

    struct TimeData {

        int Hour;
        int Minute;
        int Second;

    };

    inline std::ostream& operator<<(std::ostream& os, const TimeData& data) { // TODO: MAKE FASTER
        return os << (data.Hour < 10 ? "0" : "") << data.Hour << ":" << (data.Minute < 10 ? "0" : "") << data.Minute << ":" << (data.Second < 10 ? "0": "") << data.Second;
    }

    class Log {

    public:
        enum LogLevel {
            LogLevelError = 0, LogLevelWarn = 1, LogLevelInfo = 2
        };

    private:

        static LogLevel s_LogLevel;

    public:

        [[nodiscard]] static LogLevel& GetLogLevel() { return s_LogLevel; }
        static void SetLogLevel(const LogLevel logLevel) { s_LogLevel = logLevel; }

        template<typename... Values>
        static void FormatTrace(const char* message, Values&&... values) {
            if (s_LogLevel >= LogLevelInfo) {
                std::cout << ANSI_GREEN_BOLD << "[" << GetCurrentTime() << "] [ZYN TRACE]: " << ANSI_GREEN_BOLD;
                printf(message, std::forward<Values>(values)...);
                std::cout << ANSI_RESET << std::endl;
            }
        }

        template<typename... Values>
        static void FormatInfo(const char* message, Values&&... values) {
            if (s_LogLevel >= LogLevelInfo) {
                std::cout << "[" << GetCurrentTime() << "] [ZYN INFO]: ";
                printf(message, std::forward<Values>(values)...);
                std::cout << std::endl;
            }
        }

        template<typename... Values>
        static void FormatWarn(const char* message, Values&&... values) {
            if (s_LogLevel >= LogLevelWarn) {
                std::cout << ANSI_YELLOW_BOLD << "[" << GetCurrentTime() << "] [ZYN WARN]: " << ANSI_YELLOW;
                printf(message, std::forward<Values>(values)...);
                std::cout << ANSI_RESET << std::endl;
            }
        }

        template<typename... Values>
        static void FormatError(const char* message, Values&&... values) {
            if (s_LogLevel >= LogLevelError) {
                std::cout << ANSI_RED_BOLD << "[" << GetCurrentTime() << "] [ZYN ERROR]: " << ANSI_RED;
                printf(message, std::forward<Values>(values)...);
                std::cout << ANSI_RESET << std::endl;
            }
        }

        template<typename T>
        static void Trace(const T& message) {
            if(s_LogLevel >= LogLevelInfo)
                std::cout << ANSI_GREEN_BOLD << "[" << GetCurrentTime() << "] [ZYN TRACE]: " << ANSI_GREEN << message << ANSI_RESET << std::endl;
        }

        template<typename T>
        static void Info(const T& message) {
            if(s_LogLevel >= LogLevelInfo)
                std::cout << "[" << GetCurrentTime() << "] [ZYN INFO]: " << message << std::endl;
        }

        template<typename T>
        static void Warn(const T& message) {
            if(s_LogLevel >= LogLevelWarn)
                std::cout << ANSI_YELLOW_BOLD << "[" << GetCurrentTime() << "] [ZYN WARN]: " << ANSI_YELLOW << message << ANSI_RESET << std::endl;
        }

        template<typename T>
        static void Error(const T& message) {
            if(s_LogLevel >= LogLevelError)
                std::cout << ANSI_RED_BOLD << "[" << GetCurrentTime() << "] [ZYN ERROR]: " << ANSI_RED << message << ANSI_RESET << std::endl;
        }

    private:

        static TimeData GetCurrentTime() {

            const time_t now = time(nullptr);
            const tm* localTime = localtime(&now);

            return { localTime->tm_hour, localTime->tm_min, localTime->tm_sec };

        }

    };

}