#include "actions.h"

Actions::ScheduleActions Actions::GetAction(std::string action) {
    if (action == "today")
        return Actions::ScheduleActions::Today;
}
