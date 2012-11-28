// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_TYPE_H_
#define LIBJ_DETAIL_TYPE_H_

#include <libj/typedef.h>
#include <libj/detail/pointer.h>

#ifdef LIBJ_USE_CXX11
    #include <type_traits>
#else
    #include <boost/type_traits/is_base_of.hpp>
#endif

namespace libj {
namespace detail {

enum Category {
    PRIMITIVE,
    OBJECT,
    MUTABLE,
    IMMUTABLE,
    SINGLETON,
};

enum TypeCompre {
    TYPE_CMP_SAME        = 1,
    TYPE_CMP_DERIVED     = 2,
    TYPE_CMP_NOT_DERIVED = 3,
    TYPE_CMP_NA          = 4,
};

class ObjectBase {};
class MutableBase {};
class ImmutableBase {};
class SingletonBase {};

}  // namespace detail
}  // namespace libj

#define LIBJ_TYPE_ID_DEF \
static TypeId id() { \
    static char c; \
    return reinterpret_cast<TypeId>(&c); \
}

#endif  // LIBJ_DETAIL_TYPE_H_
