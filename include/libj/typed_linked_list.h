// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_LINKED_LIST_H_
#define LIBJ_TYPED_LINKED_LIST_H_

#include <libj/linked_list.h>
#include <libj/typed_list.h>
#include <libj/detail/generic_linked_list.h>

namespace libj {

template<typename T>
class TypedLinkedList
    : public detail::GenericLinkedList<T, TypedList<T, LinkedList> > {
 public:
    LIBJ_MUTABLE_TEMPLATE_DEFS(TypedLinkedList, LinkedList);

    static Ptr create();

    static Ptr create(Collection::CPtr c);

    virtual Value subList(Size from, Size to) const;
};

}  // namespace libj

#include <libj/impl/typed_linked_list.h>

#endif  // LIBJ_TYPED_LINKED_LIST_H_
