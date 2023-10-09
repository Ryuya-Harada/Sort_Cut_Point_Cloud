#pragma once
#ifndef _SCPC_PLY_HPP
#define _SCPC_PLY_HPP


#include "type.hpp"

namespace SCPC {
    template<typename T>
    class Vec3{
        private:
        std::vector<T> vec{0, 0, 0};
        public:
        Vec3(){}
        auto a() const { return vec[0]; };
        auto b() const { return vec[1]; };
        auto c() const { return vec[2]; };
        auto a_str() const { return std::to_string(vec[0]); };
        auto b_str() const { return std::to_string(vec[1]); };
        auto c_str() const { return std::to_string(vec[2]); };
        void a(const lld& num){ vec[0] = static_cast<T>(num); };
        void b(const lld& num){ vec[1] = static_cast<T>(num); };
        void c(const lld& num){ vec[2] = static_cast<T>(num); };
    };

    template<typename T>
    bool operator<(const Vec3<T>& A, const Vec3<T>& B) noexcept {
        if ( A.a() < B.a() ) return true;
        else if ( A.a() > B.a() ) return false;
        else if ( A.b() < B.b() ) return true;
        else if ( A.b() > B.b() ) return false;
        else if ( A.c() < B.c() ) return true;
        else if ( A.c() > B.c() ) return false;
        Error_Message("Geometry Perfect Match");
        return true;
    };

#ifndef SCPC_Geom_In
#define SCPC_Geom_In                                \
        case X:     geom.a(num);        break;      \
        case Y:     geom.b(num);        break;      \
        case Z:     geom.c(num);        break;  
#endif
#ifndef SCPC_Geom_Out
#define SCPC_Geom_Out                                       \
        case X:     return geom.a_str();        break;      \
        case Y:     return geom.b_str();        break;      \
        case Z:     return geom.c_str();        break;  
#endif

    template<typename T>
    struct XYZ_ {
        Vec3<T> geom;
        void Input(const PropertyType& p, const lld& num){
            switch (p)
            {
                SCPC_Geom_In
                default:    break;
            }
        };
        auto Output(const PropertyType& p) const {
            switch (p)
            {
                SCPC_Geom_Out
                default:    return Return_Null();       break;
            }
        };
    };

#ifndef SCPC_Attr_In
#define SCPC_Attr_In                                \
        case R:     attr.a(num);        break;      \
        case G:     attr.b(num);        break;      \
        case B:     attr.c(num);        break;  
#endif
#ifndef SCPC_Attr_Out
#define SCPC_Attr_Out                                       \
        case R:     return attr.a_str();        break;      \
        case G:     return attr.b_str();        break;      \
        case B:     return attr.c_str();        break;  
#endif
    
    template<typename T, typename U>
    struct XYZRGB_ {
        Vec3<T> geom;
        Vec3<U> attr;
        void Input(const PropertyType& p, const lld& num){
            switch (p)
            {
                SCPC_Geom_In
                SCPC_Attr_In
                default:    break;
            }
        };
        auto Output(const PropertyType& p) const {
            switch (p)
            {
                SCPC_Geom_Out
                SCPC_Attr_Out
                default:    return Return_Null();       break;
            }
        };
    };

#ifndef SCPC_Norm_In
#define SCPC_Norm_In                                 \
        case NX:     norm.a(num);        break;      \
        case NY:     norm.b(num);        break;      \
        case NZ:     norm.c(num);        break;  
#endif
#ifndef SCPC_Norm_Out
#define SCPC_Norm_Out                                       \
        case NX:     return norm.a_str();        break;      \
        case NY:     return norm.b_str();        break;      \
        case NZ:     return norm.c_str();        break;  
#endif

    template<typename T, typename U, typename N>
    struct XYZRGBN_ {
        Vec3<T> geom;
        Vec3<U> attr;
        Vec3<N> norm;
        void Input(const PropertyType& p, const lld& num){
            switch (p)
            {
                SCPC_Geom_In
                SCPC_Attr_In
                SCPC_Norm_In
                default:    break;
            }
        };
        auto Output(const PropertyType& p) const {
            switch (p)
            {
                SCPC_Geom_Out
                SCPC_Attr_Out
                SCPC_Norm_Out
                default:    return Return_Null();       break;
            }
        };
    };

    template<typename T, typename U, typename N>
    struct XYZRGBNA_ {
        Vec3<T> geom;
        Vec3<U> attr;
        Vec3<N> norm;
        Vec3<U> alpha;
        void Input(const PropertyType& p, const lld& num){
            switch (p)
            {
                SCPC_Geom_In
                SCPC_Attr_In
                SCPC_Norm_In
                case A:     alpha.a(num);       break;
                default:    break;
            }
        };
        auto Output(const PropertyType& p) const {
            switch (p)
            {
                SCPC_Geom_Out
                SCPC_Attr_Out
                SCPC_Norm_Out
                case A:     return alpha.a_str();       break;
                default:    return Return_Null();       break;
            }
        };
    };

    template<typename T>
    class List_ {
        public:
        List_(const uint8& u){ vertex = std::vector<T>(u); };
        List_(const lld& u){ vertex = std::vector<T>(static_cast<size_t>(u)); };
        void Input(size_t i, const lld& num){
            vertex[i] = static_cast<T>(num);
        };
        std::string Output() const {
            std::stringstream ss;
            for ( const auto& index : vertex )
                ss << std::to_string(index) << " ";
            return ss.str();
        };
        std::vector<T> vertex;
    };

    using XYZ = XYZ_<float32>;
    using XYZRGB = XYZRGB_<float32, uint8>;
    using XYZRGBN = XYZRGBN_<float32, uint8, float32>;
    using XYZRGBNA = XYZRGBNA_<float32, uint8, float32>;
    using List = List_<int32>;
};

#endif