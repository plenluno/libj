// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_ARRAY_LIST_H_
#define LIBJ_ARRAY_LIST_H_

#include <libj/list.h>

namespace libj {

class ArrayList : LIBJ_LIST(ArrayList)
 public:
    static Ptr create();
};

#define LIBJ_ARRAY_LIST(T) public libj::ArrayList { \
    LIBJ_MUTABLE_DEFS(T, libj::ArrayList)

}  // namespace libj

#endif  // LIBJ_ARRAY_LIST_H_
