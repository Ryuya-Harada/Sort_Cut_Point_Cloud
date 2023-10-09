#pragma once
#ifndef _SCPC_HEADER_HPP
#define _SCPC_HEADER_HPP

#include "type.hpp"

namespace SCPC {
    class Header
    {
    private:
        std::string header;
        auto Header_Check() noexcept -> bool {
            for ( const auto& element : elements )
            {
                if ( element.element == ERRORE ) return false;
                if ( !Position_Check(element.types, element.element.type) ) return false;
            }
            return true;
        };
        auto Position_Check(const vecPD types, const ElementType e) noexcept -> bool {
            std::set<PropertyType> geometry;
            for ( const auto& [p, d] : types )
            {
                if ( p == ERRORP || d == ERRORD ) return false;
                if ( e != VERTEX ) continue;
                if ( p == X || p == Y || p == Z ) geometry.insert(p.type);
            }
            return e != VERTEX ? true : Check_Position(geometry);
        };
        bool Check_Position(const std::set<PropertyType>& geometry){
            return Check(geometry, X) && Check(geometry, Y) && Check(geometry, Z);
        };
        bool Check(const std::set<PropertyType>& geometry, const PropertyType& property){
            return geometry.find(property) != geometry.end();
        };
        auto Separate(const std::string& str) noexcept {
            std::stringstream ss(str);
            std::vector<std::string> vec;
            vec.reserve(12);
            std::string buf;
            while ( std::getline(ss, buf, ' ') )
                vec.push_back(buf);
            return vec;
        };
    public:
        Header(){}
        std::vector<Elements> elements;
        FormatType format;
        auto Read(const std::string& file) noexcept -> std::ifstream;
        void Write(const std::string& file, const bool& cut){
            std::ofstream ofs(file);
            ofs << header;
            for ( const auto& element : elements ){
                switch(element.element.type){
                    case VERTEX:    ofs << "element vertex " << element.num << std::endl;               break;
                    case FACE:      if ( !cut ) ofs << "element face " << element.num << std::endl;     break;
                    default:        break;
                };
                if ( element.element.type != VERTEX && cut ) continue;
                bool flag = true;
                for ( const auto& [p, d] : element.types )
                {
                    if ( p == LIST && flag ){
                        ofs << "property list " << d.str << " ";
                        flag = false;
                    }else if ( p == LIST && !flag ){
                        ofs << d.str << " vertex_indices\n";
                        flag = true;
                    }else if ( cut && p != X && p != Y && p != Z ) continue;
                    else ofs << "property " << d.str << " " << p.str << std::endl;
                }
            };
            ofs << "end_header\n";
        };
    };

    auto Header::Read(const std::string& file) noexcept -> std::ifstream {
        const std::string extension = file.substr(file.length() - 4);
        if ( extension != ".ply" ) Error_Message("Not Supported File");
        
        std::ifstream ifs;
        ifs.open(file, std::ios::in);
        if ( !ifs ) Error_Message("Not Found");

        std::string buff;
        std::getline(ifs, buff);
        std::stringstream ss;
        ss << buff << std::endl;
        if ( buff != "ply" ) Error_Message("No ply");
        std::getline(ifs, buff);
        ss << "format ascii 1.0\n";
        const auto format_buff = Separate(buff);
        if ( format_buff[0] != "format" ) Error_Message("No format");
        this->format = Format(format_buff[1]);
        if ( this->format == ERRORF ) Error_Message("Different Variations");
        if ( format_buff[2] != "1.0" ) Error_Message("Not Supported Version");
        ss << "comment created by Ryuya-Harada\n";
        this->header = ss.str();

        while ( std::getline(ifs, buff) )
        {
            if ( buff == "end_header" ) break;
            const auto str = Separate(buff);
            if ( str[0] == "comment" ) continue;
            else if ( str[0] == "element" ) this->elements.push_back(Elements(str[1], std::stoi(str[2])));
            else if ( str[0] == "property" ){
                const int num = this->elements.size() - 1;
                if ( num < 0 ) Error_Message("Not Supported Order");
                auto p = Type<PropertyType>(str[1], Property(str[1]));
                if ( p == LIST ){
                    for (int i = 2; i < 4; i++)
                        elements[num].types.push_back(std::make_pair(p, Type<DataType>(str[i], Data(str[i]))));
                }else elements[num].types.push_back(std::make_pair(Type<PropertyType>(str[2], Property(str[2])), Type<DataType>(str[1], Data(str[1]))));
            }
        }
        
        if ( this->elements.size() == 0 || !Header_Check() ) Error_Message("Not Supported Elements and Properties");
        
        if ( format != ASCII ){
            auto end_header = ifs.tellg();
            ifs.close();
            ifs.open (file, std::ios::in | std::ios::binary);
            ifs.seekg (end_header);
        }
        
        return ifs;
    };
};

#endif