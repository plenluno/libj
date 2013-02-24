// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_PLATFORM_WINDOWS_H_
#define LIBJ_PLATFORM_WINDOWS_H_

#include <Windows.h>

#define snprintf _snprintf
#define usleep(useconds) Sleep(useconds)
#define __func__ __FUNCTION__

#endif  // LIBJ_PLATFORM_WINDOWS_H_
