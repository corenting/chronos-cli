#pragma once
#include <string>
#include "../models/event.h"
#include "boost/date_time/posix_time/posix_time.hpp"

class Display {
public:
    enum OutputSystems {
        Line,
        Ascii,
    };
    static OutputSystems GetOutput(std::string output);
    static void Print(std::vector<Event> events) {};
    static std::string TruncateString(std::string string, long length);

    static std::string GetListAsString(std::vector<std::string> list);
};