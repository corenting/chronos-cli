#pragma  once

#include "display.h"

class LineDisplay : Display{
public:
    static void print(std::vector<Event> events);
};