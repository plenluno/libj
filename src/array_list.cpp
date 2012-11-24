// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/array_list.h"
#include "libj/detail/generic_array_list.h"

namespace libj {

typedef detail::GenericArrayList<Value, ArrayList> ValueArrayList;

class ArrayListImpl : public ValueArrayList {
 public:
    static Ptr create() {
        return Ptr(new ArrayListImpl());
    }

    virtual Boolean add(const Value& v) {
        return ValueArrayList::addTyped(v);
    }

    virtual Boolean add(Size i, const Value& v) {
        return ValueArrayList::addTyped(i, v);
    }

    virtual Boolean set(Size i, const Value& v) {
        return ValueArrayList::setTyped(i, v);
    }
};

ArrayList::Ptr ArrayList::create() {
    return ArrayListImpl::create();
}

}  // namespace libj
