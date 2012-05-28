// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_ARRAY_LIST_H_
#define LIBJ_TYPED_ARRAY_LIST_H_

#include "libj/array_list.h"

namespace libj {

template<typename T>
class TypedArrayList : public libj::ArrayList {
    virtual T getTyped(Size) const = 0;
};

}  // namespace libj

#endif  // LIBJ_TYPED_ARRAY_LIST_H_
