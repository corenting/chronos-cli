#include <iostream>
#include <cmath>

#include "date.h"
#include "boost/date_time/gregorian/gregorian.hpp"

int Date::GetCurrentWeek() {
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();
    boost::gregorian::date ref(2014, 9, 1);
    float weeks = ((float) (today - ref).days()) / (float) 7;
    return (int) std::ceil(weeks);
}
