// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_XML_DOCUMENT_H_
#define LIBJ_XML_DOCUMENT_H_

#include <libj/xml/node.h>

namespace libj {
namespace xml {

class Document : LIBJ_XML_NODE(Document)
 public:
    static CPtr parse(String::CPtr str);
};

}  // namespace xml
}  // namespace libj

#endif  // LIBJ_XML_DOCUMENT_H_
