// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPE_H_
#define LIBJ_TYPE_H_

#include <libj/detail/type.h>

namespace libj {

#ifdef LIBJ_USE_CXX11
template <typename T, detail::Category =
    std::is_base_of<detail::MutableBase, T>::value
        ? detail::MUTABLE
        : std::is_base_of<detail::ImmutableBase, T>::value
            ? detail::IMMUTABLE
            : std::is_base_of<detail::SingletonBase, T>::value
                ? detail::SINGLETON
                : std::is_base_of<detail::ObjectBase, T>::value
                    ? detail::OBJECT
                    : detail::PRIMITIVE>
#else
template <typename T, detail::Category =
    boost::is_base_of<detail::MutableBase, T>::value
        ? detail::MUTABLE
        : boost::is_base_of<detail::ImmutableBase, T>::value
            ? detail::IMMUTABLE
            : boost::is_base_of<detail::SingletonBase, T>::value
                ? detail::SINGLETON
                : boost::is_base_of<detail::ObjectBase, T>::value
                    ? detail::OBJECT
                    : detail::PRIMITIVE>
#endif
class Type {
 public:
    typedef LIBJ_PTR_TYPE(T) Ptr;
    typedef LIBJ_CPTR_TYPE(T) CPtr;
    LIBJ_TYPE_ID_DEF;
};

template<typename T>
class Type<T, detail::IMMUTABLE> {
 public:
    typedef LIBJ_CPTR_TYPE(T) CPtr;
    LIBJ_TYPE_ID_DEF;
};

template<typename T>
class Type<T, detail::PRIMITIVE> {
 public:
    LIBJ_TYPE_ID_DEF;
};

}  // namespace libj

#endif  // LIBJ_TYPE_H_
