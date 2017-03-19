#pragma  once

#include "display.h"

class LineDisplay : Display{
public:
    static void Print(std::vector<Event> events);
};