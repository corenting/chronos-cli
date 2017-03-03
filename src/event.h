#pragma once

#include <boost/date_time/gregorian/greg_date.hpp>
#include <vector>

class Event {
public:
    Event(boost::gregorian::date start, boost::gregorian::date end, std::string name,
              std::vector<std::string> groups, std::vector<std::string> teachers, std::vector<std::string> rooms);
    boost::gregorian::date GetStart();
    boost::gregorian::date GetEnd();
    std::string GetName();
    std::vector<std::string> GetGroups();
    std::vector<std::string> GetTeachers();
private:
    boost::gregorian::date start;
    boost::gregorian::date end;
    std::string name;
    std::vector<std::string> groups;
    std::vector<std::string> teachers;
    std::vector<std::string> rooms;
};