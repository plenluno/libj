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

class ObjectBase {};
class MutableBase {};
class ImmutableBase {};
class SingletonBase {};

#define LIBJ_TYPE_ID() static TypeId id() { \
    static char c; \
    return reinterpret_cast<TypeId>(&c); \
}

template <typename T, Category =
    boost::is_base_of<MutableBase, T>::value
        ? MUTABLE
        : boost::is_base_of<ImmutableBase, T>::value
            ? IMMUTABLE
            : boost::is_base_of<SingletonBase, T>::value
                ? SINGLETON
                : boost::is_base_of<ObjectBase, T>::value
                    ? OBJECT
                    : PRIMITIVE>
class Type {
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
class Type<T, PRIMITIVE> {
 public:
    LIBJ_TYPE_ID();
};

template<class T>
class Classify
{
private:
    typedef char Yes;
    typedef struct { char v[2]; } No;

    static Yes object_(Type<ObjectBase>::Cptr);
    static No  object_(...);
    static Yes mutable_(Type<MutableBase>::Cptr);
    static No  mutable_(...);
    static Yes immutable_(Type<ImmutableBase>::Cptr);
    static No  immutable_(...);
    static Yes singleton_(Type<SingletonBase>::Cptr);
    static No  singleton_(...);
    static Yes cptr_(...);
    static No  cptr_(Type<ObjectBase>::Ptr);

    static T t;

public:
    static const bool isObject = (sizeof(object_(t)) == sizeof(Yes));
    static const bool isMutable = (sizeof(mutable_(t)) == sizeof(Yes));
    static const bool isImmutable = (sizeof(immutable_(t)) == sizeof(Yes));
    static const bool isSingleton = (sizeof(singleton_(t)) == sizeof(Yes));
    static const bool isCptr = (sizeof(cptr_(t)) == sizeof(Yes) &&
                                sizeof(object_(t)) == sizeof(Yes));
};

}  // namespace libj

#endif  // LIBJ_TYPE_H_
