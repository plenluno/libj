// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_NONCOPYABLE_H_
#define LIBJ_DETAIL_NONCOPYABLE_H_

namespace libj {
namespace detail {

class NonCopyable {
 protected:
    NonCopyable() {}
    ~NonCopyable() {}

 private:
    NonCopyable(const NonCopyable&);
    const NonCopyable& operator=(const NonCopyable&);
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_NONCOPYABLE_H_
