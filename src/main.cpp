#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>

#include "schedule.h"
#include "actions.h"
#include "group_cache.h"
#include "display/line_display.h"

namespace po = boost::program_options;

po::variables_map GetSettings(int argc, char **argv) {
    // Visible options
    po::options_description visibleOptions("Command line options");
    visibleOptions.add_options()
            ("help,h", "display help")
            ("renew-cache,rc", "renew group cache");;

    // Hidden option (to specify action)
    po::options_description hiddenOptions(
            "Action option (can also be specified without -a / --action, like 'chronos_cli today')");
    hiddenOptions.add_options()
            ("action,a", po::value<std::string>()->default_value("week"), "what will be displayed (next, week...)");

    // Common options (cli + config file)
    po::options_description commonOptions("Command line or config file options");
    commonOptions.add_options()
            ("output,o", po::value<std::string>()->default_value("line"), "display help")
            ("blacklist,b", po::value<std::string>(), "blacklisted courses")
            ("group,g", po::value<std::string>(), "set the group used for the request");

    // Create cli options from visible and hidden options
    po::options_description cliOptions;
    cliOptions.add(commonOptions).add(visibleOptions).add(hiddenOptions);

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
    if (ifs) {
        store(po::parse_config_file(ifs, fileOptions), settings);
        notify(settings);
    }

    // Display help
    if (settings.count("help") || argc == 1) {
        std::cout << hiddenOptions << std::endl
                  << commonOptions << std::endl
                  << visibleOptions << std::endl;
        exit(1);
    }
    return settings;
}

int main(int argc, char *argv[]) {

    // Get settings
    po::variables_map settings;
    try {
        settings = GetSettings(argc, argv);
    }
    catch (po::error &e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }

    // Check for mandatory setting
    if (settings.count("group") != 1) {
        std::cout << "Error: you need to specify a group in your config file or as an argument";
    }

    // Check if need to renew cache
    if (settings.count("renew-cache")) {
        GroupCache::RenewCache();
    }

    std::vector<Group> groupsList = GroupCache::GetGroupCache();

    // Get action and call the correct function
    Actions::ScheduleActions action = Actions::GetAction(settings["action"].as<std::string>());
    Group g = GroupCache::GetGroupName(settings["group"].as<std::string>(), groupsList);
    std::vector<Event> schedule;
    if (action == Actions::ScheduleActions::Today) {
        schedule = Schedule::GetToday(g);
    } else if (action == Actions::ScheduleActions::Week) {
        schedule = Schedule::GetCurrentWeek(g);
    } else if (action == Actions::ScheduleActions::Next) {
        schedule = Schedule::GetNext(g);
    }

    // Remove the blacklist courses
    if (settings.count("blacklist")) {
        Schedule::RemoveBlacklisted(schedule, settings["blacklist"].as<std::string>());
    }

    // Print according to the given printer
    Display::OutputSystems outputSystem = Display::GetOutput(settings["output"].as<std::string>());
    if (outputSystem == Display::OutputSystems::Line) {
        LineDisplay::Print(schedule);
    }
    /*else if (outputSystem == Display::OutputSystems::Ascii)
    {
        AsciiDisplay::Print(schedule);
    }*/
    return 0;
}