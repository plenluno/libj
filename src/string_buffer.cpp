// Copyright (c) 2012 Plenluno All rights reserved.

#include <list>
#include "libj/string_buffer.h"

namespace libj {

class StringImpl : public String {
    typedef std::basic_string<char> Str8;
    typedef std::basic_string<Char> Str32;

 public:
    const Str8* getStr8() const;
    const Str32* getStr32() const;
};

class StringBufferImpl : public StringBuffer {
    typedef std::basic_string<char> Str8;
    typedef std::basic_string<Char> Str32;

 public:
    static Ptr create() {
        Ptr p(new StringBufferImpl());
        return p;
    }

    Size length() const {
        return length_;
    }

    Char charAt(Size n) const {
        if (n >= length_) return NO_CHAR;
        if (strs_.size()) join();
        if (buf32_) return (*buf32_)[n];
        else return (*buf8_)[n];
    }

    bool append(const Value& val) {
        String::CPtr s = String::valueOf(val);
        if (s) {
            strs_.push_back(s);
            length_ += s->length();
            if (!s->isAscii()) ascii_ = false;
            return true;
        } else {
            return false;
        }
    }

    String::CPtr toString() const {
        if (strs_.size()) {
            join();
            if (ascii_)
                cstr_ = String::create(buf8_->c_str(), String::ASCII, length_);
            else
                cstr_ = String::create(buf32_->c_str(), String::UTF32, length_);
        }
        return cstr_;
    }

    ~StringBufferImpl() {
        delete buf8_;
        delete buf32_;
    }

 private:
    static String::CPtr LIBJ_STR_NULL;

    StringBufferImpl()
        : buf8_(new Str8())
        , buf32_(0)
        , strs_(std::list<String::CPtr>())
        , length_(0)
        , ascii_(true)
        , cstr_(LIBJ_STR_NULL) {}

    mutable Str8* buf8_;
    mutable Str32* buf32_;
    mutable std::list<String::CPtr> strs_;
    Size length_;
    mutable bool ascii_;
    mutable String::CPtr cstr_;

    void join() const {
        typedef std::list<String::CPtr>::const_iterator li;
        if (ascii_) {
            buf8_->reserve(length_);
            for (li i = strs_.begin(), e = strs_.end(); i != e; ++i) {
                String::CPtr s = *i;
                const StringImpl* si = reinterpret_cast<const StringImpl*>(&*s);
                buf8_->append(*si->getStr8());
            }
        } else {
            typedef Str8::const_iterator it8;
            if (!buf32_) buf32_ = new Str32();
            buf32_->reserve(length_);
            if (buf8_) {
                for (it8 i = buf8_->begin(), e = buf8_->end(); i != e; ++i) {
                    buf32_->push_back(*i);
                }
                delete buf8_;
                buf8_ = 0;
            }
            for (li i = strs_.begin(), e = strs_.end(); i != e; ++i) {
                String::CPtr s = *i;
                const StringImpl* si = reinterpret_cast<const StringImpl*>(&*s);
                if (si->isAscii()) {
                    const Str8* s8 = si->getStr8();
                    for (it8 j = s8->begin(), e = s8->end(); j != e; ++j) {
                        buf32_->push_back(*j);
                    }
                } else {
                    buf32_->append(*si->getStr32());
                }
            }
        }
        strs_.clear();
    }
};

String::CPtr StringBufferImpl::LIBJ_STR_NULL = String::create();

StringBuffer::Ptr StringBuffer::create() {
    return StringBufferImpl::create();
}

}  // namespace libj
