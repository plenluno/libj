// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/exception.h"

namespace libj {

Exception::Exception(
    Int code,
    String::CPtr message)
    : code_(code)
    , msg_(message)
    , file_(static_cast<String*>(0))
    , func_(static_cast<String*>(0))
    , line_(0) {}

Exception::Exception(
    Int code,
    const char* file,
    const char* func,
    int line)
    : code_(code)
    , msg_(static_cast<String*>(0))
    , file_(String::create(file))
    , func_(String::create(func))
    , line_(line) {}

Exception::Exception(
    Int code,
    String::CPtr message,
    const char* file,
    const char* func,
    int line)
    : code_(code)
    , msg_(message)
    , file_(String::create(file))
    , func_(String::create(func))
    , line_(line) {}

Exception::~Exception() throw() {}

}  // namespace libj
