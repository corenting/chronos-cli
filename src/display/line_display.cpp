#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include "line_display.h"

void LineDisplay::print(std::vector<Event> events) {
    int latestDisplayedDay = -1;
    for (auto event : events) {
        if (event.GetStart().date().day_of_week() > latestDisplayedDay) {
            std::cout << std::endl << event.GetStart() << std::endl;
            latestDisplayedDay = event.GetStart().date().day_of_week();
        }
        std::cout << event.GetStart() << " - " << event.GetEnd() << " - "
                  << Display::truncateString(event.GetName(), 45);

        if (event.GetRoomsList().size() != 0 || event.GetTeachersList().size() != 0) {
            std::cout << " - ";
        }
        if (event.GetRoomsList().size() != 0) {
            std::cout << Display::truncateString(Display::GetListAsString(event.GetRoomsList()), 45);
            if (event.GetTeachersList().size() != 0) {
                std::cout << " - ";
            }
        }
        if (event.GetTeachersList().size() != 0) {
            std::cout << Display::truncateString(Display::GetListAsString(event.GetTeachersList()), 45);

        }
        std::cout << std::endl;
    }
}