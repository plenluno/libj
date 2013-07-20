// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_SET_H_
#define LIBJ_TYPED_SET_H_

#include <libj/set.h>
#include <libj/typed_collection.h>
#include <libj/detail/generic_set.h>

namespace libj {

template<typename T>
class TypedSet : LIBJ_TYPED_COLLECTION(Set, T)
 public:
    static Ptr create();
};

}  // namespace libj

#include <libj/impl/typed_set.h>

#endif  // LIBJ_TYPED_SET_H_
