// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_VALUE_HOLDER_H_
#define LIBJ_DETAIL_VALUE_HOLDER_H_

#include <libj/detail/generic_value_holder.h>

namespace libj {
namespace detail {

template<typename I>
class ValueHolder : public GenericValueHolder<I, Value> {
 public:
    ValueHolder(const Value& val) : GenericValueHolder<I, Value>(val) {}

    virtual Value get() const {
        return GenericValueHolder<I, Value>::getTyped();
    }

    virtual void set(const Value& v) {
        GenericValueHolder<I, Value>::setTyped(v);
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_VALUE_HOLDER_H_
