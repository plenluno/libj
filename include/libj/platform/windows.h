// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_PLATFORM_WINDOWS_H_
#define LIBJ_PLATFORM_WINDOWS_H_

#include <direct.h>
#include <Windows.h>

#define __func__ __FUNCTION__

#define getcwd _getcwd

#define snprintf _snprintf

#define usleep(useconds) Sleep(useconds/1000)

#endif  // LIBJ_PLATFORM_WINDOWS_H_
