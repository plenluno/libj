// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef BTEST_BTEST_IMMUTABLE_H_
#define BTEST_BTEST_IMMUTABLE_H_

#include <libj/immutable.h>
#include <libj/string.h>

namespace libj {

class BTestImmutable : LIBJ_IMMUTABLE(BTestImmutable)
 public:
    static CPtr create() {
        BTestImmutable::CPtr p(new BTestImmutable);
        return p;
    }

    String::CPtr toString() const {
        return String::create();
    }
};

}  // namespace libj

#endif  // BTEST_BTEST_IMMUTABLE_H_
