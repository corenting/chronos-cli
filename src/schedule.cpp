#include "schedule.h"
#include "http_requests.h"
#include "json_parser.h"
#include "date.h"

std::vector<Event> Schedule::GetToday(Group group) {
    std::vector<Event> events = GetCurrentWeek(group);
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

std::vector<Event> Schedule::GetCurrentWeek(Group group) {
    // Create url
    std::stringstream ss;
    ss << "Week/GetCurrentWeek/"
       << group.GetId()
       << "/"
       << group.GetTypeId();

    HttpRequest::HttpResponse res = HttpRequest::MakeRequest(ss.str());

    if (res.error) {
        std::cout << "Error: cannot download timetable from Chronos" << std::endl;
        exit(1);
    }
    std::vector<Event> vec = JsonHelpers::JsonToEvents(res.body);
    if (vec.size() <= 0)
    {
        std::cout << "Nothing for this week";
        exit(0);
    }
    return vec;
}

std::vector<Event> Schedule::GetNext(Group group) {
    std::vector<Event> events = GetCurrentWeek(group);
    events.erase(
            std::remove_if(
                    events.begin(), events.end(),
                    [](Event evt) {
                        boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
                        return evt.GetStart() < now;
                    }),
            events.end());

    if (events.size() <= 0)
        return std::vector<Event>();
    std::vector<Event> subVector(events.begin(), events.begin() + 1);
    return subVector;
}
