// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_MAP_H_
#define LIBJ_MAP_H_

#include <libj/typed_set.h>

namespace libj {

class Map : LIBJ_MUTABLE(Map)
 public:
    class Entry : LIBJ_MUTABLE(Entry)
        virtual Value getKey() const = 0;

        virtual Value getValue() const = 0;
    };

    static Ptr create();

    virtual void clear() = 0;

    virtual Boolean isEmpty() const = 0;

    virtual Boolean containsKey(const Value& key) const = 0;

    virtual Boolean containsValue(const Value& val) const = 0;

    virtual Set::CPtr keySet() const = 0;

    virtual TypedSet<Entry::CPtr>::CPtr entrySet() const = 0;

    virtual Value get(const Value& key) const = 0;

    virtual Value put(const Value& key, const Value& val) = 0;

    virtual Value remove(const Value& key) = 0;

    virtual Size size() const = 0;
};

}  // namespace libj

#define LIBJ_MAP(T) public libj::Map { \
    LIBJ_MUTABLE_DEFS(T, libj::Map)

#endif  // LIBJ_MAP_H_
