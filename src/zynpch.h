#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <algorithm>
#include <cctype>
#include <regex>
#include <memory>
#include <thread>
#include <utility>
#include <string_view>
#include <cstdio>

#include <string>
#include <stack>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include <filesystem>

#include "Utils/Log.h"

#ifndef NDEBUG
#define ZYN_DEBUG 1
#else
#define ZYN_DEBUG 0
#endif

#define ZYN_PROFILE ZYN_DEBUG

#include "Debug/Profile.h"