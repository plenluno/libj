// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_XML_NAMED_NODE_MAP_H_
#define LIBJ_XML_NAMED_NODE_MAP_H_

#include <libj/xml/node.h>

namespace libj {
namespace xml {

class NamedNodeMap : LIBJ_MUTABLE(NamedNodeMap)
 public:
    virtual Size length() const = 0;

    virtual Node::Ptr item(Size index) const = 0;

    virtual Node::Ptr getNamedItem(String::CPtr name) const = 0;
};

}  // namespace xml
}  // namespace libj

#endif  // LIBJ_XML_NAMED_NODE_MAP_H_
