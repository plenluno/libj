// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_DEFAULT_THREAD_FACTORY_H_
#define LIBJ_DETAIL_DEFAULT_THREAD_FACTORY_H_

#include <libj/thread_factory.h>

namespace libj {
namespace detail {

class DefaultThreadFactory : public libj::ThreadFactory {
    virtual Thread::Ptr createThread(Function::Ptr func) {
        return Thread::create(func);
    }

    virtual String::CPtr toString() const {
        return String::create();
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_DEFAULT_THREAD_FACTORY_H_
