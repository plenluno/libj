// Copyright (c) 2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_XML_NODE_H_
#define LIBJ_IMPL_XML_NODE_H_

#define LIBJ_XML_NODE_INSTANCEOF(ID) \
    (ID == libj::Type<libj::xml::Node>::id() || LIBJ_IMMUTABLE_INSTANCEOF(ID))

#endif  // LIBJ_IMPL_XML_NODE_H_
