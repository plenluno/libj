// Copyright (c) 2012 Plenluno All rights reserved.

#include <map>

#include "libj/map.h"
#include "libj/string_buffer.h"

namespace libj {

class MapImpl : public Map {
 private:
    class ValueComp {
     public:
        Boolean operator() (const Value& lv, const Value& rv) const {
            return lv.compareTo(rv) < 0;
        }
    };

    typedef std::map<Value, Value, ValueComp> ValueMap;

 public:
    static Ptr create() {
        return Ptr(new MapImpl());
    }

    virtual Size size() const {
        return map_.size();
    }

    virtual Boolean containsKey(const Value& key) const {
        return map_.find(key) != map_.end();
    }

    virtual Boolean containsValue(const Value& val) const {
        for (ValueMap::const_iterator itr = map_.begin();
             itr != map_.end();
             ++itr) {
            if (!itr->second.compareTo(val))
                return true;
        }
        return false;
    }

    virtual Value get(const Value& key) const {
        ValueMap::const_iterator itr = map_.find(key);
        if (itr != map_.end()) {
            return itr->second;
        } else {
            return UNDEFINED;
        }
    }

    virtual Value put(const Value& key, const Value& val) {
        Value v = get(key);
        map_[key] = val;
        return v;
    }

    virtual Value remove(const Value& key) {
        Value v = get(key);
        map_.erase(key);
        return v;
    }

    virtual Set::CPtr keySet() const {
        Set::Ptr s = Set::create();
        for (ValueMap::const_iterator itr = map_.begin();
             itr != map_.end();
             ++itr) {
            s->add(itr->first);
        }
        return s;
    }

    virtual void clear() {
        map_.clear();
    }

    virtual Boolean isEmpty() const {
        return size() == 0;
    }

    virtual String::CPtr toString() const {
        StringBuffer::Ptr sb = StringBuffer::create();
        sb->appendChar('{');
        Boolean first = true;
        Set::CPtr keys = keySet();
        Iterator::Ptr itr = keys->iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            if (first) {
                first = false;
            } else {
                sb->appendCStr(", ");
            }
            sb->append(String::valueOf(v));
            sb->appendChar('=');
            sb->append(String::valueOf(get(v)));
        }
        sb->appendChar('}');
        return sb->toString();
    }

 private:
    ValueMap map_;
};

Map::Ptr Map::create() {
    return MapImpl::create();
}

}  // namespace libj
