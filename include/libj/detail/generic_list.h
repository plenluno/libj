// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GENERIC_LIST_H_
#define LIBJ_DETAIL_GENERIC_LIST_H_

#include <libj/detail/generic_collection.h>

namespace libj {
namespace detail {

template<typename I, typename T>
class GenericList : public GenericCollection<I, T> {
 public:
    virtual Size size() const = 0;

    virtual Boolean add(const Value& v) = 0;

    virtual Boolean addTyped(const T& t) = 0;

    virtual Boolean add(Size i, const Value& v) = 0;

    virtual Boolean addTyped(Size i, const T& t) = 0;

    virtual Boolean set(Size i, const Value& v) = 0;

    virtual Boolean setTyped(Size i, const T& t) = 0;

    virtual Value get(Size i) const = 0;

    virtual T getTyped(Size i) const = 0;

    virtual Value remove(Size i) = 0;

    virtual T removeTyped(Size i) = 0;

    virtual Boolean remove(const Value& v) = 0;

    virtual Boolean removeTyped(const T& t) = 0;

    virtual Value subList(Size from, Size to) const = 0;

    virtual Iterator::Ptr iterator() const = 0;

    virtual Iterator::Ptr reverseIterator() const = 0;

    virtual typename TypedIterator<T>::Ptr iteratorTyped() const = 0;

    virtual typename TypedIterator<T>::Ptr reverseIteratorTyped() const = 0;

 public:
    virtual Size length() const {
        return size();
    }

    virtual Value shift() {
        if (size()) {
            return remove(static_cast<Size>(0));
        } else {
            return UNDEFINED;
        }
    }

    virtual T shiftTyped() {
        if (!size()) {
            LIBJ_THROW(Error::EMPTY_COLLECTION);
        }
        return removeTyped(static_cast<Size>(0));
    }

    virtual Size unshift(const Value& val) {
        add(0, val);
        return size();
    }

    virtual Size unshiftTyped(const T& t) {
        addTyped(0, t);
        return size();
    }

    virtual Size push(const Value& val) {
        add(val);
        return size();
    }

    virtual Size pushTyped(const T& t) {
        addTyped(t);
        return size();
    }

    virtual Value pop() {
        Size len = size();
        if (len) {
            return remove(len - 1);
        } else {
            return UNDEFINED;
        }
    }

    virtual T popTyped() {
        Size len = size();
        if (!len) {
            LIBJ_THROW(Error::EMPTY_COLLECTION);
        }
        return removeTyped(len - 1);
    }

    virtual Int indexOf(const Value& v) const {
        Size index = 0;
        Iterator::Ptr itr = iterator();
        while (itr->hasNext()) {
            if (itr->next().equals(v)) {
                return index;
            }
            index++;
        }
        return -1;
    }

    virtual Int lastIndexOf(const Value& v) const {
        Size index = size() - 1;
        Iterator::Ptr itr = reverseIterator();
        while (itr->hasNext()) {
            if (itr->next().equals(v)) {
                return index;
            }
            index--;
        }
        return -1;
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_GENERIC_LIST_H_
