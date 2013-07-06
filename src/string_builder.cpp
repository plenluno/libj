// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/string_builder.h>
#include <libj/detail/string_builder.h>

namespace libj {

StringBuilder::Ptr StringBuilder::create() {
    return Ptr(new detail::StringBuilder<StringBuilder>());
}

}  // namespace libj
