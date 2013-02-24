// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GENERIC_COLLECTION_H_
#define LIBJ_DETAIL_GENERIC_COLLECTION_H_

#include <libj/collection.h>
#include <libj/iterator.h>
#include <libj/typed_iterator.h>
#include <libj/string_buffer.h>
#include <libj/detail/util.h>

#include <vector>

namespace libj {
namespace detail {

template<typename T, typename I>
class GenericCollection : public I {
 public:
    typedef typename I::Ptr Ptr;
    typedef typename I::CPtr CPtr;

    virtual ~GenericCollection() {}

    virtual Size size() const = 0;

    virtual Boolean add(const Value& v) = 0;

    virtual Boolean addTyped(const T& t) = 0;

    virtual void clear() = 0;

    virtual Boolean remove(const Value& v) = 0;

    virtual Boolean removeTyped(const T& t) = 0;

    virtual Iterator::Ptr iterator() const = 0;

    virtual typename TypedIterator<T>::Ptr iteratorTyped() const = 0;

 public:
    virtual Boolean isEmpty() const {
        return size() == 0;
    }

    virtual Boolean contains(const Value& val) const {
        Iterator::Ptr itr = iterator();
        while (itr->hasNext()) {
            if (itr->next().equals(val))
                return true;
        }
        return false;
    }

    virtual Boolean containsAll(Collection::CPtr collection) const {
        if (!collection) return false;

        Iterator::Ptr itr = collection->iterator();
        while (itr->hasNext()) {
            if (!contains(itr->next()))
                return false;
        }
        return true;
    }

    virtual Boolean addAll(Collection::CPtr collection) {
        if (!collection) return false;

        Iterator::Ptr itr = collection->iterator();
        Boolean changed = false;
        while (itr->hasNext()) {
            if (add(itr->next()))
                changed = true;
        }
        return changed;
    }

    virtual Boolean removeAll(Collection::CPtr collection) {
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

    virtual Boolean retainAll(Collection::CPtr collection) {
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

    virtual String::CPtr toString() const {
        libj::StringBuffer::Ptr sb = libj::StringBuffer::create();
        sb->append('[');
        Boolean first = true;
        Iterator::Ptr itr = iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            if (first) {
                first = false;
            } else {
                sb->append(", ");
            }
            sb->append(String::valueOf(v));
        }
        sb->append(']');
        return sb->toString();
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_GENERIC_COLLECTION_H_
