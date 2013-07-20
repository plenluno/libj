// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_LINKED_LIST_H_
#define LIBJ_DETAIL_LINKED_LIST_H_

#include <libj/detail/generic_linked_list.h>

namespace libj {
namespace detail {

template<typename I>
class LinkedList : public GenericLinkedList<I, Value> {
 public:
    virtual Boolean add(const Value& v) {
        return GenericLinkedList<I, Value>::addTyped(v);
    }

    virtual Boolean add(Size i, const Value& v) {
        return GenericLinkedList<I, Value>::addTyped(i, v);
    }

    virtual Boolean set(Size i, const Value& v) {
        return GenericLinkedList<I, Value>::setTyped(i, v);
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_LINKED_LIST_H_
