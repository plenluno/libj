// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPE_H_
#define LIBJ_TYPE_H_

#include <libj/pointer.h>
#include <libj/typedef.h>

#ifdef LIBJ_USE_CXX11
    #include <type_traits>
#else
    #include <boost/type_traits/is_base_of.hpp>
#endif

namespace libj {

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

#define LIBJ_TYPE_ID() static TypeId id() { \
    static char c; \
    return reinterpret_cast<TypeId>(&c); \
}

#ifdef LIBJ_USE_CXX11
template <typename T, Category =
    std::is_base_of<MutableBase, T>::value
        ? MUTABLE
        : std::is_base_of<ImmutableBase, T>::value
            ? IMMUTABLE
            : std::is_base_of<SingletonBase, T>::value
                ? SINGLETON
                : std::is_base_of<ObjectBase, T>::value
                    ? OBJECT
                    : PRIMITIVE>
#else
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
#endif
class Type {
 public:
    typedef LIBJ_PTR_TYPE(T) Ptr;
    typedef LIBJ_CPTR_TYPE(T) CPtr;
    LIBJ_TYPE_ID();
};

template<typename T>
class Type<T, IMMUTABLE> {
 public:
    typedef LIBJ_CPTR_TYPE(T) CPtr;
    LIBJ_TYPE_ID();
};

template<typename T>
class Type<T, PRIMITIVE> {
 public:
    LIBJ_TYPE_ID();
};

template<class T>
class Classify {
 private:
    typedef char Yes;
    typedef struct {
        char v[2];
    } No;

    static Yes object_(Type<ObjectBase>::CPtr);
    static No  object_(...);
    static Yes mutable_(Type<MutableBase>::CPtr);
    static No  mutable_(...);
    static Yes immutable_(Type<ImmutableBase>::CPtr);
    static No  immutable_(...);
    static Yes singleton_(Type<SingletonBase>::CPtr);
    static No  singleton_(...);
    static Yes cptr_(...);
    static No  cptr_(Type<ObjectBase>::Ptr);

    static T t;

 public:
    static const Boolean isObject = (sizeof(object_(t)) == sizeof(Yes));
    static const Boolean isMutable = (sizeof(mutable_(t)) == sizeof(Yes));
    static const Boolean isImmutable = (sizeof(immutable_(t)) == sizeof(Yes));
    static const Boolean isSingleton = (sizeof(singleton_(t)) == sizeof(Yes));
    static const Boolean isCPtr = (sizeof(cptr_(t)) == sizeof(Yes) &&
                                   sizeof(object_(t)) == sizeof(Yes));
};

}  // namespace libj

#endif  // LIBJ_TYPE_H_
