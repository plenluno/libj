// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_BRIDGE_ABSTRACT_LIST_H_
#define LIBJ_BRIDGE_ABSTRACT_LIST_H_

#include "libj/list.h"

#include "./abstract_collection.h"

namespace libj {
namespace bridge {

template<typename I>
class AbstractList : public AbstractCollection<I> {
 public:
    AbstractList(List::Ptr list)
        : AbstractCollection<I>(list)
        , list_(list) {}

    virtual Boolean add(const Value& v) {
        return list_->add(v);
    }

    virtual Boolean add(Size i, const Value& v) {
        return list_->add(i, v);
    }

    virtual Value get(Size i) const {
        return list_->get(i);
    }

    virtual Int indexOf(const Value& val) {
        return list_->indexOf(val);
    }

    virtual Int lastIndexOf(const Value& val) {
        return list_->lastIndexOf(val);
    }

    virtual Boolean remove(const Value& v) {
        return list_->remove(v);
    }

    virtual Value remove(Size i) {
        return list_->remove(i);
    }

    virtual Iterator::Ptr reverseIterator() const {
        return list_->reverseIterator();
    }

    virtual Boolean set(Size i, const Value& v) {
        return list_->set(i, v);
    }

 public:
    virtual Size length() const {
        return list_->length();
    }

    virtual Value shift() {
        return list_->shift();
    }

    virtual Size unshift(const Value& val) {
        return list_->unshift(val);
    }

    virtual Size push(const Value& val) {
        return list_->push(val);
    }

    virtual Value pop() {
        return list_->pop();
    }

 private:
    List::Ptr list_;
};

}  // namespace bridge
}  // namespace libj

#endif  // LIBJ_BRIDGE_ABSTRACT_LIST_H_
