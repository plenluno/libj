// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_EXCEPTION_H_
#define LIBJ_EXCEPTION_H_

#include <libj/config.h>

#ifdef LIBJ_USE_EXCEPTION

#include <exception>

#include "libj/string.h"

namespace libj {

class Exception : public std::exception {
 public:
    Exception(Int code)
        : code_(code)
        , msg_(String::null())
        , file_(String::null())
        , func_(String::null())
        , line_(0) {}

    Exception(String::CPtr message)
        : code_(1)  // Error::ANY
        , msg_(message)
        , file_(String::null())
        , func_(String::null())
        , line_(0) {}

    Exception(Int code, String::CPtr message)
        : code_(code)
        , msg_(message)
        , file_(String::null())
        , func_(String::null())
        , line_(0) {}

    Exception(Int code, const char* file, const char* func, int line)
        : code_(code)
        , msg_(String::null())
        , file_(String::create(file))
        , func_(String::create(func))
        , line_(line) {}

    virtual ~Exception() throw() {}

    Int code() const {
        return code_;
    }

    String::CPtr message() const {
        return msg_;
    }

    String::CPtr file() const {
        return file_;
    }

    String::CPtr function() const {
        return func_;
    }

    Int line() const {
        return line_;
    }

 private:
    Int code_;
    String::CPtr msg_;
    String::CPtr file_;
    String::CPtr func_;
    Int line_;
};

#define LIBJ_THROW(code) \
    throw libj::Exception(code, __FILE__, __func__, __LINE__)

}  // namespace libj

#endif  // LIBJ_USE_EXCEPTION

#endif  // LIBJ_EXCEPTION_H_
