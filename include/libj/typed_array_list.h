// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_ARRAY_LIST_H_
#define LIBJ_TYPED_ARRAY_LIST_H_

#include <libj/array_list.h>
#include <libj/typed_list.h>
#include <libj/detail/generic_array_list.h>

namespace libj {

template<typename T>
class TypedArrayList
    : public detail::GenericArrayList<T, TypedList<T, ArrayList> > {
 public:
    LIBJ_MUTABLE_TEMPLATE_DEFS(TypedArrayList, ArrayList);

    static Ptr create();

    static Ptr create(Collection::CPtr c);

    virtual Value subList(Size from, Size to) const;
};

}  // namespace libj

#include <libj/impl/typed_array_list.h>

#endif  // LIBJ_TYPED_ARRAY_LIST_H_
