// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef BTEST_BTEST_MUTABLE_H_
#define BTEST_BTEST_MUTABLE_H_

#include <libj/mutable.h>
#include <libj/string.h>

namespace libj {

class BTestMutable : LIBJ_MUTABLE(BTestMutable)
 public:
    static CPtr create() {
        BTestMutable::CPtr p(new BTestMutable);
        return p;
    }

    String::CPtr toString() const {
        return String::create();
    }
};

}  // namespace libj

#endif  // BTEST_BTEST_MUTABLE_H_
