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
        bool operator() (const Value& lv, const Value& rv) const {
            return lv.compareTo(rv) < 0;
        }
    };
    
    typedef std::map<Value,Value,ValueComp> ValueMap;
     
 public:
    Size size() const {
        return map_.size();
    }
    
    Value get(Value key) const {
        ValueMap::const_iterator itr = map_.find(key);
        if (itr != map_.end())
            return itr->second;
        else
            return Null::instance();
    }

    Value put(Value key, Value val) {
        Value v = get(key);
        map_[key] = val;
        return v;
    }
    
    Value remove(Value key) {
        Value v = get(key);
        map_.erase(key);
        return v;
    }
    
    Type<Set>::Cptr keySet() const {
        Type<Set>::Ptr s = Set::create();
        for (ValueMap::const_iterator itr = map_.begin();
             itr != map_.end();
             itr++) {
            s->add(itr->first);     
        }
        return s;
    }

    void clear() {
        map_.clear();
    }

    Type<Map>::Ptr clone() const {
        // TODO(PL): implement
        Type<Map>::Ptr p(new MapImpl());
        return p;
    }

    Type<String>::Cptr toString() const {
        // TODO(PL): implement
        return String::create();
    }

 private:
    ValueMap map_;
};

Type<Map>::Ptr Map::create() {
    Type<Map>::Ptr p(new MapImpl());
    return p;
}

}  // namespace libj
