#pragma once
#ifndef _SCPC_TYPE_HPP
#define _SCPC_TYPE_HPP

#include "const.hpp"

namespace SCPC {
    enum FormatType {
        ERRORF,
        ASCII,
        LITTLE,
        BIG
    };

    inline auto Format(const std::string& str) noexcept -> FormatType {
        if ( str == "ascii" )                       return ASCII;
        else if ( str == "binary_little_endian" )   return LITTLE;
        else if ( str == "binary_big_endian" )      return BIG;
        else                                        return ERRORF;
    };

    enum ElementType {
        ERRORE,
        VERTEX,
        FACE
    };

    inline auto Element(const std::string& str) noexcept -> ElementType {
        if ( str == "vertex" )      return VERTEX;
        else if ( str == "face" )   return FACE;
        else                        return ERRORE;
    };

    enum PropertyType {
        ERRORP,
        X,
        Y,
        Z,
        NX,
        NY,
        NZ,
        R,
        G,
        B,
        A,
        LIST
    };

    inline auto Property(const std::string& str) noexcept -> PropertyType {
        if ( str == "x" )           return X;
        else if ( str == "y" )      return Y;
        else if ( str == "z" )      return Z;
        else if ( str == "nx" )     return NX;
        else if ( str == "ny" )     return NY;
        else if ( str == "nz" )     return NZ;
        else if ( str == "red" )    return R;
        else if ( str == "green" )  return G;
        else if ( str == "blue" )   return B;
        else if ( str == "alpha" )  return A;
        else if ( str == "list" )   return LIST;
        else                        return ERRORP;
    };

    enum DataType {
        ERRORD,
        INT8,
        UINT8,
        INT16,
        UINT16,
        INT32,
        UINT32,
        FLOAT32,
        FLOAT64
    };

    inline auto Data(const std::string& str) noexcept -> DataType {
        if ( str == "char" || str == "int8" )           return INT8;
        else if ( str == "uchar" || str == "uint8" )    return UINT8;
        else if ( str == "short" || str == "int16" )    return INT16;
        else if ( str == "ushort" || str == "uint16" )  return UINT16;
        else if ( str == "int" || str == "int32" )      return INT32;
        else if ( str == "uint" || str == "uint32" )    return UINT32;
        else if ( str == "float" || str == "float32" )  return FLOAT32;
        else if ( str == "double" || str == "float64" ) return FLOAT64;
        else                                            return ERRORD;
    };

    template<typename T>
    struct Type {
        Type(const std::string& str_, const T& type_) : str(str_), type(type_) {}
        const T type;
        const std::string str;
    };

    template<typename T>
    bool operator==(const Type<T>& a, const T& b) noexcept { return a.type == b; };
    template<typename T>
    bool operator!=(const Type<T>& a, const T& b) noexcept { return a.type != b; };

    using vecPD = std::vector<std::pair<Type<PropertyType>, Type<DataType>>>;

    struct Elements{
        Elements(const std::string& str, const ull& num_) : element(Type<ElementType>(str, Element(str))), num(num_) {}
        Elements(const Elements& elements) : element(elements.element), num(elements.num), types(elements.types) {}
        const Type<ElementType> element;
        const ull num;
        vecPD types;
    };
};

#endif