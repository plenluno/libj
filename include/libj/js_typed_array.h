// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_TYPED_ARRAY_H_
#define LIBJ_JS_TYPED_ARRAY_H_

#include "libj/js_array.h"
#include "libj/js_property.h"
#include "libj/typed_array_list.h"

namespace libj {

template<typename T>
class JsTypedArray
    : public JsPropertyMixin
    , LIBJ_TYPED_ARRAY_LIST_TEMPLATE(JsTypedArray, T)
 public:
    static Ptr create() {
        return Ptr(new JsTypedArray());
    }

    static Ptr create(Collection::CPtr c) {
        Ptr ary(new JsTypedArray());
        Iterator::Ptr itr = c->iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            T t;
            if (GenericArrayList<T>::convert(v, &t)) {
                ary->addTyped(t);
            } else {
                return null();
            }
        }
        return ary;
    }

    String::CPtr toString() const {
        StringBuffer::Ptr sb = StringBuffer::create();
        Iterator::Ptr itr = this->iterator();
        Boolean first = true;
        while (itr->hasNext()) {
            Value v = itr->next();
            if (first) {
                first = false;
            } else {
                sb->appendChar(',');
            }
            if (!v.isNull() && !v.isUndefined())
                sb->append(String::valueOf(v));
        }
        return sb->toString();
    }

    Value subList(Size from, Size to) const {
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
