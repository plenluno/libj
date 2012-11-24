// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_LINKED_LIST_H_
#define LIBJ_TYPED_LINKED_LIST_H_

#include "libj/linked_list.h"
#include "libj/typed_list.h"
#include "libj/detail/generic_linked_list.h"

namespace libj {

template<typename T>
class TypedLinkedList
    : public detail::GenericLinkedList<T, TypedList<T, LinkedList> > {
 public:
    LIBJ_MUTABLE_TEMPLATE_DEFS(TypedLinkedList, LinkedList);

    static Ptr create() {
        return Ptr(new TypedLinkedList());
    }

    static Ptr create(Collection::CPtr c) {
        Ptr list(new TypedLinkedList());
        Iterator::Ptr itr = c->iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            T t;
            if (detail::convert<T>(v, &t)) {
                list->addTyped(t);
            } else {
                return null();
            }
        }
        return list;
    }

    virtual Value subList(Size from, Size to) const {
        if (to > this->size() || from > to) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }

        TypedLinkedList* list(new TypedLinkedList());
        for (Size i = from; i < to; i++) {
            list->addTyped(this->getTyped(i));
        }
        return Ptr(list);
    }
};

}  // namespace libj

#endif  // LIBJ_TYPED_LINKED_LIST_H_
