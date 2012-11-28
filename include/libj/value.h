// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_VALUE_H_
#define LIBJ_VALUE_H_

#include <libj/detail/value.h>

namespace libj {

typedef detail::Value Value;

template<typename T>
Boolean to(const Value & val, T* out);

template<typename T>
typename Type<T>::Ptr toPtr(const Value& val);

template<typename T>
typename Type<T>::CPtr toCPtr(const Value& val);

}  // namespace libj

#include <libj/impl/value.h>

#endif  // LIBJ_VALUE_H_
