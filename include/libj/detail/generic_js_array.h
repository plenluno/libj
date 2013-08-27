// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GENERIC_JS_ARRAY_H_
#define LIBJ_DETAIL_GENERIC_JS_ARRAY_H_

#include <libj/js_object.h>
#include <libj/detail/generic_array_list.h>

namespace libj {
namespace detail {

template<typename I, typename T>
class GenericJsArray : public GenericArrayList<I, T> {
 public:
    GenericJsArray() : obj_(libj::JsObject::null()) {}

    virtual Value subList(Size from, Size to) const {
        if (to > this->size() || from > to) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }

        GenericJsArray* a = new GenericJsArray();
        for (Size i = from; i < to; i++) {
            a->addTyped(this->getTyped(i));
        }
        return typename GenericArrayList<I, T>::Ptr(a);
    }

    virtual String::CPtr toString() const {
        libj::StringBuilder::Ptr sb = libj::StringBuilder::create();
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
                sb->append(v);
        }
        return sb->toString();
    }

 public:
    virtual Boolean hasProperty(const Value& name) const {
        if (obj_) {
            return obj_->hasProperty(name);
        } else {
            return false;
        }
    }

    virtual Value getProperty(const Value& name) const {
        if (obj_) {
            return obj_->getProperty(name);
        } else {
            return UNDEFINED;
        }
    }

    virtual Value setProperty(const Value& name, const Value& val) {
        if (!obj_) {
            obj_ = libj::JsObject::create();
        }
        return obj_->setProperty(name, val);
    }

    virtual Value deleteProperty(const Value& name) {
        if (obj_) {
            return obj_->deleteProperty(name);
        } else {
            return UNDEFINED;
        }
    }

 private:
    libj::JsObject::Ptr obj_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_GENERIC_JS_ARRAY_H_
