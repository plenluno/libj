// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_EXCEPTION_H_
#define LIBJ_EXCEPTION_H_

#ifdef LIBJ_USE_EXCEPTION

#include <exception>

#include "libj/string.h"

namespace libj {

class Exception : public std::exception {
 public:
    Exception(
        Int code,
        String::CPtr message);

    Exception(
        Int code,
        const char* file,
        const char* func,
        int line);

    Exception(
        Int code,
        String::CPtr message,
        const char* file,
        const char* func,
        int line);

    virtual ~Exception() throw();

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
