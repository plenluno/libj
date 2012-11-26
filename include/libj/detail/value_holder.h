// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_VALUE_HOLDER_H_
#define LIBJ_DETAIL_VALUE_HOLDER_H_

#include "./generic_value_holder.h"

namespace libj {
namespace detail {

template<typename I>
class ValueHolder : public GenericValueHolder<Value, I> {
 public:
    ValueHolder(const Value& val) : GenericValueHolder<Value, I>(val) {}

    virtual Value get() const {
        return GenericValueHolder<Value, I>::getTyped();
    }

    virtual void set(const Value& v) {
        GenericValueHolder<Value, I>::setTyped(v);
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_VALUE_HOLDER_H_
