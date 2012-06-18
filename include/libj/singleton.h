// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_SINGLETON_H_
#define LIBJ_SINGLETON_H_

#include "libj/object.h"

namespace libj {

class Singleton
    : public Object
    , public SingletonBase {
 public:
    typedef LIBJ_PTR(Singleton) Ptr;
    typedef LIBJ_CPTR(Singleton) CPtr;
};

template<typename T>
class SingletonTmpl
    : public Singleton {
 public:
    static LIBJ_PTR_TYPE(T) instance() {
        static T t;
        LIBJ_SINGLETON_PTR_TYPE(T, p, &t);
        return p;
    }

    Boolean instanceof(TypeId id) const {
        return id == Type<Singleton>::id()
            || Object::instanceof(id);
    }

 protected:
    SingletonTmpl() {}
    virtual ~SingletonTmpl() {}
};

#define LIBJ_SINGLETON(T) public libj::SingletonTmpl<T> { \
private: \
    friend class libj::SingletonTmpl<T>; \
    T() : libj::SingletonTmpl<T>() {} \
    ~T() {} \
public: \
    typedef LIBJ_PTR(T) Ptr; \
    typedef LIBJ_CPTR(T) CPtr; \
    libj::TypeId type() const { \
        return libj::Type<T>::id(); \
    } \
    Boolean instanceof(libj::TypeId id) const { \
        return id == type() \
            || libj::SingletonTmpl<T>::instanceof(id); \
    }

}  // namespace libj

#endif  // LIBJ_SINGLETON_H_
