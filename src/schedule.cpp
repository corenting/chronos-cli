#include "schedule.h"
#include "http_requests.h"
#include "json_parser.h"
#include "date.h"

std::vector<Event> Schedule::GetToday(Group group, std::string api_token) {
    // Create url
    std::stringstream ss;
    ss << "Week/GetWeek/"
       << Date::GetCurrentWeek()
       << "/"
       << group.GetId()
       << "/"
       << group.GetTypeId();

    HttpRequest::HttpResponse res = HttpRequest::MakeRequest(ss.str(), api_token);
    return JsonHelpers::JsonToEvents(res.body);
}