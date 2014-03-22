// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_ARRAY_LIST_H_
#define LIBJ_ARRAY_LIST_H_

#include <libj/list.h>

namespace libj {

class ArrayList : LIBJ_LIST(ArrayList)
 public:
    static Ptr create();
};

}  // namespace libj

#include <libj/impl/array_list.h>

#define LIBJ_ARRAY_LIST(T) public libj::ArrayList { \
    LIBJ_MUTABLE_DEFS(T, LIBJ_ARRAY_LIST)

#define LIBJ_ARRAY_LIST_TEMPLATE(T) public libj::ArrayList { \
    LIBJ_MUTABLE_TEMPLATE_DEFS(T, LIBJ_ARRAY_LIST)

#endif  // LIBJ_ARRAY_LIST_H_
