//
// Created by robin on 8/8/15.
//

#include <iostream>
#include <sysexits.h>
#include <DBO/Result.h>
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
    CommandLineOption check("check", 'C', "Only check configurations", "", "");
    CommandLineOption help("help", 'h', "Displays this help", "", "");
    CommandLineParser parser(_argc, _argv);
    parser.addOption(&help);
    parser.addOption(&configFile);
    parser.addOption(&check);
    if (!parser.parse())
        return parser.showHelp(EX_USAGE);
    if (help.isSet())
        return parser.showHelp(0, false);

    auto filePath = configFile.getValue();
    std::cout << "Using configuration file " << filePath << std::endl;

    PdnsSlave pdnsSlave(filePath);
    BResult res;
    Result<Actions> res2;

    std::cout << "Reading pdns-slave configuration" << std::endl;
    if (!(res = pdnsSlave.readConfig()))
    {
        std::cerr << "Failed to read pdns-slave configuration" << std::endl;
        res.print();
        return 1;
    }
    res.print();

    std::cout << "Reading dhcpd template" << std::endl;
    if (!(res = pdnsSlave.readDhcpdTemplate()))
    {
        std::cerr << "Failed to read dhcpd template" << std::endl;
        res.print();
        return 2;
    }
    res.print();

    std::cout << "Reading hosts configuration" << std::endl;
    if (!(res2 = pdnsSlave.readHosts()))
    {
        std::cerr << "Failed to read hosts configuration" << std::endl;
        res2.print();
        return 3;
    }
    res2.print();

    if (!check.isSet())
    {
        std::cout << "Overriding dns" << std::endl;
        if (!(res = pdnsSlave.overridePdns()))
        {
            std::cerr << "Failed to override dns" << std::endl;
            res.print();
            return 4;
        }
        res.print();

        std::cout << "Overriding dhcp" << std::endl;
        if (!(res = pdnsSlave.overrideDhcp()))
        {
            std::cerr << "Failed to override dhcp" << std::endl;
            res.print();
            return 5;
        }
        res.print();
    }

    return 0;
}
