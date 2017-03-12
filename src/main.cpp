#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>

#include "schedule.h"
#include "actions.h"
#include "display/line_display.h"

namespace po = boost::program_options;

po::variables_map getSettings(int argc, char *argv[])
{
    // Visible options
    po::options_description visibleOptions("Options");
    visibleOptions.add_options()
            ("help,h", "display help")
            ("group,g", "set the group used for the request");

    // Hidden option (to specify action)
    po::options_description HiddenOptions("Hidden options");
    HiddenOptions.add_options()
            ("action", po::value<std::string>(), "action");

    // Create cli options from visible and hidden options
    po::options_description cliOptions;
    cliOptions.add(visibleOptions).add(HiddenOptions);

    // Config file options
    po::options_description configOptions("Config file options");
    configOptions.add_options()
            ("api_token", "The token for the API");

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
    fileOptions.add(configOptions);
    std::string configPath;
    configPath += getenv("HOME");
    configPath += "/.chronosrc";
    std::ifstream ifs(configPath.c_str());
    if (!ifs)
    {
        std::cout << "Error: cannot open config file " << configPath << std::endl;
        exit(1);
    }
    else {
        store(po::parse_config_file(ifs, fileOptions), settings);
        notify(settings);
    }

    // Display help
    if (settings.count("help") || argc == 1) {
        std::cout << visibleOptions << "\n";
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
    catch(int e)
    {
        std::cout << "Error " << e << ": config parsing error" << std::endl;
        exit(1);
    }

    // Check for mandatory settings
    if (settings.count("action") != 1) {
        std::cout << "Error: you need to specify an action";
    }
    if (settings.count("api_token") != 1) {
        std::cout << "Error: you need to specify an api token in your config file";
    }

    // Get action and call the correct function
    Actions::ScheduleActions action = Actions::GetAction(settings["action"].as<std::string>());
    if (action == Actions::ScheduleActions::Today)
    {
        Group g(973, 14, "ING1/GRB1", 1);
        std::vector<Event> schedule = Schedule::GetToday(g, settings["api_token"].as<std::string>());
        LineDisplay::print(schedule);
    }
    return 0;
}