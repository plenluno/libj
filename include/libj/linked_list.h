// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_LINKED_LIST_H_
#define LIBJ_LINKED_LIST_H_

#include <libj/list.h>

namespace libj {

class LinkedList : LIBJ_LIST(LinkedList)
 public:
    static Ptr create();
};

}  // namespace libj

#include <libj/impl/linked_list.h>

#define LIBJ_LINKED_LIST(T) public libj::LinkedList { \
    LIBJ_MUTABLE_DEFS(T, LIBJ_LINKED_LIST)

#define LIBJ_LINKED_LIST_TEMPLATE(T) public libj::LinkedList { \
    LIBJ_MUTABLE_TEMPLATE_DEFS(T, LIBJ_LINKED_LIST)

#endif  // LIBJ_LINKED_LIST_H_
