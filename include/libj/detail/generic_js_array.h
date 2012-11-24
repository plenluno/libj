// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GENERIC_JS_ARRAY_H_
#define LIBJ_DETAIL_GENERIC_JS_ARRAY_H_

#include "./generic_array_list.h"

namespace libj {
namespace detail {

template<typename T, typename I>
class GenericJsArray : public GenericArrayList<T, I> {
 public:
    virtual Value subList(Size from, Size to) const {
        if (to > this->size() || from > to) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }

        GenericJsArray* a = new GenericJsArray();
        for (Size i = from; i < to; i++) {
            a->addTyped(this->getTyped(i));
        }
        return typename GenericArrayList<T, I>::Ptr(a);
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

#endif  // LIBJ_DETAIL_GENERIC_JS_ARRAY_H_
