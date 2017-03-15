#include "event.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "display.h"

Display::OutputSystems Display::getOutput(std::string output) {
        if (output == "line")
            return Line;
        if (output == "ascii")
            return Ascii;
        std::cout << "Error: " << output << " is not a valid output option" << std::endl;
        exit(1);
}

std::string Display::truncateString(std::string string, long length) {
    if (string.length() <= 1)
        return string;
    if (string.length() <= length)
        return string;
    return string.substr(0, length - 1) + "…";
}

std::string Display::GetListAsString(std::vector<std::string> list) {
    if (list.size() == 1)
        return list.at(0);
    if (list.size() == 0)
        return std::string("");
    std::stringstream ss;
    for (int i = 0; i < list.size() - 2; i++)
    {
        ss << list.at(i) << ", ";
    }
    ss << list.at(list.size() - 1);
    return ss.str();
}