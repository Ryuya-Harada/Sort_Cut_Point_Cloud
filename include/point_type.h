#pragma once
#ifndef _SCPC_POINT_TYPE_H
#define _SCPC_POINT_TYPE_H

#include "point_cloud.h"

#include <string>

namespace SCPC {
    inline auto In_Property(const std::string& str) noexcept {
        if ( str == "char" || str == "int8" ) return CHAR;
        else if ( str == "uchar" || str == "uint8" ) return UCHAR;
        else if ( str == "short" || str == "int16" ) return SHORT;
        else if ( str == "ushort" || str == "uint16" ) return USHORT;
        else if ( str == "int" || str == "int32" ) return INT;
        else if ( str == "uint" || str == "uint32" ) return UINT;
        else if ( str == "float" || str == "float32" ) return FLOAT;
        else if ( str == "double" || str == "float64" ) return DOUBLE;
        else std::logic_error("Not Supported Data Type\n\n");
        return INITIAL_VALUE;
    };

    inline auto Out_Property(const PropertyType& type) noexcept {
        switch (type)
        {
        case CHAR:
            return "char";
        case UCHAR:
            return "uchar";
        case SHORT:
            return "short";
        case USHORT:
            return "ushort";
        case INT:
            return "int";
        case UINT:
            return "uint";
        case FLOAT:
            return "float";
        case DOUBLE:
            return "double";
        default:
            return "int";
        }
    };

    inline auto In_Geom_Attr(const std::string& str) noexcept {
        if ( str == "x" ) return X;
        else if ( str == "y" ) return Y;
        else if ( str == "z" ) return Z;
        else if ( str == "red" ) return R;
        else if ( str == "green" ) return G;
        else if ( str == "blue" ) return B;
        else std::logic_error("Not Supported Property\n\n");
        return NON;
    };

    
};

#endif