#include <iostream>
#include "line_display.h"

void LineDisplay::print(std::vector<Event> events) {
    for (auto event : events)
    {
        std::cout << event.GetName() << std::endl;
    }
}
