//
// Created by robin on 8/8/15.
//

#include <iostream>
#include <sysexits.h>
#include "CommandLineParser.h"
#include "MainClass.h"

MainClass::MainClass(int argc, char *argv[])
    : _argc(argc)
    , _argv(argv)
{
}

int MainClass::main()
{
    CommandLineOption configFile("config", 'c', "Path to the configuration file",
                                 "FILE", "/etc/pdns-slave/pdns-slave.json");
    CommandLineOption help("help", 'h', "Displays this help", "", "");
    CommandLineParser parser(_argc, _argv);
    parser.addOption(&help);
    parser.addOption(&configFile);
    if (!parser.parse())
        return parser.showHelp(EX_USAGE);
    if (help.isSet())
        return parser.showHelp(0, false);

    auto file = configFile.getValue();
    std::cout << "Using configuration file " << file << std::endl;

    return 0;
}
