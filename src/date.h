#pragma once

#include <string>
#include <boost/date_time/gregorian/greg_date.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

class Date {
public:
    static int GetCurrentWeek();
    static boost::posix_time::ptime DateFromIsoString(std::string date);
};