// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_THIS_H_
#define LIBJ_THIS_H_

#include <libj/cast.h>

#define LIBJ_THIS_PTR(T) LIBJ_STATIC_PTR_CAST(T)(self())
#define LIBJ_THIS_CPTR(T) LIBJ_STATIC_CPTR_CAST(T)(self())

#endif  // LIBJ_THIS_H_
