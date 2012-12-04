// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_SINGLETON_H_
#define LIBJ_IMPL_SINGLETON_H_

namespace libj {

inline Singleton::Ptr Singleton::null() {
    static LIBJ_NULL_PTR_DEF(Singleton, nullp);
    return nullp;
}

template<typename T>
class SingletonTmpl : public Singleton {
 public:
    typedef LIBJ_PTR_TYPE(T) Ptr;
    typedef LIBJ_CPTR_TYPE(T) CPtr;

    static Ptr null() {
        static LIBJ_NULL_PTR_TYPE_DEF(T, nullp);
        return nullp;
    }

    static Ptr instance() {
        static T t;
        LIBJ_SINGLETON_PTR_TYPE_DEF(T, p, &t);
        return p;
    }

    virtual TypeId type() const {
        return Type<T>::id();
    }

    virtual Boolean instanceof(TypeId id) const {
        return id == type()
            || id == Type<Singleton>::id()
            || Object::instanceof(id);
    }

 protected:
    SingletonTmpl() {}
    virtual ~SingletonTmpl() {}
};

}  // namespace libj

#define LIBJ_SINGLETON_DEFS(T) public libj::SingletonTmpl<T> { \
private: \
    friend class libj::SingletonTmpl<T>; \
    T() : libj::SingletonTmpl<T>() {} \
    virtual ~T() {}

#endif  // LIBJ_IMPL_SINGLETON_H_
