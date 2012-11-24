// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_JS_ARRAY_H_
#define LIBJ_TYPED_JS_ARRAY_H_

#include "libj/js_array.h"
#include "libj/typed_list.h"
#include "libj/detail/generic_js_array.h"

namespace libj {

template<typename T>
class TypedJsArray
    : public detail::GenericJsArray<T, TypedList<T, JsArray> > {
 public:
    LIBJ_MUTABLE_TEMPLATE_DEFS(TypedJsArray, JsArray);

    static Ptr create() {
        return Ptr(new TypedJsArray());
    }

    static Ptr create(Collection::CPtr c) {
        Ptr ary(new TypedJsArray());
        Iterator::Ptr itr = c->iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            T t;
            if (detail::convert<T>(v, &t)) {
                ary->addTyped(t);
            } else {
                return null();
            }
        }
        return ary;
    }

    virtual Value subList(Size from, Size to) const {
        if (to > this->size() || from > to) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }

        TypedJsArray* ary(new TypedJsArray());
        for (Size i = from; i < to; i++) {
            ary->addTyped(this->getTyped(i));
        }
        return Ptr(ary);
    }

    Ptr subarray(Size from, Size to = NO_POS) const {
        to = to > this->size() ? this->size() : to;
        if (from >= to) {
            return Ptr(new TypedJsArray());
        }

        TypedJsArray* ary(new TypedJsArray());
        for (Size i = from; i < to; i++) {
            ary->addTyped(this->getTyped(i));
        }
        return Ptr(ary);
    }
};

}  // namespace libj

#endif  // LIBJ_TYPED_JS_ARRAY_H_
