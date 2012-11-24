// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/set.h"
#include "libj/detail/generic_set.h"

namespace libj {

typedef detail::GenericSet<Value, Set> ValueSet;

class SetImpl : public ValueSet {
 public:
    static Ptr create() {
        return Ptr(new SetImpl());
    }

    Boolean add(const Value& v) {
        return ValueSet::addTyped(v);
    }

    Boolean remove(const Value& v) {
        return ValueSet::removeTyped(v);
    }
};

Set::Ptr Set::create() {
    return SetImpl::create();
}

}  // namespace libj
