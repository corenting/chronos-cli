#pragma once

#include "models/event.h"

class JsonHelpers {
public:
    static std::vector<Event> JsonToEvents(std::string json);
};