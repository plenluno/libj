// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_COLLECTION_H_
#define LIBJ_COLLECTION_H_

#include <vector>

#include "libj/iterator.h"
#include "libj/string_buffer.h"

namespace libj {

class Collection : LIBJ_MUTABLE(Collection)
 public:
    virtual Boolean add(const Value& val) = 0;
    virtual void clear() = 0;
    virtual Iterator::Ptr iterator() const = 0;
    virtual Boolean remove(const Value& val) = 0;
    virtual Size size() const = 0;

 public:
    Boolean isEmpty() const {
        return size() == 0;
    }

    Boolean contains(const Value& val) const {
        Iterator::Ptr itr = iterator();
        while (itr->hasNext()) {
            if (itr->next().equals(val))
                return true;
        }
        return false;
    }

    Boolean containsAll(CPtr collection) const {
        if (!collection) return false;

        Iterator::Ptr itr = collection->iterator();
        while (itr->hasNext()) {
            if (!contains(itr->next()))
                return false;
        }
        return true;
    }

    Boolean addAll(CPtr collection) {
        if (!collection) return false;

        Iterator::Ptr itr = collection->iterator();
        Boolean changed = false;
        while (itr->hasNext()) {
            if (add(itr->next()))
                changed = true;
        }
        return changed;
    }

    Boolean removeAll(CPtr collection) {
        if (!collection) return false;

        Iterator::Ptr itr = collection->iterator();
        Boolean changed = false;
        while (itr->hasNext()) {
            Value val = itr->next();
            while (remove(val))
                changed = true;
        }
        return changed;
    }

    Boolean retainAll(CPtr collection) {
        if (!collection) return false;

        Iterator::Ptr itr = iterator();
        std::vector<Value> vs;
        while (itr->hasNext()) {
            Value val = itr->next();
            if (!collection->contains(val)) {
                vs.push_back(val);
            }
        }

        Boolean changed = false;
        size_t len = vs.size();
        for (size_t i = 0; i < len; i++) {
            while (remove(vs[i]))
                changed = true;
        }
        return changed;
    }

    String::CPtr toString() const {
        static const String::CPtr lbracket = String::create("[");
        static const String::CPtr rbracket = String::create("]");
        static const String::CPtr comma = String::create(", ");

        StringBuffer::Ptr sb = StringBuffer::create();
        sb->append(lbracket);
        Boolean first = true;
        Iterator::Ptr itr = iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            if (first) {
                first = false;
            } else {
                sb->append(comma);
            }
            sb->append(String::valueOf(v));
        }
        sb->append(rbracket);
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
    void clear() { \
        C->clear(); \
    } \
        Iterator::Ptr iterator() const { \
        return C->iterator(); \
    } \
    Boolean remove(const Value& v) { \
        return C->remove(v); \
    } \
    Size size() const { \
        return C->size(); \
    }

}  // namespace libj

#endif  // LIBJ_COLLECTION_H_
