// Copyright (c) 2012 Plenluno All rights reserved.

#include <set>
#include "libj/set.h"
#include "libj/string.h"

namespace libj {

class SetImpl : public Set {
 private:
    class ValueComp {
     public:
        bool operator() (const Value& lv, const Value& rv) const {
            return lv.compareTo(rv) < 0;
        }
    };
    
    typedef std::set<Value,ValueComp> ValueSet;
     
 public:
    Size size() const {
        return set_.size();
    }

    bool add(Value v) {
        std::pair<ValueSet::iterator,bool> p = set_.insert(v);
        return p.second;
    }
    
    bool remove(Value v) {
        return set_.erase(v) > 0;
    }

    void clear() {
        set_.clear();
    }

    Type<Set>::Ptr clone() const {
        // TODO(PL): implement
        Type<Set>::Ptr p(new SetImpl());
        return p;
    }

    Type<String>::Cptr toString() const {
        // TODO(PL): implement
        return String::create();
    }

 private:
    class IteratorImpl : public Iterator {
        friend class SetImpl;
        
        IteratorImpl(const ValueSet* s)
            : set_(s)
            , itr_(s->begin()) {}
    
     public:
        bool hasNext() const {
            return itr_ != set_->end();
        }
        
        Value next() {
            Value v = *itr_;
            ++itr_;
            return v;
        }
        
     private:
        const ValueSet* set_;
        ValueSet::const_iterator itr_;
    };

 public:
    Type<Iterator>::Ptr iterator() const {
        Type<Iterator>::Ptr p(new IteratorImpl(&set_));
        return p;
    }

 private:
    ValueSet set_;
};

Type<Set>::Ptr Set::create() {
    Type<Set>::Ptr p(new SetImpl());
    return p;
}

}  // namespace libj
