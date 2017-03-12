#include "boost/date_time/posix_time/posix_time.hpp"
#include "libs/json.hpp"
#include "json_parser.h"
#include "date.h"
#include "models/event.h"

using json = nlohmann::json;

std::vector<Event> JsonHelpers::JsonToEvents(std::string jsonString) {
    std::vector<Event> events;
    json parsedJson = json::parse(jsonString);

    //Days
    for (auto day : parsedJson["DayList"])
    {
        //Events
        for (auto event: day["CourseList"])
        {
            boost::posix_time::ptime start = Date::DateFromIsoString(event["BeginDate"].get<std::string>());
            boost::posix_time::ptime end = Date::DateFromIsoString(event["BeginDate"].get<std::string>());
            std::string name = event["Name"].get<std::string>();

            std::vector<std::string> teachers;
            for (auto room: event["StaffList"])
            {
                teachers.push_back(room["Name"].get<std::string>());
            }

            std::vector<std::string> rooms;
            for (auto room: event["RoomList"])
            {
                rooms.push_back(room["Name"].get<std::string>());
            }

            std::vector<std::string> groups;
            for (auto room: event["GroupList"])
            {
                groups.push_back(room["Name"].get<std::string>());
            }
            events.emplace_back(start, end, name, groups, teachers, rooms);
        }
    }

    return events;
}
