#pragma once
#include "event.h"

class JsonHelpers {
public:
    static std::vector<Event> JsonToEvents(std::string json);
};