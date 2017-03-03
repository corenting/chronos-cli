#include <iostream>
#include <boost/program_options.hpp>

#include "schedule.h"
#include "actions.h"
#include "display/line_display.h"

namespace po = boost::program_options;

int main(int argc, char *argv[]) {

    // Add visibles options
    po::options_description desc("Options");
    desc.add_options()
            ("help,h", "display help")
            ("group,g", "set the group used for the request");

    // Add hidden options (to specify action)
    po::options_description hidden("Hidden options");
    hidden.add_options()
            ("action", po::value<std::string>(), "action");

    // Set operation as positional arg
    po::positional_options_description op;
    op.add("action", -1);

    // Set args and parse them
    po::options_description cmdline_options;
    cmdline_options.add(desc).add(hidden);
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
            options(cmdline_options).positional(op).run(), vm);
    po::notify(vm);

    // Display help
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if (vm.count("action") != 1) {
        std::cout << "Error : you need to specify an action";
    }

    // Get action and call the correct function
    Actions::ScheduleActions action = Actions::GetAction(vm["action"].as<std::string>());
    if (action == Actions::ScheduleActions::Today)
    {
        Group g(973, 14, "ING1/GRB1", 1);
        std::vector<Event> schedule = Schedule::GetToday(g);
        LineDisplay::print(schedule);
    }
    return 0;
}