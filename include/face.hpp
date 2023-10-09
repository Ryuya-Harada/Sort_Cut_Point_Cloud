#pragma once
#ifndef _SCPC_FACE_HPP
#define _SCPC_FACE_HPP

#include "type.hpp"
#include "ioput.hpp"

namespace SCPC {
    template<class T>
    class Face
    {
    private:
        std::vector<T> lists;
        Elements element;
        FormatType format;
        auto List_Type(std::ifstream& ifs){
            auto list = T(Data_type_input(element.types[0].second.type, format, ifs));
            for (int i = 0; i < list.vertex.size(); i++)
                list.Input(i, Data_type_input(element.types[1].second.type, format, ifs));
            return list;
        };
        template<typename U>
        auto Size_to_str(const size_t& num){
            return std::to_string(static_cast<U>(num));
        };
        auto List_Size(const size_t& num, const DataType& data){
            switch(data)
            {
                case INT8:      return Size_to_str<int8>(num);      break;
                case UINT8:     return Size_to_str<uint8>(num);     break;
                case INT16:     return Size_to_str<int16>(num);     break;
                case UINT16:    return Size_to_str<uint16>(num);    break;
                case INT32:     return Size_to_str<int32>(num);     break;
                case UINT32:    return Size_to_str<uint32>(num);    break;
                case FLOAT32:   return Size_to_str<float32>(num);   break;
                case FLOAT64:   return Size_to_str<float64>(num);   break;
                default:        return Size_to_str<uint8>(num);     break;
            };
        };
    public:
        Face(const Elements& element_, const FormatType& format_) : element(element_), format(format_) {}
        void Read(std::ifstream& ifs){
            lists.reserve(element.num);
            for (int i = 0; i < element.num; i++)
                lists.push_back(List_Type(ifs));
        };
        void Sort(){
            std::sort(lists.begin(), lists.end(), [](const T& a, const T& b){
                return std::tie(a.vertex) < std::tie(b.vertex);
            });
        };
        void Write(const std::string file){
            std::ofstream ofs;
            ofs.open(file, std::ios::app);
            for ( const auto& list : lists )
            {
                std::stringstream ss;
                ss << List_Size(list.vertex.size(), element.types[0].second.type) << " ";
                ss << list.Output();
                ofs << ss.str() << std::endl;
            }
            ofs.close();
        };
    };
};

#endif