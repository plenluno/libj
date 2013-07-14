// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_XML_ELEMENT_H_
#define LIBJ_XML_ELEMENT_H_

#include <libj/xml/attr.h>

namespace libj {
namespace xml {

class Element : LIBJ_XML_NODE(Element)
 public:
    virtual String::CPtr tagName() const = 0;

    virtual String::CPtr getAttribute(String::CPtr name) const = 0;

    virtual Attr::CPtr getAttributeNode(String::CPtr name) const = 0;

    virtual Boolean hasAttribute(String::CPtr name) const = 0;
};

}  // namespace xml
}  // namespace libj

#endif  // LIBJ_XML_ELEMENT_H_
