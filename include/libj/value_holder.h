// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_VALUE_HOLDER_H_
#define LIBJ_VALUE_HOLDER_H_

#include "libj/mutable.h"
#include "libj/value.h"

namespace libj {

class ValueHolder : LIBJ_MUTABLE(ValueHolder)
 public:
    static Ptr create(const Value& v);

    virtual Value get() const = 0;
    virtual void set(const Value& val) = 0;

    template<typename T>
    typename Type<T>::Ptr getPtr() const {
        typename Type<T>::Ptr p = toPtr<T>(get());
        return p;
    }

    template<typename T>
    typename Type<T>::CPtr getCPtr() const {
        typename Type<T>::CPtr p = toCPtr<T>(get());
        return p;
    }
};

}  // namespace libj

#endif  // LIBJ_VALUE_HOLDER_H_
