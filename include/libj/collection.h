// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_COLLECTION_H_
#define LIBJ_COLLECTION_H_

#include "libj/iterator.h"
#include "libj/string_buffer.h"

namespace libj {

class Collection : LIBJ_MUTABLE(Collection)
 public:
    virtual Boolean add(const Value& val) = 0;
    virtual void clear() = 0;
    // virtual Boolean contains(const Value& val) const = 0;
    // virtual Boolean containsAll(CPtr collection) const = 0;
    virtual Boolean remove(const Value& val) = 0;
    // virtual Boolean removeAll(CPtr collection) = 0;
    virtual Iterator::Ptr iterator() const = 0;
    virtual Size size() const = 0;

    Boolean isEmpty() const {
        return size() == 0;
    }

    Boolean addAll(Collection::CPtr collection) {
        if (!collection) return false;

        Iterator::Ptr itr = collection->iterator();
        Boolean changed = false;
        while (itr->hasNext()) {
            if (add(itr->next()))
                changed = true;
        }
        return changed;
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
};

#define LIBJ_COLLECTION(T) public libj::Collection { \
    LIBJ_MUTABLE_DEFS(T, libj::Collection)

#define LIBJ_COLLECTION_IMPL(C) \
public: \
    Boolean add(const Value& v) { \
        return C->add(v); \
    } \
    Boolean addAll(Collection::CPtr c) { \
        return C->addAll(c); \
    } \
    void clear() { \
        C->clear(); \
    } \
    Boolean remove(const Value& v) { \
        return C->remove(v); \
    } \
    Iterator::Ptr iterator() const { \
        return C->iterator(); \
    } \
    Size size() const { \
        return C->size(); \
    } \
    Boolean isEmpty() const { \
        return C->isEmpty(); \
    }

}  // namespace libj

#endif  // LIBJ_COLLECTION_H_
