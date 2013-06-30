// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_XML_ATTR_H_
#define LIBJ_DETAIL_XML_ATTR_H_

#include <libj/xml/attr.h>
#include <libj/detail/xml/node.h>

namespace libj {
namespace detail {
namespace xml {

class Attr : public Node<libj::xml::Attr> {
 public:
    Attr(
        libj::xml::Document::CPtr root,
        const pugi::xml_attribute& attr)
        : attr_(attr.internal_object()) {
        root_ = root;
        if (attr_) {
            name_ = createString(attr_.name());
            value_ = createString(attr_.value());
        } else {
            name_ = String::create();
            value_ = String::create();
        }
    }

    Attr(
        libj::xml::Document::CPtr root,
        String::CPtr name) {
        assert(!attr_);
        root_ = root;
        name_ = name;
        value_ = String::create();
    }

    virtual String::CPtr name() const {
        return name_;
    }

    virtual String::CPtr value() const {
        return value_;
    }

    virtual void setValue(String::CPtr value) {
        if (!value) value = String::create();
        value_ = value;
        if (attr_) {
            attr_.set_value(value->data());
        }
    }

 public:
    virtual String::CPtr nodeName() const {
        return name();
    }

    virtual String::CPtr nodeValue() const {
        return value();
    }

    virtual void setNodeValue(String::CPtr value) {
        setValue(value);
    }

    virtual NodeType nodeType() const {
        return ATTRIBUTE_NODE;
    }

    virtual libj::xml::Node::Ptr parentNode() const {
        return libj::xml::Node::null();
    }

    virtual libj::xml::NodeList::Ptr childNodes() const {
        // TODO(plenluno): check
        return libj::xml::NodeList::null();
    }

    virtual libj::xml::Node::Ptr firstChild() const {
        // TODO(plenluno): check
        return libj::xml::Node::null();
    }

    virtual libj::xml::Node::Ptr lastChild() const {
        // TODO(plenluno): check
        return libj::xml::Node::null();
    }

    virtual libj::xml::Node::Ptr previousSibling() const {
        return libj::xml::Node::null();
    }

    virtual libj::xml::Node::Ptr nextSibling() const {
        return libj::xml::Node::null();
    }

    virtual libj::xml::NamedNodeMap::Ptr attributes() const {
        return libj::xml::NamedNodeMap::null();
    }

    virtual Boolean hasChildNodes() const {
        // TODO(plenluno): check
        return false;
    }

    virtual Boolean hasAttributes() const {
        return false;
    }

 private:
    pugi::xml_attribute attr_;
    String::CPtr name_;
    String::CPtr value_;
};

inline libj::xml::Attr::Ptr createAttr(
    libj::xml::Document::CPtr root,
    const pugi::xml_attribute& attr) {
    return libj::xml::Attr::Ptr(new Attr(root, attr));
}

inline libj::xml::Attr::Ptr createAttr(
    libj::xml::Document::CPtr root,
    String::CPtr name) {
    return libj::xml::Attr::Ptr(new Attr(root, name));
}

}  // namespace xml
}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_XML_ATTR_H_
