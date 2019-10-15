#include "cmd.h"

// #define BOOST_TEST_MODULE subcommand options
#include <boost/program_options.hpp>
// #include <boost/test/unit_test.hpp>
#include <boost/variant/get.hpp>
#include <boost/variant/variant.hpp>

#include <iostream>
#include <string>

#include "lscmd.h"
#include "chmodcmd.h"

using namespace std;
CCmd* CCmd::CreateCommand(string t_subcmd)
{
    if (t_subcmd == "ls")
    {
        return new ClsCommand();
    }
    else if(t_subcmd == "chmod")
    {
        return new ChmodCommand();
    }
    else
    {
        cout << "Unknown subcommand: " << t_subcmd << endl; 
    }

    return nullptr;
}

// typedef boost::variant<LsCommand, ChmodCommand> Command;
// Command ParseOptions(int argc, const char *argv[]) {
//   namespace po = boost::program_options;
//   po::options_description global("Global options");
//   global.add_options()
//         ("help,h", "help message")
//         ("verbose,-v", "Turn on debug output")
//         ("command", po::value<std::string>(),"command to execute")
//         ("subargs", po::value<std::vector<std::string>>(), "Arguments for command");
//   po::positional_options_description pos;
//   pos.add("command", 1).add("subargs", -1);
//   po::variables_map vm;
//   po::parsed_options parsed = po::command_line_parser(argc, argv)
//                                   .options(global)
//                                   .positional(pos)
//                                   .allow_unregistered()
//                                   .run();
//   po::store(parsed, vm);
  
//   std::string cmd = vm["command"].as<std::string>();
//   if (cmd == "ls") {
//     // ls command has the following options:
//     po::options_description ls_desc("ls options");
//     ls_desc.add_options()
//         ("hidden", "Show hidden files")
//         ("path", po::value<std::string>(), "Path to list");
//     // Collect all the unrecognized options from the first pass. This will
//     // include the (positional) command name, so we need to erase that.
//     std::vector<std::string>::iterator itr;
//     std::vector<std::string> opts =
//         po::collect_unrecognized(parsed.options, po::include_positional);
//     std::cout << "before ..." << std::endl;
//     for (itr = opts.begin(); itr != opts.end(); itr++) {
//       std::cout << *itr << std::endl;
//     }
//     opts.erase(opts.begin());
//     // Parse again...
//     std::cout << "after ..." << std::endl;
//     for (itr = opts.begin(); itr != opts.end(); itr++) {
//       std::cout << *itr << std::endl;
//     }
//     try
//     {
//         po::store(po::command_line_parser(opts).options(ls_desc).run(), vm);
//     }
//     catch (po::unknown_option& e)
//     {
//         std::cout << e.what() << std::endl;
//     }
//     po::notify(vm);
//     LsCommand ls;
//     ls.debug_ = vm.count("debug");
//     ls.hidden_ = vm.count("hidden");
//     ls.path_ = vm["path"].as<std::string>();
//     return ls;
//   } else if (cmd == "chmod") {
//     // Something similar
//   }
//   // unrecognised command
//   throw po::invalid_option_value(cmd);
// }
// BOOST_AUTO_TEST_CASE(NoCommand) {
//   const int argc = 2;
//   const char *argv[argc] = {"0", "nocommand"};
//   BOOST_CHECK_THROW(ParseOptions(argc, argv),
//                     boost::program_options::invalid_option_value);
// }
// BOOST_AUTO_TEST_CASE(LsTest) {
//   const int argc = 5;
//   const char *argv[argc] = {"0", "--debug", "ls", "--hidden", "--path=./"};
//   Command c = ParseOptions(argc, argv);
//   BOOST_REQUIRE(boost::get<LsCommand>(&c));
//   const LsCommand &ls = boost::get<LsCommand>(c);
//   BOOST_CHECK(ls.debug_);
//   BOOST_CHECK(ls.hidden_);
//   BOOST_CHECK_EQUAL(ls.path_, "./");
// }
