// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_CLASSIFY_H_
#define LIBJ_DETAIL_CLASSIFY_H_

#include <libj/type.h>

namespace libj {
namespace detail {

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

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_CLASSIFY_H_
