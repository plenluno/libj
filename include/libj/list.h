// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_LIST_H_
#define LIBJ_LIST_H_

#include "libj/collection.h"

namespace libj {

class List : LIBJ_COLLECTION(List)
 public:
    virtual Boolean add(const Value& val) = 0;
    virtual Boolean add(Size index, const Value& val) = 0;
    virtual Value get(Size index) const = 0;
    virtual Value remove(Size index) = 0;
    virtual Boolean remove(const Value& val) = 0;
    virtual Iterator::Ptr reverseIterator() const = 0;
    virtual Boolean set(Size index, const Value& val) = 0;
    virtual Value subList(Size from, Size to) const = 0;

 public:
    Size length() const {
        return size();
    }

    Value shift() {
        return remove(0);
    }

    Size unshift(const Value& val) {
        add(0, val);
        return size();
    }

    Size push(const Value& val) {
        add(val);
        return size();
    }

    Value pop() {
        return remove(size() - 1);
    }

    Int indexOf(const Value& val) {
        Size index = 0;
        Iterator::Ptr itr = iterator();
        while (itr->hasNext()) {
            if (itr->next().equals(val)) {
                return index;
            }
            index++;
        }
        return -1;
    }

    Int lastIndexOf(const Value& val) {
        Size index = size() - 1;
        Iterator::Ptr itr = reverseIterator();
        while (itr->hasNext()) {
            if (itr->next().equals(val)) {
                return index;
            }
            index--;
        }
        return -1;
    }
};

#define LIBJ_LIST(T) public libj::List { \
    LIBJ_MUTABLE_DEFS(T, libj::List)

#define LIBJ_LIST_IMPL(L) \
    LIBJ_COLLECTION_IMPL(L) \
public: \
    Boolean add(Size i, const Value& v) { \
        return L->add(i, v); \
    } \
    Value get(Size i) const { \
        return L->get(i); \
    } \
    Value remove(Size i) { \
        return L->remove(i); \
    } \
    Iterator::Ptr reverseIterator() const { \
        return L->reverseIterator(); \
    } \
    Boolean set(Size i, const Value& v) { \
        return L->set(i, v); \
    }

}  // namespace libj

#endif  // LIBJ_LIST_H_
