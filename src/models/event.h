#pragma once

#include "boost/date_time/posix_time/posix_time.hpp"
#include <vector>

class Event {
public:
    Event(boost::posix_time::ptime start, boost::posix_time::ptime end, std::string name,
          std::vector<std::string> groups, std::vector<std::string> teachers, std::vector<std::string> rooms);

    boost::posix_time::ptime GetStart();

    boost::posix_time::ptime GetEnd();

    std::string GetName();

    std::vector<std::string> GetGroupsList();

    std::vector<std::string> GetRoomsList();

    std::vector<std::string> GetTeachersList();

private:
    boost::posix_time::ptime start;
    boost::posix_time::ptime end;
    std::string name;
    std::vector<std::string> groups;
    std::vector<std::string> teachers;
    std::vector<std::string> rooms;
};