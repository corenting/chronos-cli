#include <iostream>
#include <string>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

int main(int argc, char *argv[]) {

    // Add visibles options
    po::options_description desc("Options");
    desc.add_options()
            ("help,h", "display help");

    // Add hidden options (to specify current operation)
    po::options_description hidden("Hidden options");
    hidden.add_options()
            ("operation", po::value<std::string>(), "operation");

    // Set operation as positional arg
    po::positional_options_description op;
    op.add("operation", -1);

    // Set args and parse them
    po::options_description cmdline_options;
    cmdline_options.add(desc).add(hidden);
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
                    options(cmdline_options).positional(op).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }
    
    return 0;
}