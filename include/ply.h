#pragma once
#ifndef _PLY_H
#define _PLY_H

#include "point_cloud.h"

#include <string>
#include <vector>
#include <fstream>
#include <map>

namespace SCPC {
    class PolygonFileFormat
    {
    private:
        std::string file;
        std::string header;
        std::pair<PropertyType, PropertyType> property{std::make_pair(INITIAL_VALUE, INITIAL_VALUE)};
        uint64_t element;
        std::vector<XYZRGB<long double, long double>> points;

        auto Property_Check(const std::vector<std::pair<GeomAttr, PropertyType>>& prop) noexcept -> bool {
            if ( prop.size() != 3 || prop.size() != 6 ) return false;
            std::vector<bool> vec(3, false);
            for ( const auto& index : prop )
            {
                if ( index.first == X || index.first == Y || index.first == Z ){
                    vec[index.first - 1] = true;
                    this->property.first = index.second;
                }else this->property.second = index.second;
            }
            
            return vec[0] && vec[1] && vec[2];
        };
        void Read_data(std::ifstream& ifs);
    public:
        PolygonFileFormat(const std::string& file_) : file(file_){}
        auto Read_header() noexcept -> std::ifstream;
        void Read(){
            auto start = Read_header();
            Read_data(start);
        };
        void Sort(){
            file += ".sorted.ply";
            std::sort(points.begin(), points.end(), [](const XYZRGB<long double, long double>& a, const XYZRGB<long double, long double>& b){
                return std::tie(a.x, a.y, a.z, a.r, a.g, a.b) < std::tie(b.x, b.y, b.z, b.r, b.g, b.b);
            });
        };
        void Cut(){
            file += ".cut.ply";
            property.second = INITIAL_VALUE;
        };
        void Write() noexcept;
    };
    
    
};

#endif