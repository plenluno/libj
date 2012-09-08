// Copyright (c) 2012 Plenluno All rights reserved.

#include <map>

#include "libj/map.h"
#include "libj/null.h"
#include "libj/string.h"

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
    Size size() const {
        return map_.size();
    }

    Boolean containsKey(const Value& key) const {
        return map_.find(key) != map_.end();
    }

    Boolean containsValue(const Value& val) const {
        for (ValueMap::const_iterator itr = map_.begin();
             itr != map_.end();
             ++itr) {
            if (!itr->second.compareTo(val))
                return true;
        }
        return false;
    }

    Value get(const Value& key) const {
        ValueMap::const_iterator itr = map_.find(key);
        if (itr != map_.end())
            return itr->second;
        else
            return Null::instance();
    }

    Value put(const Value& key, const Value& val) {
        Value v = get(key);
        map_[key] = val;
        return v;
    }

    Value remove(const Value& key) {
        Value v = get(key);
        map_.erase(key);
        return v;
    }

    Set::CPtr keySet() const {
        Set::Ptr s = Set::create();
        for (ValueMap::const_iterator itr = map_.begin();
             itr != map_.end();
             ++itr) {
            s->add(itr->first);
        }
        return s;
    }

    void clear() {
        map_.clear();
    }

    String::CPtr toString() const {
        static const String::CPtr lbrace = String::create("{");
        static const String::CPtr rbrace = String::create("}");
        static const String::CPtr eq = String::create("=");
        static const String::CPtr comma = String::create(", ");

        StringBuffer::Ptr sb = StringBuffer::create();
        sb->append(lbrace);
        Boolean first = true;
        Set::CPtr keys = keySet();
        Iterator::Ptr itr = keys->iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            if (first) {
                first = false;
            } else {
                sb->append(comma);
            }
            sb->append(String::valueOf(v));
            sb->append(eq);
            sb->append(String::valueOf(get(v)));
        }
        sb->append(rbrace);
        return sb->toString();
    }

 private:
    ValueMap map_;
};

Map::Ptr Map::create() {
    Map::Ptr p(new MapImpl());
    return p;
}

}  // namespace libj
