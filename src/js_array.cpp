// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/exception.h"
#include "libj/js_array.h"
#include "libj/js_object.h"

namespace libj {

class JsArrayImpl : public JsArray {
 public:
    static Ptr create() {
        return Ptr(new JsArrayImpl());
    }

 private:
    ArrayList::Ptr ary_;

    JsArrayImpl() : ary_(ArrayList::create()) {}

    Value subList(Size from, Size to) const {
        if (to > size() || from > to) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }

        JsArray::Ptr a = JsArray::create();
        for (Size i = from; i < to; i++) {
            a->add(get(i));
        }
        return a;
    }

    String::CPtr toString() const {
        StringBuffer::Ptr sb = StringBuffer::create();
        Iterator::Ptr itr = iterator();
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

    LIBJ_LIST_IMPL(ary_);
};

JsArray::Ptr JsArray::create() {
    return JsArrayImpl::create();
}

JsArray::Ptr JsArray::create(ArrayList::CPtr list) {
    if (!list) return null();

    JsArray::Ptr ary = JsArray::create();
    ary->addAll(list);
    return ary;
}

}  // namespace libj
