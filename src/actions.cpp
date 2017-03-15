#include <iostream>
#include "actions.h"

Actions::ScheduleActions Actions::GetAction(std::string action) {
    if (action == "today")
        return Actions::ScheduleActions::Today;
    if (action == "week")
        return Actions::ScheduleActions::Week;
    std::cout << "Error: action " << action << " is not supported" << std::endl;
    exit(1);
}
