#include <iostream>
#include <cmath>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>


#include "date.h"
#include "libs/json.hpp"
#include "http_requests.h"

using json = nlohmann::json;

int Date::GetCurrentWeek() {
    std::string service("Week/GetCurrentWeek/" +
                      std::to_string(73) + "/" + std::to_string(3));
    cpr::Response req = HttpRequest::MakeRequest(service);
    if (req.status_code != 200)
    {
        std::cout << "Error: cannot get current date for week calculation" << std::endl;
        exit(1);
    }
    json j = json::parse(req.text);
    if (!j["Id"].is_null()) {
        return j["Id"].get<int>();
    }
    std::cout << "Error: cannot get current date for week calculation" << std::endl;
    exit(1);
}

boost::posix_time::ptime Date::DateFromIsoString(std::string date) {
    //Adapt the string
    date.pop_back(); // remove the trailing Z
    boost::erase_all(date, "-");
    boost::erase_all(date, ":");

    return boost::posix_time::from_iso_string(date);
}
