// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/detail/xml/document.h>

namespace libj {
namespace xml {

Document::Ptr Document::parse(String::CPtr str) {
    return detail::xml::Document::parse(str);
}

}  // namespace xml
}  // namespace libj
