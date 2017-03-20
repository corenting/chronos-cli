#pragma once

#include <vector>
#include "models/group.h"
#include "models/event.h"

class Schedule {
public:
    static std::vector<Event> GetToday(Group group);
    static std::vector<Event> GetWeek(Group group);

    static std::vector<Event> GetNext(Group group);
};