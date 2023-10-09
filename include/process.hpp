
#pragma once
#ifndef _SCPC_PROCESS_HPP
#define _SCPC_PROCESS_HPP

#include "header.hpp"
#include "ply.hpp"
#include "vertex.hpp"
#include "face.hpp"

namespace SCPC{
    class Process_Data
    {
        public:
        Process_Data(const bool& cut_, const bool& sort_, const Elements& elements_, const FormatType& format_, const std::string& file_) : 
            cut(cut_), sort(sort_), elements(elements_), format(format_), file(file_) {}
        const bool cut;
        const bool sort;
        const Elements elements;
        const FormatType format;
        const std::string file;
    };

    template<class Points>
    inline void Process_Vertex(const Process_Data& process_data, std::ifstream& ifs){
        auto vertex = Vertex<Points>(process_data.elements, process_data.format);
        vertex.Read(ifs);
        if ( process_data.sort ) vertex.Sort();
        if ( process_data.cut ) vertex.Cut();
        vertex.Write(process_data.file);
    };

    template<typename T, typename U, typename N>
    inline void Decide_Type(const Process_Data& process_data, std::ifstream& ifs, const bool& alpha){
        if ( alpha ) Process_Vertex<XYZRGBNA_<T, U, N>>(process_data, ifs);
        else Process_Vertex<XYZRGBN_<T, U, N>>(process_data, ifs);
    };

    template<typename T, typename U>
    inline void Decide_Normal_type(const Process_Data& process_data, std::ifstream& ifs, Decide_Point_Type& point_type){
        switch (point_type.geometry)
        {
            case INT8:      Decide_Type<T, U, int8>(process_data, ifs, point_type.alpha);     break;
            case UINT8:     Decide_Type<T, U, uint8>(process_data, ifs, point_type.alpha);    break;
            case INT16:     Decide_Type<T, U, int16>(process_data, ifs, point_type.alpha);    break;
            case UINT16:    Decide_Type<T, U, uint16>(process_data, ifs, point_type.alpha);   break;
            case INT32:     Decide_Type<T, U, int32>(process_data, ifs, point_type.alpha);    break;
            case UINT32:    Decide_Type<T, U, uint32>(process_data, ifs, point_type.alpha);   break;
            case FLOAT32:   Decide_Type<T, U, float32>(process_data, ifs, point_type.alpha);  break;
            case FLOAT64:   Decide_Type<T, U, float64>(process_data, ifs, point_type.alpha);  break;
            default:        Process_Vertex<XYZRGB_<T, U>>(process_data, ifs);                 break;
        };
    };

    template<typename T>
    inline void Decide_Attribute_type(const Process_Data& process_data, std::ifstream& ifs, Decide_Point_Type& point_type){
        switch (point_type.attribute)
        {
            case INT8:      Decide_Normal_type<T, int8>(process_data, ifs, point_type);         break;
            case UINT8:     Decide_Normal_type<T, uint8>(process_data, ifs, point_type);        break;
            case INT16:     Decide_Normal_type<T, int16>(process_data, ifs, point_type);        break;
            case UINT16:    Decide_Normal_type<T, uint16>(process_data, ifs, point_type);       break;
            case INT32:     Decide_Normal_type<T, int32>(process_data, ifs, point_type);        break;
            case UINT32:    Decide_Normal_type<T, uint32>(process_data, ifs, point_type);       break;
            case FLOAT32:   Decide_Normal_type<T, float32>(process_data, ifs, point_type);      break;
            case FLOAT64:   Decide_Normal_type<T, float64>(process_data, ifs, point_type);      break;
            default:        Process_Vertex<XYZ_<T>>(process_data, ifs);                         break;
        }
    };

    inline void Decide_Geometry_type(const Process_Data& process_data, std::ifstream& ifs, Decide_Point_Type& point_type){
        switch (point_type.geometry)
        {
            case INT8:      Decide_Attribute_type<int8>(process_data, ifs, point_type);         break;
            case UINT8:     Decide_Attribute_type<uint8>(process_data, ifs, point_type);        break;
            case INT16:     Decide_Attribute_type<int16>(process_data, ifs, point_type);        break;
            case UINT16:    Decide_Attribute_type<uint16>(process_data, ifs, point_type);       break;
            case INT32:     Decide_Attribute_type<int32>(process_data, ifs, point_type);        break;
            case UINT32:    Decide_Attribute_type<uint32>(process_data, ifs, point_type);       break;
            case FLOAT32:   Decide_Attribute_type<float32>(process_data, ifs, point_type);      break;
            case FLOAT64:   Decide_Attribute_type<float64>(process_data, ifs, point_type);      break;
            default:        Error_Message("Mismatch : Geometry Data Type");                     break;
        }
    };

    inline void Point_type(const Process_Data& process_data, std::ifstream& ifs){
        auto point_type = Decide_Point_Type(process_data.elements.types);
        if ( point_type.def ){
            if ( point_type.XYZRGBNA() )        Process_Vertex<XYZRGBNA>(process_data, ifs);
            else if ( point_type.XYZRGBN() )    Process_Vertex<XYZRGBN>(process_data, ifs);
            else if ( point_type.XYZRGB() )     Process_Vertex<XYZRGB>(process_data, ifs);
            else                                Process_Vertex<XYZ>(process_data, ifs);
        }else                                   Decide_Geometry_type(process_data, ifs, point_type);
    };

    template<class Lists>
    inline void Process_Face(const Process_Data& process_data, std::ifstream& ifs){
        auto face = Face<Lists>(process_data.elements, process_data.format);
        face.Read(ifs);
        if ( !process_data.cut ){
            if ( process_data.sort ) face.Sort();
            face.Write(process_data.file);
        }
    };

    inline void Decide_List_type(const Process_Data& process_data, std::ifstream& ifs){
        switch (process_data.elements.types[1].second.type)
        {
            case INT8:      Process_Face<List_<int8>>(process_data, ifs);         break;
            case UINT8:     Process_Face<List_<uint8>>(process_data, ifs);        break;
            case INT16:     Process_Face<List_<int16>>(process_data, ifs);        break;
            case UINT16:    Process_Face<List_<uint16>>(process_data, ifs);       break;
            case INT32:     Process_Face<List_<int32>>(process_data, ifs);        break;
            case UINT32:    Process_Face<List_<uint32>>(process_data, ifs);       break;
            case FLOAT32:   Process_Face<List_<float32>>(process_data, ifs);      break;
            case FLOAT64:   Process_Face<List_<float64>>(process_data, ifs);      break;
            default:        Error_Message("Mismatch : List Data Type");          break;
        }
    };

    inline void List_type(const Process_Data& process_data, std::ifstream& ifs){
        if ( process_data.elements.types[0].second.type == UINT8
          && process_data.elements.types[1].second.type == INT32 ) Process_Face<List>(process_data, ifs);
        else Decide_List_type(process_data, ifs);
    };

    inline void Process(std::string file, const bool& cut, const bool& sort){
        auto header = Header();
        auto ifs = header.Read(file);
        if ( sort ) file += ".sorted.ply";
        if ( cut ) file += ".cut.ply";
        header.Write(file, cut);
        for ( const auto& element : header.elements )
        {
            const auto process_data = Process_Data(cut, sort, element, header.format, file);
            switch(element.element.type){
                case VERTEX:    Point_type(process_data, ifs);                     break;
                case FACE:      List_type(process_data, ifs);                      break;
                default:        Error_Message("Not Supproted Element Type");       break;
            };
        }
    };
    
};

#endif