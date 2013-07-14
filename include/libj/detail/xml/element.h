// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_XML_ELEMENT_H_
#define LIBJ_DETAIL_XML_ELEMENT_H_

#include <libj/xml/element.h>
#include <libj/detail/xml/node.h>

namespace libj {
namespace detail {
namespace xml {

libj::xml::Attr::CPtr createAttr(
    libj::xml::Document::CPtr root,
    const pugi::xml_attribute& attr);

class Element : public Node<libj::xml::Element> {
 public:
    Element(
        libj::xml::Document::CPtr root,
        const pugi::xml_node& node)
        : Node(root, node) {}

    virtual String::CPtr tagName() const {
        return name_;
    }

    virtual String::CPtr getAttribute(String::CPtr name) const {
        if (!name) return String::null();

        pugi::xml_attribute attr = node_.attribute(
            reinterpret_cast<const pugi::char_t*>(name->data()));
        if (attr) {
            return createString(attr.value());
        } else {
            return String::create();
        }
    }

    virtual Attr::CPtr getAttributeNode(String::CPtr name) const {
        if (!name) return Attr::null();

        pugi::xml_attribute attr = node_.attribute(
            reinterpret_cast<const pugi::char_t*>(name->data()));
        return createAttr(root_, node_, attr);
    }

    virtual Boolean hasAttribute(String::CPtr name) const {
        return name && node_.attribute(
            reinterpret_cast<const pugi::char_t*>(name->data()));
    }

 public:
    virtual String::CPtr nodeName() const {
        return tagName();
    }

    virtual String::CPtr nodeValue() const {
        return String::null();
    }

    virtual NodeType nodeType() const {
        return ELEMENT_NODE;
    }

    virtual libj::xml::NamedNodeMap::CPtr attributes() const {
        return libj::xml::NamedNodeMap::CPtr(
                new NamedNodeMap(root(), node_));
    }

    virtual libj::xml::Element::CPtr asElement() const {
        return LIBJ_THIS_CPTR(Element);
    }
};

inline libj::xml::Element::CPtr createElement(
    libj::xml::Document::CPtr root,
    const pugi::xml_node& node) {
    if (node) {
        return libj::xml::Element::CPtr(new Element(root, node));
    } else {
        return libj::xml::Element::null();
    }
}

}  // namespace xml
}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_XML_ELEMENT_H_
