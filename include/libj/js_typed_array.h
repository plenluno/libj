// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_TYPED_ARRAY_H_
#define LIBJ_JS_TYPED_ARRAY_H_

#include "libj/js_array.h"
#include "libj/js_property.h"
#include "libj/typed_array_list.h"

namespace libj {

template<typename T>
class JsTypedArray : LIBJ_TYPED_ARRAY_LIST_TEMPLATE(JsTypedArray, T)
 public:
    static Ptr create() {
        return Ptr(new JsTypedArray());
    }

    static Ptr create(JsArray::CPtr a) {
        JsTypedArray* ary(new JsTypedArray());
        Iterator::Ptr itr = a->iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            if (ary->match(v)) {
                ary->list_->add(v);
            } else {
                return null();
            }
        }
        return Ptr(ary);
    }

    String::CPtr toString() const {
        static String::CPtr comma = String::create(",");

        StringBuffer::Ptr sb = StringBuffer::create();
        Iterator::Ptr itr = this->iterator();
        Boolean first = true;
        while (itr->hasNext()) {
            Value v = itr->next();
            if (first) {
                first = false;
            } else {
                sb->append(comma);
            }
            if (!v.isNull() && !v.isUndefined())
                sb->append(String::valueOf(v));
        }
        return sb->toString();
    }

    Value subList(Size from, Size to) const {
        if (to > this->list_->size() || from > to) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }

        JsTypedArray* ary(new JsTypedArray());
        for (Size i = from; i < to; i++) {
            ary->list_->add(this->list_->get(i));
        }
        return Ptr(ary);
    }

    Ptr subarray(Size from, Size to = NO_POS) const {
        to = to > this->list_->size() ? this->list_->size() : to;
        if (from >= to) {
            return Ptr(new JsTypedArray());
        }

        JsTypedArray* ary(new JsTypedArray());
        for (Size i = from; i < to; i++) {
            ary->list_->add(this->list_->get(i));
        }
        return Ptr(ary);
    }

    LIBJ_JS_PROPERTY_MIX(JsTypedArray);
};

}  // namespace libj

#endif  // LIBJ_JS_TYPED_ARRAY_H_
