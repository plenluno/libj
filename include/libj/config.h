// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_CONFIG_H_
#define LIBJ_CONFIG_H_

#ifdef LIBJ_USE_BOEHM_GC
#include <gc_cpp.h>
#else
#define LIBJ_USE_SP
#endif

#endif  // LIBJ_CONFIG_H_
