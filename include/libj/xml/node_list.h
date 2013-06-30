// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_XML_NODE_LIST_H_
#define LIBJ_XML_NODE_LIST_H_

#include <libj/xml/node.h>

namespace libj {
namespace xml {

class NodeList : LIBJ_MUTABLE(NodeList)
 public:
    virtual Size length() const = 0;

    virtual Node::Ptr item(Size index) const = 0;
};

}  // namespace xml
}  // namespace libj

#endif  // LIBJ_XML_NODE_LIST_H_
