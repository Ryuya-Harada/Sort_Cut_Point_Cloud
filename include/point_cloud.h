#pragma once
#ifndef _SCPC_POINT_CLOUD_H
#define _SCPC_POINT_CLOUD_H

namespace SCPC {
    enum PropertyType {
        INITIAL_VALUE,
        CHAR,
        UCHAR,
        SHORT,
        USHORT,
        INT,
        UINT,
        FLOAT,
        DOUBLE,
    };

    enum GeomAttr {
        NON,
        X,
        Y,
        Z,
        R,
        G,
        B,
    };
    
    template<typename T, typename U>
    struct XYZRGB {
        public:
        XYZRGB() : x(0), y(0), z(0), r(0), g(0), b(0){}
        XYZRGB(const T& x_, const T& y_, const T& z_) : x(x_), y(y_), z(z_){}
        XYZRGB(const T& x_, const T& y_, const T& z_, const U& r_, const U& g_, const U& b_)
         : x(x_), y(y_), z(z_), r(r_), g(g_), b(b_){}

        T x;
        T y;
        T z;
        U r;
        U g;
        U b;
    };
};

#endif