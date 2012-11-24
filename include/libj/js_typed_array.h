// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_TYPED_ARRAY_H_
#define LIBJ_JS_TYPED_ARRAY_H_

#include "libj/js_array.h"
#include "libj/typed_list.h"
#include "libj/detail/generic_js_array.h"

namespace libj {

template<typename T>
class JsTypedArray
    : public detail::GenericJsArray<T, TypedList<T, JsArray> > {
 public:
    LIBJ_MUTABLE_TEMPLATE_DEFS(JsTypedArray, JsArray);

    static Ptr create() {
        return Ptr(new JsTypedArray());
    }

    static Ptr create(Collection::CPtr c) {
        Ptr ary(new JsTypedArray());
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

        JsTypedArray* ary(new JsTypedArray());
        for (Size i = from; i < to; i++) {
            ary->addTyped(this->getTyped(i));
        }
        return Ptr(ary);
    }

    Ptr subarray(Size from, Size to = NO_POS) const {
        to = to > this->size() ? this->size() : to;
        if (from >= to) {
            return Ptr(new JsTypedArray());
        }

        JsTypedArray* ary(new JsTypedArray());
        for (Size i = from; i < to; i++) {
            ary->addTyped(this->getTyped(i));
        }
        return Ptr(ary);
    }
};

}  // namespace libj

#endif  // LIBJ_JS_TYPED_ARRAY_H_
