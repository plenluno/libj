// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_STATUS_H_
#define LIBJ_DETAIL_STATUS_H_

#include <libj/symbol.h>

namespace libj {
namespace detail {

template<typename I>
class Status : public I {
 public:
    Status(Int code, String::CPtr msg)
        : code_(code)
        , message_(msg) {}

    virtual Int code() const {
        return code_;
    }

    virtual String::CPtr message() const {
        if (message_) {
            return message_;
        } else {
            return String::create();
        }
    }

    virtual String::CPtr toString() const {
        return message();
    }

 private:
    Int code_;
    String::CPtr message_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_STATUS_H_
