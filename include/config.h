#pragma once
#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>

namespace sort_ply{
    class Config
    {
    public:
        std::string file{"sorted.ply"};
        std::string attr{"none"};
        Config(const int& argc, const char** argv) noexcept {
            for (int i = 0; i < argc; i++)
            {
                const std::string str = std::string(argv[i]);
                if ( str.substr(0, 2) == "-i" ) file = str.substr(str.find("=") + 1);
                else if ( str.substr(0, 2) == "-a" ) attr = str.substr(str.find("=") + 1);
            }
        };
    };
    
};

#endif