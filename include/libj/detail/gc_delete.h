// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GC_DELETE_H_
#define LIBJ_DETAIL_GC_DELETE_H_

#include <libj/config.h>

#ifdef LIBJ_USE_BDWGC

#define LIBJ_GC_DELETE(P) delete P

#else   // LIBJ_USE_BDWGC

#define LIBJ_GC_DELETE(P)

#endif  // LIBJ_USE_BDWGC

#endif  // LIBJ_DETAIL_GC_DELETE_H_
