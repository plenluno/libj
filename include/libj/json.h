// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JSON_H_
#define LIBJ_JSON_H_

#include "libj/singleton.h"

namespace libj {

class Json : LIBJ_SINGLETON(Json)
 public:
    Value parse(Type<String>::Cptr str);
    Type<String>::Cptr stringify(Value val);
};

}  // namespace libj

#endif  // LIBJ_JSON_H_