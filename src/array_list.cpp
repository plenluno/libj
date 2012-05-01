// Copyright (c) 2012 Plenluno All rights reserved.

#include <vector>
#include "libj/array_list.h"
#include "libj/string.h"

namespace libj {

class ArrayListImpl : public ArrayList {
 public:
    Size size() const {
        return vec_.size();
    }

    bool add(Value v) {
        vec_.push_back(v);
        return true;
    }

    bool add(Size i, Value v) {
        if (i < 0 || i > vec_.size()) {
            return false;
        } else {
            vec_.insert(vec_.begin() + i, v);
            return true;
        }
    }

    bool set(Size i, Value v) {
        if (i >= vec_.size()) {
            return false;
        } else {
            vec_[i] = v;
            return true;
        }
    }

    Value get(Size i) {
        if (i >= vec_.size()) {
            // TODO(PL): return Error
            return 0;
        } else {
            return vec_[i];
        }
    }

    Value remove(Size i) {
        if (i >= vec_.size()) {
            // TODO(PL): return Error
            return 0;
        } else {
            return *vec_.erase(vec_.begin() + i);
        }
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
    std::vector<Value> vec_;
};

Type<ArrayList>::Ptr ArrayList::create() {
    Type<ArrayList>::Ptr p(new ArrayListImpl());
    return p;
}

}  // namespace libj
