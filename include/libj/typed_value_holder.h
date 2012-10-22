// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_VALUE_HOLDER_H_
#define LIBJ_TYPED_VALUE_HOLDER_H_

#include "libj/mutable.h"
#include "libj/string.h"

namespace libj {

template<typename T>
class TypedValueHolder : LIBJ_MUTABLE_TEMPLATE(TypedValueHolder)
 public:
    static Ptr create(const T& val) {
        return Ptr(new TypedValueHolder(val));
    }

    virtual T get() const {
        return val_;
    }

    virtual void set(const T& val) {
        val_ = val;
    }

    virtual String::CPtr toString() const {
        return String::valueOf(val_);
    }

 private:
    T val_;

    TypedValueHolder(const T& val) : val_(val) {}
};

}  // namespace libj

#endif  // LIBJ_TYPED_VALUE_HOLDER_H_
