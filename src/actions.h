#pragma once
#include <string>


class Actions {
public:
    enum ScheduleActions {
        Today,
        Week,
    };
    static ScheduleActions  GetAction(std::string action);
};
