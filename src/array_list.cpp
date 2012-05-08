// Copyright (c) 2012 Plenluno All rights reserved.

#include <vector>
#include "libj/array_list.h"
#include "libj/error.h"
#include "libj/string.h"

namespace libj {

class ArrayListImpl : public ArrayList {
 public:
    Size size() const {
        return vec_.size();
    }

    bool add(const Value& v) {
        vec_.push_back(v);
        return true;
    }

    bool add(Size i, const Value& v) {
        if (i < 0 || i > vec_.size()) {
            return false;
        } else {
            vec_.insert(vec_.begin() + i, v);
            return true;
        }
    }

    bool set(Size i, const Value& v) {
        if (i >= vec_.size()) {
            return false;
        } else {
            vec_[i] = v;
            return true;
        }
    }

    Value get(Size i) const {
        if (i >= vec_.size()) {
            return Error::create(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            return vec_[i];
        }
    }

    Value remove(Size i) {
        if (i >= vec_.size()) {
            return Error::create(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            return *vec_.erase(vec_.begin() + i);
        }
    }
    
    bool remove(const Value& v) {
        Size n = size();
        for (Size i = 0; i < n; i++) {
            if (!vec_[i].compareTo(v)) {
                remove(i);
                return true;
            }
        }
        return false;
    }

    void clear() {
        vec_.clear();
    }

    Type<ArrayList>::Ptr clone() const {
        // TODO(PL): implement
        Type<ArrayList>::Ptr p(new ArrayListImpl());
        return p;
    }

    Type<String>::Cptr toString() const {
        // TODO(PL): implement
        return String::create();
    }

 private:
    class IteratorImpl : public Iterator {
        friend class ArrayListImpl;
        
        IteratorImpl(const std::vector<Value>* v)
            : vec_(v)
            , itr_(v->begin()) {}
    
     public:
        bool hasNext() const {
            return itr_ != vec_->end();
        }
        
        Value next() {
            Value v = *itr_;
            ++itr_;
            return v;
        }
        
     private:
        const std::vector<Value>* vec_;
        std::vector<Value>::const_iterator itr_;
    };

 public:
    Type<Iterator>::Ptr iterator() const {
        Type<Iterator>::Ptr p(new IteratorImpl(&vec_));
        return p;
    }

 private:
    std::vector<Value> vec_;
};

Type<ArrayList>::Ptr ArrayList::create() {
    Type<ArrayList>::Ptr p(new ArrayListImpl());
    return p;
}

}  // namespace libj
