// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/endian.h"
#include "libj/typedef.h"

namespace libj {

Endian endian() {
    static union {
        UInt i;
        UByte b[4];
    } u = { 0x01020304 };

    return u.b[0] == 1 ? BIG : LITTLE;
}

}  // namespace libj
