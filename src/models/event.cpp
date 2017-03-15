#include "boost/date_time/posix_time/posix_time.hpp"
#include "event.h"

Event::Event(boost::posix_time::ptime start, boost::posix_time::ptime end, std::string name,
             std::vector<std::string> groups, std::vector<std::string> teachers, std::vector<std::string> rooms)
        : start(start), end(end), name(name), groups(groups), teachers(teachers), rooms(rooms) {}

boost::posix_time::ptime Event::GetStart() {
    return start;
}

boost::posix_time::ptime Event::GetEnd() {
    return end;
}

std::string Event::GetName() {
    return name;
}

std::vector<std::string> Event::GetGroupsList() {
    return groups;
}

std::vector<std::string> Event::GetTeachersList() {
    return teachers;
}

std::vector<std::string> Event::GetRoomsList() {
    return rooms;
}