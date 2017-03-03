#pragma once

#include <vector>
#include "group.h"
#include "event.h"

class Schedule {
public:
    static std::vector<Event> GetToday(Group group);
};