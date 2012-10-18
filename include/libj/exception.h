// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_EXCEPTION_H_
#define LIBJ_EXCEPTION_H_

#include <libj/error.h>

#ifdef LIBJ_USE_EXCEPTION

#include <exception>

#include "libj/string.h"

namespace libj {

class Exception : public std::exception {
 public:
    Exception(Error::Code code)
        : err_(Error::create(code))
        , file_(String::null())
        , func_(String::null())
        , line_(0) {}

    Exception(String::CPtr message)
        : err_(Error::create(Error::ANY))
        , file_(String::null())
        , func_(String::null())
        , line_(0) {}

    Exception(Error::Code code, String::CPtr message)
        : err_(Error::create(code, message))
        , file_(String::null())
        , func_(String::null())
        , line_(0) {}

    Exception(Error::Code code, const char* file, const char* func, int line)
        : err_(Error::create(code))
        , file_(String::create(file))
        , func_(String::create(func))
        , line_(line) {}

    virtual ~Exception() throw() {}

    Int code() const {
        return err_ ? err_->code() : -1;
    }

    String::CPtr message() const {
        return err_ ? err_->message() : String::null();
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

 protected:
    Error::CPtr err_;
    String::CPtr file_;
    String::CPtr func_;
    Int line_;
};

#define LIBJ_THROW(code) \
    throw libj::Exception(code, __FILE__, __func__, __LINE__);

#define LIBJ_HANDLE_ERROR(code) \
    LIBJ_THROW(code)

}  // namespace libj

#endif  // LIBJ_USE_EXCEPTION

#endif  // LIBJ_EXCEPTION_H_
