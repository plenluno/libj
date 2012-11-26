// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/value_holder.h"
#include "libj/detail/value_holder.h"

namespace libj {

ValueHolder::Ptr ValueHolder::create(const Value& val) {
    return Ptr(new detail::ValueHolder<ValueHolder>(val));
}

}  // namespace libj
