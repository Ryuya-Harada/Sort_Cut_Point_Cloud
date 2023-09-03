#pragma once
#ifndef _SCPC_CONFIG_H
#define _SCPC_CONFIG_H

#include <string>
#include <vector>

namespace SCPC {
    class Config
    {
    public:
        std::vector<std::string> files;
        bool cut{false};
        bool sort{false};
        Config(const int& argc, char** argv) noexcept {
            for (int i = 0; i < argc; i++)
            {
                const std::string str = std::string(argv[i]);
                if ( str == "-i" && i < argc - 1 ) files.push_back(std::string(argv[i + 1]));
                else if ( str == "-c" ) cut = true;
                else if ( str == "-s" ) sort = true;
                else if ( str == "-h" || str == "--help" || str == "-?" ) Help();
            }
        };
        void Help(){
            printf("\n~~~~~ Help ~~~~~\n\n");
            printf("    -i  : path/to/input/file\n");
            printf("    -c  : cut attribute\n");
            printf("    -s  : sort coordinate and attribute\n");
            printf("    -h, --help, -?  : help\n\n");
        };
    };
    
};

#endif