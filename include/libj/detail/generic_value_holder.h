// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GENERIC_VALUE_HOLDER_H_
#define LIBJ_DETAIL_GENERIC_VALUE_HOLDER_H_

#include "libj/string.h"

#include "./util.h"

namespace libj {
namespace detail {

template<typename T, typename I>
class GenericValueHolder : public I {
 public:
    GenericValueHolder() {}

    GenericValueHolder(const T& t) : val_(t) {}

    virtual Value get() const {
        return val_;
    }

    virtual void set(const Value& v) {
        T t;
        if (convert<T>(v, &t)) {
            val_ = t;
        } else {
            LIBJ_THROW(Error::ILLEGAL_ARGUMENT);
        }
    }

    virtual T getTyped() const {
        return val_;
    }

    virtual void setTyped(const T& t) {
        val_ = t;
    }

    virtual String::CPtr toString() const {
        return String::valueOf(val_);
    }

 private:
    T val_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_GENERIC_VALUE_HOLDER_H_
