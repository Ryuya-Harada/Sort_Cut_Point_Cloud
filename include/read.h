#pragma once
#ifndef _SCPC_READ_H
#define _SCPC_READ_H

#include "ply.h"
#include "point_type.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

namespace SCPC {
    inline auto Separate(const std::string& str) noexcept {
        std::stringstream ss(str);
        std::vector<std::string> vec;
        vec.reserve(6);
        std::string buf;
        while ( std::getline(ss, buf, ' ') )
        {
            buf.erase(std::remove_if(buf.begin(), buf.end(), ispunct), buf.end());
            vec.push_back(buf);
        }
        return vec;
    };

    auto PolygonFileFormat::Read_header() noexcept -> std::ifstream {
        const std::string extension = file.substr(file.length() - 4);
        if ( extension != ".ply" ) std::logic_error("Not Supported File\n\n");
        
        std::ifstream ifs;
        ifs.open(file, std::ios::in);
        if ( !ifs ) std::logic_error("Not Found\n\n");

        std::string buff;
        std::getline(ifs, buff);
        std::stringstream ss;
        ss << buff << "\n";
        if ( buff != "ply" ) std::logic_error("No ply\n\n");
        std::getline(ifs, buff);
        ss << buff << "\n";
        const auto format_buff = Separate(buff);
        if ( format_buff[0] != "format" ) std::logic_error("No format\n\n");
        if ( format_buff[1] != "ascii"
         && format_buff[1] != "binary_little_endian"
         && format_buff[1] != "binary_big_endian" ) std::logic_error("Different Variations\n\n");
        if ( format_buff[2] != "1.0" ) std::logic_error("Not Supported Version\n\n");
        const auto format = format_buff[1] == "ascii" ? true : false;
        
        ss << "comment created by Ryuya-Harada\n";
        this->header = ss.str();
        std::vector<std::pair<GeomAttr, PropertyType>> prop;
        prop.reserve(6);
        while ( std::getline(ifs, buff) )
        {
            if ( buff == "end_header" ) break;
            const auto str = Separate(buff);
            if ( str[0] == "comment" ) continue;
            else if ( str[0] == "element" ){
                if ( str[1] != "vertex" ) std::logic_error("Not Supported Style\n\n");
                this->element = std::stoi(str[2]);
            }else if ( str[0] == "property" ){
                if ( str[1] == "list" ) std::logic_error("Not Supported Style\n\n");
                prop.push_back(std::make_pair(In_Geom_Attr(str[2]), In_Property(str[1])));
            }
        }

        if ( this->element != 0 || !this->Property_Check(prop) ) std::logic_error("No Element and Property\n\n");
        
        if ( !format ){
            auto end_header = ifs.tellg();
            ifs.close();
            ifs.open (file, std::ios::in | std::ios::binary);
            ifs.seekg (end_header);
        }
        return ifs;
    };

    inline auto Convert(const std::string& str){
        return std::stold(str);
    };

    void PolygonFileFormat::Read_data(std::ifstream& ifs){
        std::string buff;
        this->points.reserve(element);
        bool flag = true;
        while ( std::getline(ifs, buff) )
        {
            const auto str = Separate(buff);
            auto point = XYZRGB<long double, long double>(Convert(str[0]), Convert(str[1]), Convert(str[2]), Convert(str[3]), Convert(str[4]), Convert(str[5]));
            points.push_back(point);
        }
        ifs.close();
    };
};

#endif