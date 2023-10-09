#pragma once
#ifndef _SCPC_IOPUT_HPP
#define _SCPC_IOPUT_HPP

#include "type.hpp"

namespace SCPC {
    inline bool Swap_Order(char* byte, const std::streamsize& size)
    {
        if ( size == 1 ) return true;
        else if ( size % 2 != 0 ) return false;
        for (int i = 0; i < size / 2; i++)
            std::swap(byte[i], byte[size - i - 1]);
        return true;
    };

    template<typename T>
    inline void Swap_Order(T& value){
        if ( !Swap_Order(reinterpret_cast<char*>(&value), sizeof(T)) ) Error_Message("Cant Swap Bytes Order");
    };

    template<typename U>
    inline auto Format_type_input(const FormatType& f, std::ifstream& ifs){
        U u = static_cast<U>(0.f);
        switch (f)
        {
            case ASCII:
                float64 f;
                ifs >> f >> std::ws;
                u = static_cast<U>(f);
                break;
            case LITTLE: ifs.read(reinterpret_cast<char*>(&u), sizeof(U)); break;
            case BIG:
                ifs.read(reinterpret_cast<char*>(&u), sizeof(U));
                Swap_Order<U>(u);
                break;
            default: Error_Message("Not Supproted Format Type"); break;
        };
        return u;
    };

    inline auto Data_type_input(const DataType& d, const FormatType& f, std::ifstream& ifs){
        switch(d)
        {
            case INT8:      return static_cast<lld>(Format_type_input<int8>(f, ifs));        break;
            case UINT8:     return static_cast<lld>(Format_type_input<uint8>(f, ifs));       break;
            case INT16:     return static_cast<lld>(Format_type_input<int16>(f, ifs));       break;
            case UINT16:    return static_cast<lld>(Format_type_input<uint16>(f, ifs));      break;
            case INT32:     return static_cast<lld>(Format_type_input<int32>(f, ifs));       break;
            case UINT32:    return static_cast<lld>(Format_type_input<uint32>(f, ifs));      break;
            case FLOAT32:   return static_cast<lld>(Format_type_input<float32>(f, ifs));     break;
            case FLOAT64:   return static_cast<lld>(Format_type_input<float64>(f, ifs));     break;
            default:        return static_cast<lld>(0);                                      break;
        };
    };
};

#endif