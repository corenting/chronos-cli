#include "schedule.h"
#include "http_requests.h"
#include "json_parser.h"
#include "date.h"

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

    if (res.error) {
        std::cout << "Error: cannot download timetable from Chronos" << std::endl;
        exit(1);
    }
    return JsonHelpers::JsonToEvents(res.body);
}