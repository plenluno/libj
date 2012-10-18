// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_VALUE_HOLDER_H_
#define LIBJ_VALUE_HOLDER_H_

#include "libj/mutable.h"
#include "libj/value.h"

namespace libj {

class ValueHolder : LIBJ_MUTABLE(ValueHolder)
 public:
    static Ptr create(const Value& val) {
        return Ptr(new ValueHolder(val));
    }

    virtual Value get() const {
        return val_;
    }

    virtual void set(const Value& val) {
        val_ = val;
    }

    virtual String::CPtr toString() const {
        return String::valueOf(val_);
    }

    template<typename T>
    typename Type<T>::Ptr getPtr() const {
        return toPtr<T>(get());
    }

    template<typename T>
    typename Type<T>::CPtr getCPtr() const {
        return toCPtr<T>(get());
    }

 private:
    Value val_;

    ValueHolder(const Value& val) : val_(val) {}
};

}  // namespace libj

#endif  // LIBJ_VALUE_HOLDER_H_
