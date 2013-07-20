// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_MUTABLE_H_
#define LIBJ_TYPED_MUTABLE_H_

#include <libj/mutable.h>

namespace libj {

template<typename L, typename T>
class TypedMutable : public L {};

}  // namespace libj

#define LIBJ_TYPED_MUTABLE(L, T) \
    public detail::Generic##L<TypedMutable<L, T>, T> { \
    LIBJ_MUTABLE_TEMPLATE_DEFS(Typed##L, L)

#endif  // LIBJ_TYPED_MUTABLE_H_
