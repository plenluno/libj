// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/error.h"
#include "libj/exception.h"
#include "libj/js_array.h"
#include "libj/js_object.h"

namespace libj {

class JsArrayImpl : public JsArray {
 public:
    static Ptr create() {
        Ptr p(new JsArrayImpl());
        return p;
    }

 private:
    JsObject::Ptr obj_;
    ArrayList::Ptr ary_;

    JsArrayImpl()
        : obj_(JsObject::create())
        , ary_(ArrayList::create()) {}

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
        static String::CPtr comma = String::create(",");
        StringBuffer::Ptr sb = StringBuffer::create();
        Iterator::Ptr itr = iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            if (sb->length())
                sb->append(comma);
            sb->append(String::valueOf(v));
        }
        return sb->toString();
    }

    LIBJ_LIST_IMPL(ary_);
    LIBJ_JS_PROPERTY_IMPL(obj_);
};

JsArray::Ptr JsArray::create() {
    return JsArrayImpl::create();
}

JsArray::Ptr JsArray::create(ArrayList::CPtr list) {
    JsArray::Ptr ary = JsArray::create();
    ary->addAll(list);
    return ary;
}

}  // namespace libj
