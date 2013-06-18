// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_EXCEPTION_H_
#define LIBJ_EXCEPTION_H_

#include <libj/error.h>

#ifdef LIBJ_USE_EXCEPTION

#ifdef LIBJ_PF_WINDOWS
#include <libj/platform/windows.h>
#endif

#include <exception>

namespace libj {

class Exception : public std::exception {
 public:
    Exception(Error::Code code);

    Exception(String::CPtr message);

    Exception(Error::Code code, String::CPtr message);

    Exception(Error::Code code, const char* file, const char* func, int line);

    virtual ~Exception() throw();

    Int code() const;

    String::CPtr message() const;

    String::CPtr file() const;

    String::CPtr function() const;

    Int line() const;

 private:
    class Impl;
    Impl* impl_;
};

}  // namespace libj

#define LIBJ_THROW(code) \
    throw libj::Exception(code, __FILE__, __func__, __LINE__);

#define LIBJ_HANDLE_ERROR(code) \
    LIBJ_THROW(code)

#endif  // LIBJ_USE_EXCEPTION

#endif  // LIBJ_EXCEPTION_H_
