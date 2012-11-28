// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_CAST_H_
#define LIBJ_CAST_H_

#include <libj/detail/pointer.h>

#ifdef LIBJ_USE_SP
    #define LIBJ_STATIC_PTR_CAST(T) STATIC_POINTER_CAST(T)
    #define LIBJ_STATIC_CPTR_CAST(T) STATIC_POINTER_CAST(const T)
#else
    #define LIBJ_STATIC_PTR_CAST(T) static_cast<T*>
    #define LIBJ_STATIC_CPTR_CAST(T) static_cast<const T*>
#endif

#endif  // LIBJ_CAST_H_
