// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_VALUE_HOLDER_H_
#define LIBJ_VALUE_HOLDER_H_

#include "libj/mutable.h"
#include "libj/value.h"

namespace libj {

class ValueHolder : LIBJ_MUTABLE(ValueHolder)
 public:
    static Ptr create(const Value& val);

    virtual Value get() const = 0;

    virtual void set(const Value& val) = 0;

 public:
    template<typename T>
    typename Type<T>::Ptr getPtr() const {
        return toPtr<T>(get());
    }

    template<typename T>
    typename Type<T>::CPtr getCPtr() const {
        return toCPtr<T>(get());
    }
};

}  // namespace libj

#endif  // LIBJ_VALUE_HOLDER_H_
