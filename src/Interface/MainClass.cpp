//
// Created by robin on 8/8/15.
//

#include <iostream>
#include <sysexits.h>
#include "CommandLineParser.h"
#include "Business/PdnsSlave.h"
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

    auto filePath = configFile.getValue();
    std::cout << "Using configuration file " << filePath << std::endl;

    PdnsSlave pdnsSlave(filePath);
    if (!pdnsSlave.readConfig())
    {
        std::cerr << "Failed to read pdns-slave configuration" << std::endl;
        return 1;
    }
    if (!pdnsSlave.readDhcpdTemplate())
    {
        std::cerr << "Failed to read dhcpd template" << std::endl;
        return 2;
    }

    return 0;
}
