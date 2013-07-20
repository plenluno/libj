// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_ARRAY_LIST_H_
#define LIBJ_DETAIL_ARRAY_LIST_H_

#include <libj/detail/generic_array_list.h>

namespace libj {
namespace detail {

template<typename I>
class ArrayList : public GenericArrayList<I, Value> {
 public:
    virtual Boolean add(const Value& v) {
        return GenericArrayList<I, Value>::addTyped(v);
    }

    virtual Boolean add(Size i, const Value& v) {
        return GenericArrayList<I, Value>::addTyped(i, v);
    }

    virtual Boolean set(Size i, const Value& v) {
        return GenericArrayList<I, Value>::setTyped(i, v);
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_ARRAY_LIST_H_
