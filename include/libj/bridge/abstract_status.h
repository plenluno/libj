// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_BRIDGE_ABSTRACT_STATUS_H_
#define LIBJ_BRIDGE_ABSTRACT_STATUS_H_

#include "libj/status.h"

namespace libj {
namespace bridge {

template<typename T>
class AbstractStatus : public T {
 public:
    AbstractStatus(Status::CPtr status) : status_(status) {}

    virtual Int code() const {
        return status_->code();
    }

    virtual String::CPtr message() const {
        return status_->message();
    }

    virtual String::CPtr toString() const {
        return status_->toString();
    }

 private:
    Status::CPtr status_;
};

}  // namespace bridge
}  // namespace libj

#endif  // LIBJ_BRIDGE_ABSTRACT_STATUS_H_
