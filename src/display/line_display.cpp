#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "line_display.h"

void LineDisplay::Print(std::vector<Event> events) {
    int latestDisplayedDay = -1;
    bool first = true;
    for (auto event : events) {

        if (event.GetStart().date().day_of_week() > latestDisplayedDay) {
            // Facet for date display
            boost::posix_time::time_facet *dateFacet(new boost::posix_time::time_facet("%a %d %b %Y"));
            std::cout.imbue(std::locale(std::cout.getloc(), dateFacet));

            if (first) {
                first = false;
            }
            else {
                std::cout << std::endl;
            }
            std::cout << event.GetStart() << std::endl;
            latestDisplayedDay = event.GetStart().date().day_of_week();

            //Facet for time display
            boost::posix_time::time_facet *timeFacet(new boost::posix_time::time_facet("%H:%M"));
            std::cout.imbue(std::locale(std::cout.getloc(), timeFacet));
        }
        std::cout << event.GetStart() << " - " << event.GetEnd() << " - "
                  << Display::TruncateString(event.GetName(), 45);

        if (event.GetRoomsList().size() != 0 || event.GetTeachersList().size() != 0) {
            std::cout << " - ";
        }
        if (event.GetRoomsList().size() != 0) {
            std::cout << Display::TruncateString(Display::GetListAsString(event.GetRoomsList()), 45);
            if (event.GetTeachersList().size() != 0) {
                std::cout << " - ";
            }
        }
        if (event.GetTeachersList().size() != 0) {
            std::cout << Display::TruncateString(Display::GetListAsString(event.GetTeachersList()), 45);

        }
        std::cout << std::endl;
    }
}