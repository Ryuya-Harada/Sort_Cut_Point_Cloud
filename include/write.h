#pragma once
#ifndef _SCPC_WRITE_H
#define _SCPC_WRITE_H

#include "ply.h"

namespace SCPC {
    template<typename T>
    inline auto Convert(const long double& num){
        return std::to_string(static_cast<T>(num));
    };

    std::string Composite(const PropertyType& type, const long double& num) noexcept {
        switch (type)
        {
        case CHAR:
            return Convert<int8_t>(num);
        case UCHAR:
            return Convert<uint8_t>(num);
        case SHORT:
            return Convert<int16_t>(num);
        case USHORT:
            return Convert<uint16_t>(num);
        case INT:
            return Convert<int32_t>(num);
        case UINT:
            return Convert<uint32_t>(num);
        case FLOAT:
            return Convert<_Float32>(num);
        case DOUBLE:
            return Convert<_Float64>(num);
        default:
            return Convert<int32_t>(num);
        }
    };

    void PolygonFileFormat::Write() noexcept {
        std::ofstream ofs(file);
        ofs << header;
        ofs << "element vertex " << points.size() << std::endl;
        ofs << "property " << Out_Property(property.first) << " x\n";
        ofs << "property " << Out_Property(property.first) << " y\n";
        ofs << "property " << Out_Property(property.first) << " z\n";
        if ( property.second != INITIAL_VALUE ){
            ofs << "property " << Out_Property(property.second) << " r\n";
            ofs << "property " << Out_Property(property.second) << " g\n";
            ofs << "property " << Out_Property(property.second) << " b\n";
        }
        ofs << "end_header\n";

        for (const auto& index : points){
            ofs << Composite(property.first, index.x) << " "
                << Composite(property.first, index.y) << " "
                << Composite(property.first, index.z) << " ";
            if ( property.second == INITIAL_VALUE ) ofs << "\n";
            else {
                ofs << Composite(property.second, index.r) << " "
                    << Composite(property.second, index.g) << " "
                    << Composite(property.second, index.b) << "\n";
            }
        }
    };
};

#endif