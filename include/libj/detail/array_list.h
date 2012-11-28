// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_ARRAY_LIST_H_
#define LIBJ_DETAIL_ARRAY_LIST_H_

#include <libj/detail/generic_array_list.h>

namespace libj {
namespace detail {

template<typename I>
class ArrayList : public GenericArrayList<Value, I> {
 public:
    virtual Boolean add(const Value& v) {
        return GenericArrayList<Value, I>::addTyped(v);
    }

    virtual Boolean add(Size i, const Value& v) {
        return GenericArrayList<Value, I>::addTyped(i, v);
    }

    virtual Boolean set(Size i, const Value& v) {
        return GenericArrayList<Value, I>::setTyped(i, v);
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_ARRAY_LIST_H_
