// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_SET_H_
#define LIBJ_TYPED_SET_H_

#include <libj/set.h>
#include <libj/detail/generic_set.h>

namespace libj {

template<typename T>
class TypedSet : public detail::GenericSet<T, Set> {
 public:
    LIBJ_MUTABLE_TEMPLATE_DEFS(TypedSet, Set);

    static Ptr create();
};

}  // namespace libj

#include <libj/impl/typed_set.h>

#endif  // LIBJ_TYPED_SET_H_
