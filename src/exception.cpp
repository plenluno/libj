// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/error.h"
#include "libj/exception.h"

#ifdef LIBJ_USE_EXCEPTION

namespace libj {

Exception::Exception(Int code)
    : code_(code)
    , msg_(LIBJ_NULL(String))
    , file_(LIBJ_NULL(String))
    , func_(LIBJ_NULL(String))
    , line_(0) {}

Exception::Exception(String::CPtr message)
    : code_(Error::ANY)
    , msg_(message)
    , file_(LIBJ_NULL(String))
    , func_(LIBJ_NULL(String))
    , line_(0) {}

Exception::Exception(Int code, String::CPtr message)
    : code_(code)
    , msg_(message)
    , file_(LIBJ_NULL(String))
    , func_(LIBJ_NULL(String))
    , line_(0) {}

Exception::Exception(Int code, const char* file, const char* func, int line)
    : code_(code)
    , msg_(LIBJ_NULL(String))
    , file_(String::create(file))
    , func_(String::create(func))
    , line_(line) {}

Exception::~Exception() throw() {}

}  // namespace libj

#endif  // LIBJ_USE_EXCEPTION
