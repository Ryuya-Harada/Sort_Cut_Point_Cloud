#pragma once
#ifndef _SCPC_CONST_HPP
#define _SCPC_CONST_HPP

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

namespace SCPC{
    using ull = unsigned long long;
    using lld = long double;
    using int8 = std::int8_t;
    using uint8 = std::uint8_t;
    using int16 = std::int16_t;
    using uint16 = std::uint16_t;
    using int32 = std::int32_t;
    using uint32 = std::uint32_t;
    using float32 = float;
    using float64 = double;

    inline void Error_Message(const std::string& str){
        std::cerr << str << std::endl;
        std::exit(EXIT_FAILURE);
    };

    inline auto Return_Null() noexcept {
        return std::to_string(0);
    };
};

#endif