#include <iostream>
#include <cmath>

#include "date.h"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/algorithm/string.hpp>

int Date::GetCurrentWeek() {
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();
    boost::gregorian::date ref(2014, 9, 1);
    float weeks = ((float) (today - ref).days()) / (float) 7;
    return (int) std::ceil(weeks);
}

boost::posix_time::ptime Date::DateFromIsoString(std::string date) {
    //Adapt the string
    date.pop_back(); // remove the trailing Z
    boost::erase_all(date, "-");
    boost::erase_all(date, ":");

    return boost::posix_time::from_iso_string(date);
}

