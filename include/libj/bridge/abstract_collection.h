// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_BRIDGE_ABSTRACT_COLLECTION_H_
#define LIBJ_BRIDGE_ABSTRACT_COLLECTION_H_

#include <libj/collection.h>

namespace libj {
namespace bridge {

template<typename I>
class AbstractCollection : public I {
 public:
    AbstractCollection(Collection::Ptr c) : collection_(c) {}

    virtual Boolean add(const Value& v) {
        return collection_->add(v);
    }

    virtual Boolean addAll(Collection::CPtr c) {
        return collection_->addAll(c);
    }

    virtual void clear() {
        collection_->clear();
    }

    virtual Boolean contains(const Value& v) const {
        return collection_->contains(v);
    }

    virtual Boolean containsAll(Collection::CPtr c) const {
        return collection_->containsAll(c);
    }

    virtual Boolean isEmpty() const {
        return collection_->isEmpty();
    }

    virtual Iterator::Ptr iterator() const {
        return collection_->iterator();
    }

    virtual Boolean remove(const Value& v) {
        return collection_->remove(v);
    }

    virtual Boolean removeAll(Collection::CPtr c) {
        return collection_->removeAll(c);
    }

    virtual Boolean retainAll(Collection::CPtr c) {
        return collection_->retainAll(c);
    }

    virtual Size size() const {
        return collection_->size();
    }

 private:
    Collection::Ptr collection_;
};

}  // namespace bridge
}  // namespace libj

#endif  // LIBJ_BRIDGE_ABSTRACT_COLLECTION_H_
