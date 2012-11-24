// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_LINKED_LIST_H_
#define LIBJ_DETAIL_LINKED_LIST_H_

#include "libj/linked_list.h"

#include "./generic_linked_list.h"

namespace libj {
namespace detail {

template<typename I>
class LinkedList : public GenericLinkedList<Value, I> {
 public:
    virtual Boolean add(const Value& v) {
        return this->addTyped(v);
    }

    virtual Boolean add(Size i, const Value& v) {
        return this->addTyped(i, v);
    }

    virtual Boolean set(Size i, const Value& v) {
        return this->setTyped(i, v);
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_LINKED_LIST_H_
