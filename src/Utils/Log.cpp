#include "Log.h"

using namespace Zyn;

#ifdef NDEBUG

Log::LogLevel Log::s_LogLevel = Log::LogLevelError;

#else

Log::LogLevel Log::s_LogLevel = LogLevelInfo;

#endif