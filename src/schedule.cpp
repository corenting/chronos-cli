#include <algorithm>
#include<boost/tokenizer.hpp>

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

    cpr::Response res = HttpRequest::MakeRequest(ss.str());

    if (res.status_code != 200) {
        std::cout << "Error: cannot download timetable from Chronos" << std::endl;
        exit(1);
    }
    std::vector<Event> vec = JsonHelpers::JsonToEvents(res.text);
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

void Schedule::RemoveBlacklisted(std::vector<Event>& schedule, std::string blacklist) {
    typedef boost::tokenizer<boost::char_separator<char>>  tokenizer;
    boost::char_separator<char> char_separator(";");
    tokenizer tokens(blacklist, char_separator);
    schedule.erase(
        std::remove_if(
            schedule.begin(), schedule.end(),
                [&tokens](Event evt) {
                    return std::find(tokens.begin(), tokens.end(), evt.GetName()) != tokens.end();
                }),
            schedule.end());
}
