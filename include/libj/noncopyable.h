// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_NONCOPYABLE_H_
#define LIBJ_NONCOPYABLE_H_

class NonCopyable {
 protected:
    NonCopyable() {}
    ~NonCopyable() {}

 private:
    NonCopyable(const NonCopyable&);
    const NonCopyable& operator=(const NonCopyable&);
};

#endif  // LIBJ_NONCOPYABLE_H_
