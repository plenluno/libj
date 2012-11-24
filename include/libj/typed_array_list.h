// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_ARRAY_LIST_H_
#define LIBJ_TYPED_ARRAY_LIST_H_

#include "libj/array_list.h"
#include "libj/typed_list.h"
#include "libj/detail/generic_array_list.h"

namespace libj {

template<typename T>
class TypedArrayList
    : public detail::GenericArrayList<T, TypedList<T, ArrayList> > {
 public:
    LIBJ_MUTABLE_TEMPLATE_DEFS(TypedArrayList, ArrayList);

    static Ptr create() {
        return Ptr(new TypedArrayList());
    }

    static Ptr create(Collection::CPtr c) {
        Ptr list(new TypedArrayList());
        Iterator::Ptr itr = c->iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            T t;
            if (detail::convert<T>(v, &t)) {
                list->addTyped(t);
            } else {
                return null();
            }
        }
        return list;
    }

    virtual Value subList(Size from, Size to) const {
        if (to > this->size() || from > to) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }

        TypedArrayList* list(new TypedArrayList());
        for (Size i = from; i < to; i++) {
            list->addTyped(this->getTyped(i));
        }
        return Ptr(list);
    }
};

}  // namespace libj

#endif  // LIBJ_TYPED_ARRAY_LIST_H_
