// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_VALUE_HOLDER_H_
#define LIBJ_VALUE_HOLDER_H_

#include <libj/mutable.h>
#include <libj/string.h>
#include <libj/value.h>

namespace libj {

class ValueHolder : LIBJ_MUTABLE(ValueHolder)
 public:
    static Ptr create(const Value& val);

    virtual Value get() const = 0;

    virtual void set(const Value& val) = 0;

    template<typename T>
    typename Type<T>::Ptr getPtr() const;

    template<typename T>
    typename Type<T>::CPtr getCPtr() const;
};

}  // namespace libj

#include <libj/impl/value_holder.h>

#define LIBJ_VALUE_HOLDER_TEMPLATE(T) public libj::ValueHolder { \
    LIBJ_MUTABLE_TEMPLATE_DEFS(T, LIBJ_VALUE_HOLDER)

#endif  // LIBJ_VALUE_HOLDER_H_
