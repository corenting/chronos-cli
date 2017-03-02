#pragma once
#include <string>


class Actions {
public:
    enum ScheduleActions {
        Today,
    };
    static ScheduleActions  GetAction(std::string action);
};
