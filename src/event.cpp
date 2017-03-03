#include "event.h"

Event::Event(boost::gregorian::date start, boost::gregorian::date end, std::string name,
             std::vector<std::string> groups, std::vector<std::string> teachers, std::vector<std::string> rooms)
        : start(start), end(end), name(name), groups(groups), teachers(teachers), rooms(rooms) {}

boost::gregorian::date Event::GetStart() {
    return start;
}

boost::gregorian::date Event::GetEnd() {
    return end;
}

std::string Event::GetName() {
    return name;
}

std::vector<std::string> Event::GetGroups() {
    return groups;
}

std::vector<std::string> Event::GetTeachers() {
    return teachers;
}
