// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/linked_list.h"
#include "libj/detail/generic_linked_list.h"

namespace libj {

typedef detail::GenericLinkedList<Value, LinkedList> ValueLinkedList;

class LinkedListImpl : public ValueLinkedList {
 public:
    static Ptr create() {
        return Ptr(new LinkedListImpl());
    }

    Boolean add(const Value& v) {
        return ValueLinkedList::addTyped(v);
    }

    Boolean add(Size i, const Value& v) {
        return ValueLinkedList::addTyped(i, v);
    }

    Boolean set(Size i, const Value& v) {
        return ValueLinkedList::setTyped(i, v);
    }
};

LinkedList::Ptr LinkedList::create() {
    return LinkedListImpl::create();
}

}  // namespace libj
