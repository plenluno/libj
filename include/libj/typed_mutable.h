// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_MUTABLE_H_
#define LIBJ_TYPED_MUTABLE_H_

#include <libj/mutable.h>

namespace libj {

template<typename M, typename T>
class TypedMutable : public M {};

}  // namespace libj

#define LIBJ_TYPED_MUTABLE(M, T) \
    public detail::Generic##M<TypedMutable<M, T>, T> { \
    LIBJ_MUTABLE_TEMPLATE_DEFS(Typed##M, M)

#define LIBJ_TYPED_MUTABLE_IF(M, T) \
    public TypedMutable<M, T> { \
    LIBJ_MUTABLE_TEMPLATE_DEFS(Typed##M, M)

#endif  // LIBJ_TYPED_MUTABLE_H_
