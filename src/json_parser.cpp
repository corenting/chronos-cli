#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time_adjustor.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include "libs/json.hpp"
#include "json_parser.h"
#include "date.h"

using json = nlohmann::json;

std::vector<Event> JsonHelpers::JsonToEvents(std::string jsonString) {
    std::vector<Event> events;
    json parsedJson = json::parse(jsonString);
    typedef boost::date_time::c_local_adjustor<boost::posix_time::ptime> local_adj;


    //Days
    for (auto day : parsedJson["DayList"]) {
        //Events
        for (auto event: day["CourseList"]) {
            // Dates
            boost::posix_time::ptime start = Date::DateFromIsoString(event["BeginDate"].get<std::string>());
            boost::posix_time::ptime end = Date::DateFromIsoString(event["EndDate"].get<std::string>());
            start = local_adj::utc_to_local(start);
            end = local_adj::utc_to_local(end);

            std::string name = boost::trim_copy(event["Name"].get<std::string>());

            std::vector<std::string> teachers;
            for (auto teacher: event["StaffList"]) {
                std::string teacherName = teacher["Name"].get<std::string>();
                boost::trim(teacherName);
                teachers.push_back(teacherName);
            }

            std::vector<std::string> rooms;
            for (auto room: event["RoomList"]) {
                std::string roomName = boost::trim_copy(room["Name"].get<std::string>());
                rooms.push_back(roomName);
            }

            std::vector<std::string> groups;
            for (auto group: event["GroupList"]) {
                std::string groupName = boost::trim_copy(group["Name"].get<std::string>());
                groups.push_back(groupName);
            }
            events.emplace_back(start, end, name, groups, teachers, rooms);
        }
    }

    return events;
}
