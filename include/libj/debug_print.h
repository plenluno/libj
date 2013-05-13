// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DEBUG_PRINT_H_
#define LIBJ_DEBUG_PRINT_H_

#ifdef LIBJ_DEBUG
# include <libj/console.h>
# define LIBJ_DEBUG_PRINT(FMT, ...) \
    libj::console::printf( \
        libj::console::LEVEL_DEBUG, \
        "[LIBJ DEBUG] " FMT "\n", \
        ##__VA_ARGS__);
#else
# define LIBJ_DEBUG_PRINT(FMT, ...)
#endif

#endif  // LIBJ_DEBUG_PRINT_H_
