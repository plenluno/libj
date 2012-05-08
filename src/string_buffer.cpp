// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/string_buffer.h"

namespace libj {

class StringBufferImpl : public StringBuffer {
 public:
    static Ptr create() {
        Ptr p(new StringBufferImpl());
        return p;
    }
    
    Size length() const {
        return str_->length();
    }
    
    Char charAt(Size n) const {
        return str_->charAt(n);
    }
    
    // TODO: make it more efficient
    bool append(const Value& val) {
        Type<String>::Cptr s = String::valueOf(val);
        if (s) {
            str_ = str_->concat(s);
            return true;
        } else {
            return false;
        }
    }
    
    Type<String>::Cptr toString() const {
        return str_->toString();
    }
    
 private:
    StringBufferImpl() : str_(String::create()) {}
    
    Type<String>::Cptr str_;
};

Type<StringBuffer>::Ptr StringBuffer::create() {
    return StringBufferImpl::create();
}

}  // namespace libj
