#pragma once
#ifndef _SCPC_VERTEX_HPP
#define _SCPC_VERTEX_HPP

#include "type.hpp"
#include "ioput.hpp"

namespace SCPC {
    template<class T>
    class Vertex
    {
    private:
        std::vector<T> points;
        Elements element;
        FormatType format;
        auto Point(std::ifstream& ifs){
            auto point = T();
            for ( const auto& [p, d] : element.types )
                point.Input(p.type, Data_type_input(d.type, format, ifs));
            return point;
        };
    public:
        Vertex(const Elements& element_, const FormatType& format_) : element(element_), format(format_) {}
        void Read(std::ifstream& ifs){
            this->points.reserve(element.num);
            for (int i = 0; i < element.num; i++)
                this->points.push_back(Point(ifs));
        };
        void Sort(){
            std::sort(points.begin(), points.end(), [](const T& a, const T& b){
                return a.geom < b.geom;
            });
        };
        void Cut(){
            const vecPD vec = element.types;
            element.types.clear();
            for (const auto& [p, d] : vec)
                if ( p == X || p == Y || p == Z ) element.types.push_back(std::make_pair(p, d));
        };
        void Write(const std::string file){
            std::ofstream ofs;
            ofs.open(file, std::ios::app);
            ofs.rdbuf()->pubsetbuf(nullptr, 0);
            for ( const auto& point : points )
            {
                std::stringstream ss;
                for ( const auto& [p, d] : element.types )
                    ss << point.Output(p.type) << " ";
                ofs << ss.str() << std::endl;
            }
            ofs.close();
        };
    };

    class Decide_Point_Type {
        public:
        bool def{false};
        DataType geometry{ERRORD};
        DataType attribute{ERRORD};
        DataType normal{ERRORD};
        bool alpha{false};
        Decide_Point_Type(const vecPD& types){
            if ( Check_DataType(types, X, Y) && Check_DataType(types, X, Z) ) geometry = Check_Exist(types, X);
            if ( Check_DataType(types, R, G) && Check_DataType(types, R, B) ) attribute = Check_Exist(types, R);
            if ( Check_DataType(types, NX, NY) && Check_DataType(types, NX, NZ) ) normal = Check_Exist(types, NX);
            if ( Check_DataType(types, R, A) ) alpha = true;

            if ( geometry == ERRORD ) Error_Message("Mismatch : Geometry Data Type");
            if ( Check_Exist(types, R) != ERRORD && attribute == ERRORD ) Error_Message("Mismatch : Attribute Data Type");
            if ( Check_Exist(types, NX) != ERRORD && normal == ERRORD ) Error_Message("Mismatch : Normal Data Type");
            if ( Check_Exist(types, A) != ERRORD && !alpha ) Error_Message("Mismatch : Alpha Data Type");

            if ( Check_Default(types) ) def = true;
        };
        auto XYZRGB(){ return attribute != ERRORD; };
        auto XYZRGBN(){ return XYZRGB() && normal != ERRORD; };
        auto XYZRGBNA(){ return XYZRGBN() && alpha; };
        private:
        auto Check_Exist(const vecPD& types, const PropertyType& property) noexcept -> DataType {
            for (const auto& [p, d] : types)
                if ( p == property ) return d.type;
            return ERRORD;
        };
        auto Check_DataType(const vecPD& types, const PropertyType& p1, const PropertyType& p2) noexcept -> bool {
            const auto d1 = Check_Exist(types, p1);
            const auto d2 = Check_Exist(types, p2);
            return d1 != ERRORD && d2 != ERRORD && d1 == d2;
        };
        auto Check_Default(const vecPD& types) noexcept -> bool {
            for (const auto& [p, d] : types)
                if ( !Check_Com(p.type, d.type) ) return false;
            return true;
        };
        auto Check_Com(const PropertyType& p, const DataType& d) noexcept -> bool {
            switch(p)
            {
                case X:     return d == FLOAT32 ? true : false; break;
                case Y:     return d == FLOAT32 ? true : false; break;
                case Z:     return d == FLOAT32 ? true : false; break;
                case NX:    return d == FLOAT32 ? true : false; break;
                case NY:    return d == FLOAT32 ? true : false; break;
                case NZ:    return d == FLOAT32 ? true : false; break;
                case R:     return d == UINT8   ? true : false; break;
                case G:     return d == UINT8   ? true : false; break;
                case B:     return d == UINT8   ? true : false; break;
                case A:     return d == UINT8   ? true : false; break;
                default:    return false;                       break;
            };
        };
    };
    
};

#endif