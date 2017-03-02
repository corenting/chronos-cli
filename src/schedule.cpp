#include "schedule.h"
#include <string>
#include <sstream>

#include "group.h"
#include "date.h"
#include "http_requests.h"

std::string Schedule::GetToday(Group group) {
    // Create url
    std::stringstream ss;
    ss << "Week/GetWeek/"
       << Date::GetCurrentWeek()
       << "/"
       << group.GetId()
       << "/"
       << group.GetTypeId();

    HttpRequest::HttpResponse res = HttpRequest::MakeRequest(ss.str());
    return res.body;
}