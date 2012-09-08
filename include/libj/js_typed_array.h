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
        Ptr p(new JsTypedArray());
        return p;
    }

    static Ptr create(JsArray::CPtr a) {
        Ptr p(new JsTypedArray());
        Iterator::Ptr itr = a->iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            if (p->match(v)) {
                p->list_->add(v);
            } else {
                return null();
            }
        }
        return p;
    }

    String::CPtr toString() const {
        static String::CPtr comma = String::create(",");
        StringBuffer::Ptr sb = StringBuffer::create();
        Iterator::Ptr itr = this->iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            if (sb->length())
                sb->append(comma);
            sb->append(String::valueOf(v));
        }
        return sb->toString();
    }

    Value subList(Size from, Size to) const {
        if (to > this->list_->size() || from > to) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }

        Ptr p(new JsTypedArray());
        for (Size i = from; i < to; i++) {
            p->list_->add(this->list_->get(i));
        }
        return p;
    }

    Ptr subarray(Size from, Size to = NO_POS) const {
        to = to > this->list_->size() ? this->list_->size() : to;
        if (from >= to) {
            Ptr p(new JsTypedArray());
            return p;
        }

        Ptr p(new JsTypedArray());
        for (Size i = from; i < to; i++) {
            p->list_->add(this->list_->get(i));
        }
        return p;
    }

    LIBJ_JS_PROPERTY_MIX(JsTypedArray);
};

}  // namespace libj

#endif  // LIBJ_JS_TYPED_ARRAY_H_
