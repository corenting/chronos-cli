#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include "libs/json.hpp"
#include "json_parser.h"
#include "date.h"

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
            boost::posix_time::ptime end = Date::DateFromIsoString(event["EndDate"].get<std::string>());
            std::string name = event["Name"].get<std::string>();
            boost::trim(name);

            std::vector<std::string> teachers;
            for (auto teacher: event["StaffList"])
            {
                std::string teacherName = teacher["Name"].get<std::string>();
                boost::trim(teacherName);
                teachers.push_back(teacherName);
            }

            std::vector<std::string> rooms;
            for (auto room: event["RoomList"])
            {
                std::string roomName = room["Name"].get<std::string>();
                boost::trim(roomName);
                rooms.push_back(roomName);
            }

            std::vector<std::string> groups;
            for (auto group: event["GroupList"])
            {
                std::string groupName = group["Name"].get<std::string>();
                boost::trim(groupName);
                groups.push_back(groupName);
            }
            events.emplace_back(start, end, name, groups, teachers, rooms);
        }
    }

    return events;
}
