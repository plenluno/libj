// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_JS_ARRAY_H_
#define LIBJ_DETAIL_JS_ARRAY_H_

#include "libj/js_array.h"

#include "./array_list.h"

namespace libj {
namespace detail {

template<typename I>
class JsArray : public ArrayList<I> {
 public:
    virtual Value subList(Size from, Size to) const {
        if (to > this->size() || from > to) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }

        typename ArrayList<I>::Ptr a = JsArray::create();
        for (Size i = from; i < to; i++) {
            a->add(this->get(i));
        }
        return a;
    }

 	virtual String::CPtr toString() const {
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
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_ARRAY_LIST_H_
