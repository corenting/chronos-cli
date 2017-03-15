#include "schedule.h"
#include "http_requests.h"
#include "json_parser.h"
#include "date.h"

std::vector<Event> Schedule::GetToday(Group group) {
    std::vector<Event> events = GetWeek(group);
    events.erase(
            std::remove_if(
                    events.begin(), events.end(),
                    [](Event evt) {
                        boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
                        return evt.GetStart().date().day_of_week() != now.date().day_of_week();
                    }),
            events.end());
    return events;
}

std::vector<Event> Schedule::GetWeek(Group group) {
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