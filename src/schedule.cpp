#include "schedule.h"
#include <sstream>

#include "date.h"
#include "http_requests.h"
#include "event.h"
#include "json_parser.h"

std::vector<Event> Schedule::GetToday(Group group) {
    // Create url
    std::stringstream ss;
    ss << "Week/GetWeek/"
       << Date::GetCurrentWeek()
       << "/"
       << group.GetId()
       << "/"
       << group.GetTypeId();

    HttpRequest::HttpResponse res = HttpRequest::MakeRequest(ss.str());
    return JsonHelpers::JsonToEvents(res.body);
}