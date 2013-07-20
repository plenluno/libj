// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_VALUE_HOLDER_H_
#define LIBJ_TYPED_VALUE_HOLDER_H_

#include <libj/value_holder.h>
#include <libj/typed_mutable.h>
#include <libj/detail/generic_value_holder.h>

namespace libj {

template<typename T>
class TypedValueHolder : LIBJ_TYPED_MUTABLE(ValueHolder, T)
 public:
    static Ptr create(const T& val);

    virtual T getTyped() const;

    virtual void setTyped(const T& t);
};

}  // namespace libj

#include <libj/impl/typed_value_holder.h>

#endif  // LIBJ_TYPED_VALUE_HOLDER_H_
