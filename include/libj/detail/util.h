// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_UTIL_H_
#define LIBJ_DETAIL_UTIL_H_

#include <libj/exception.h>
#include <libj/value.h>

namespace libj {
namespace detail {

template<typename T>
inline Boolean convert(const Value& v, T* t, Boolean throwable = true) {
    Boolean result = to<T>(v, t);
#ifdef LIBJ_USE_EXCEPTION
    if (!result && throwable) LIBJ_THROW(Error::ILLEGAL_TYPE);
#endif  // LIBJ_USE_EXCEPTION
    return result;
}

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_UTIL_H_
