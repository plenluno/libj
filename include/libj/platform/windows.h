// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_PLATFORM_WINDOWS_H_
#define LIBJ_PLATFORM_WINDOWS_H_

#include <direct.h>
#include <float.h>
#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>

#define __func__ __FUNCTION__

#define getcwd _getcwd

#define snprintf _snprintf

#define usleep(useconds) Sleep(useconds/1000)

namespace std {
    inline bool isinf(double x) {
        return _fpclass(x) & (_FPCLASS_PINF | _FPCLASS_NINF);
    }

    inline bool isnan(double x) {
        return _isnan(x);
    }

    inline bool signbit(double x) {
        return (_fpclass(x) & _FPCLASS_NZ) || x < 0;
    }
}

#endif  // LIBJ_PLATFORM_WINDOWS_H_
