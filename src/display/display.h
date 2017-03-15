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
    static OutputSystems getOutput(std::string output);
    static void print(std::vector<Event> events) {};
    static std::string truncateString(std::string string, long length);

    static std::string GetListAsString(std::vector<std::__cxx11::string> list);
};