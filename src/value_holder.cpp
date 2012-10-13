// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/string.h"
#include "libj/value_holder.h"

namespace libj {

class ValueHolderImpl : public ValueHolder {
 public:
    static Ptr create(const Value& val) {
        return Ptr(new ValueHolderImpl(val));
    }

    virtual Value get() const {
        return val_;
    }

    virtual void set(const Value& val) {
        val_ = val;
    }

    virtual String::CPtr toString() const {
        return String::valueOf(val_);
    }

 private:
    Value val_;

    ValueHolderImpl(const Value& val) : val_(val) {}
};

ValueHolder::Ptr ValueHolder::create(const Value& val) {
    return ValueHolderImpl::create(val);
}

}  // namespace libj
