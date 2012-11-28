// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_VALUE_HOLDER_H_
#define LIBJ_TYPED_VALUE_HOLDER_H_

#include <libj/value_holder.h>
#include <libj/detail/generic_value_holder.h>

namespace libj {

template<typename T>
class TypedValueHolder
    : public detail::GenericValueHolder<T, ValueHolder> {
 public:
    LIBJ_MUTABLE_TEMPLATE_DEFS(TypedValueHolder, ValueHolder);

    static Ptr create(const T& val);
};

}  // namespace libj

#include <libj/impl/typed_value_holder.h>

#endif  // LIBJ_TYPED_VALUE_HOLDER_H_
