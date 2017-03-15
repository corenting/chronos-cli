#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>

#include "schedule.h"
#include "actions.h"
#include "group_cache.h"
#include "display/line_display.h"

namespace po = boost::program_options;

po::variables_map getSettings(int argc, char *argv[]) {
    // Visible options
    po::options_description visibleOptions("Command line options");
    visibleOptions.add_options()
            ("help,h", "display help")
            ("renew-cache,rc", "renew group cache");;

    // Hidden option (to specify action)
    po::options_description HiddenOptions("Hidden options");
    HiddenOptions.add_options()
            ("action", po::value<std::string>(), "action");

    // Common options (cli + config file)
    po::options_description commonOptions("Command line or config file options");
    commonOptions.add_options()
            ("output,o", po::value<std::string>(), "display help")
            ("group,g", po::value<std::string>(), "set the group used for the request");

    // Create cli options from visible and hidden options
    po::options_description cliOptions;
    cliOptions.add(commonOptions).add(visibleOptions).add(HiddenOptions);


    // Set action as a positional argument
    po::positional_options_description op;
    op.add("action", -1);

    // Create settings map
    po::variables_map settings;
    po::store(po::command_line_parser(argc, argv).
            options(cliOptions).positional(op).run(), settings);
    po::notify(settings);

    // Config file parsing
    po::options_description fileOptions;
    fileOptions.add(commonOptions);
    std::string configPath;
    configPath += getenv("HOME");
    configPath += "/.chronosrc";
    std::ifstream ifs(configPath.c_str());
    if (!ifs) {
        std::cout << "Error: cannot open config file " << configPath << std::endl;
        exit(1);
    } else {
        store(po::parse_config_file(ifs, fileOptions), settings);
        notify(settings);
    }

    // Display help
    if (settings.count("help") || argc == 1) {
        std::cout << commonOptions;
        std::cout << visibleOptions << std::endl;
        exit(1);
    }
    return settings;
}

int main(int argc, char *argv[]) {

    // Get settings
    po::variables_map settings;
    try {
        settings = getSettings(argc, argv);
    }
    catch (int e) {
        std::cout << "Error " << e << ": config parsing error" << std::endl;
        exit(1);
    }

    // Check for mandatory settings
    if (settings.count("action") != 1) {
        std::cout << "Error: you need to specify an action";
    }
    if (settings.count("group") != 1) {
        std::cout << "Error: you need to specify a group in your config file or as an argument";
    }

    // Check if need to renew cache
    if (settings.count("renew-cache")) {
        GroupCache::renewCache();
    }

    std::vector<Group> groupsList = GroupCache::getGroupCache();

    // Get action and call the correct function
    Actions::ScheduleActions action = Actions::GetAction(settings["action"].as<std::string>());
    if (action == Actions::ScheduleActions::Today) {
        Group g = GroupCache::getGroupFromName(settings["group"].as<std::string>(), groupsList);
        std::vector<Event> schedule = Schedule::GetToday(g);
        LineDisplay::print(schedule);
    }
    return 0;
}