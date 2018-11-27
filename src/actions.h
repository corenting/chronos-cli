#pragma once

#include <string>


class Actions {
public:
    enum ScheduleActions {
        Today,
        Next,
        Week,
    };

    static ScheduleActions GetAction(std::string action);
};
