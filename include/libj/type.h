// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPE_H_
#define LIBJ_TYPE_H_

#include <boost/type_traits/is_base_of.hpp>
#include "libj/gc_base.h"
#include "libj/pointer.h"
#include "libj/typedef.h"

namespace libj {

enum Category {
    PRIMITIVE,
    OBJECT,
    MUTABLE,
    IMMUTABLE,
    SINGLETON,
    UNDEFINED,
};

class Object {};
class Mutable   : public Object {};
class Immutable : public Object {};
class Singleton : public Object {};

#define LIBJ_TYPE_ID() static TypeId id() { \
    static char c; \
    return reinterpret_cast<TypeId>(&c); \
}

template <typename T, Category =
    boost::is_base_of<Object, T>::value
        ? boost::is_base_of<Mutable, T>::value
            ? MUTABLE
            : boost::is_base_of<Immutable, T>::value
                ? IMMUTABLE
                : boost::is_base_of<Singleton, T>::value
                    ? SINGLETON
                    : OBJECT
        : PRIMITIVE>
class Type {
 public:
    LIBJ_TYPE_ID();
};

template<typename T>
class Type<T, OBJECT> {
 public:
    typedef LIBJ_PTR_TYPE(T) Ptr;
    typedef LIBJ_CPTR_TYPE(T) Cptr;
    LIBJ_TYPE_ID();
};

template<typename T>
class Type<T, MUTABLE> {
 public:
    typedef LIBJ_PTR_TYPE(T) Ptr;
    typedef LIBJ_CPTR_TYPE(T) Cptr;
    LIBJ_TYPE_ID();
};

template<typename T>
class Type<T, IMMUTABLE> {
 public:
    typedef LIBJ_CPTR_TYPE(T) Cptr;
    LIBJ_TYPE_ID();
};

template<typename T>
class Type<T, SINGLETON> {
 public:
    typedef LIBJ_PTR_TYPE(T) Ptr;
    typedef LIBJ_CPTR_TYPE(T) Cptr;
    LIBJ_TYPE_ID();
};

}  // namespace libj

#endif  // LIBJ_TYPE_H_
