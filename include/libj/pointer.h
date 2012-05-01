// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_POINTER_H_
#define LIBJ_POINTER_H_

#include "libj/config.h"

#ifdef LIBJ_USE_SP
#include "libj/shared_ptr.h"
#define LIBJ_PTR(T) libj::SharedPtr<T>::Type
#define LIBJ_CPTR(T) libj::SharedPtr<const T>::Type
#define LIBJ_PTR_TYPE(T) typename libj::SharedPtr<T>::Type
#define LIBJ_CPTR_TYPE(T) typename libj::SharedPtr<const T>::Type
#else
#define LIBJ_PTR(T) T*
#define LIBJ_CPTR(T) const T*
#define LIBJ_PTR_TYPE(T) T*
#define LIBJ_CPTR_TYPE(T) const T*
#endif

#endif  // LIBJ_POINTER_H_
