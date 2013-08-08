// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_XML_NODE_H_
#define LIBJ_DETAIL_XML_NODE_H_

#include <libj/this.h>
#include <libj/symbol.h>
#include <libj/xml/attr.h>
#include <libj/xml/element.h>
#include <libj/xml/document.h>
#include <libj/xml/node_list.h>
#include <libj/xml/named_node_map.h>
#include <libj/detail/xml/node_list.h>
#include <libj/detail/xml/named_node_map.h>

namespace libj {
namespace detail {
namespace xml {

libj::xml::Element::CPtr createElement(
    libj::xml::Document::CPtr root,
    const pugi::xml_node& node);

class StringWriter : public pugi::xml_writer {
 public:
    StringWriter() : str_(String::create()) {}

    virtual void write(const void* data, size_t size) {
#ifdef LIBJ_USE_UTF32
        String::CPtr d = String::create(data, String::UTF32, size >> 2);
#else
        String::CPtr d = String::create(data, String::UTF16, size >> 1);
#endif
        str_ = str_->concat(d);
    }

    String::CPtr result() { return str_; }

 private:
    String::CPtr str_;
};

template<typename I>
class Node : public I {
 public:
    Node()
        : root_(libj::xml::Document::null())
        , node_()
        , name_(String::null())
        , value_(String::null()) {}

    Node(
        libj::xml::Document::CPtr root,
        const pugi::xml_node& node)
        : root_(root)
        , node_(node.internal_object())
        , name_(createString(node_.name()))
        , value_(createString(node_.value())) {}

    virtual String::CPtr nodeName() const {
        LIBJ_STATIC_SYMBOL_DEF(symCdataSection,     "#cdata-section");
        LIBJ_STATIC_SYMBOL_DEF(symComment,          "#comment");
        LIBJ_STATIC_SYMBOL_DEF(symDocument,         "#document");
        LIBJ_STATIC_SYMBOL_DEF(symDocumentFragment, "#document-fragment");
        LIBJ_STATIC_SYMBOL_DEF(symText,             "#text");

        switch (nodeType()) {
        case I::CDATA_SECTION_NODE:
            return symCdataSection;
        case I::COMMENT_NODE:
            return symComment;
        case I::DOCUMENT_NODE:
            return symDocument;
        case I::DOCUMENT_FRAGMENT_NODE:
            return symDocumentFragment;
        case I::TEXT_NODE:
            return symText;
        default:
            return name_;
        }
    }

    virtual String::CPtr nodeValue() const {
        switch (nodeType()) {
        case I::DOCUMENT_NODE:
        case I::DOCUMENT_FRAGMENT_NODE:
        case I::DOCUMENT_TYPE_NODE:
        case I::ELEMENT_NODE:
        case I::ENTITY_NODE:
        case I::ENTITY_REFERENCE_NODE:
        case I::NOTATION_NODE:
            return String::null();
        default:
            return value_;
        }
    }

    virtual typename I::NodeType nodeType() const {
        pugi::xml_node_type type = node_.type();
        switch (type) {
        case pugi::node_document:
            return I::DOCUMENT_NODE;
        case pugi::node_element:
            return I::ELEMENT_NODE;
        case pugi::node_pcdata:
            return I::TEXT_NODE;
        case pugi::node_cdata:
            return I::CDATA_SECTION_NODE;
        case pugi::node_comment:
            return I::COMMENT_NODE;
        case pugi::node_pi:
            return I::PROCESSING_INSTRUCTION_NODE;
        case pugi::node_doctype:
            return I::DOCUMENT_TYPE_NODE;
        default:
            assert(false);
            return I::DOCUMENT_NODE;
        }
    }

    virtual libj::xml::Node::CPtr parentNode() const {
        pugi::xml_node parent = node_.parent();
        if (parent) {
            return libj::xml::Node::CPtr(new Node(root(), parent));
        } else {
            return libj::xml::Node::null();
        }
    }

    virtual libj::xml::NodeList::CPtr childNodes() const {
        return libj::xml::NodeList::CPtr(new NodeList(root(), node_));
    }

    virtual libj::xml::Node::CPtr firstChild() const {
        pugi::xml_node child = findNode(node_.first_child());
        if (child) {
            return libj::xml::Node::CPtr(new Node(root(), child));
        } else {
            return libj::xml::Node::null();
        }
    }

    virtual libj::xml::Node::CPtr lastChild() const {
        pugi::xml_node child = rfindNode(node_.last_child());
        if (child) {
            return libj::xml::Node::CPtr(new Node(root(), child));
        } else {
            return libj::xml::Node::null();
        }
    }

    virtual libj::xml::Node::CPtr previousSibling() const {
        pugi::xml_node node = rfindNode(node_.previous_sibling());
        if (node) {
            return libj::xml::Node::CPtr(new Node(root(), node));
        } else {
            return libj::xml::Node::null();
        }
    }

    virtual libj::xml::Node::CPtr nextSibling() const {
        pugi::xml_node node = findNode(node_.next_sibling());
        if (node) {
            return libj::xml::Node::CPtr(new Node(root(), node));
        } else {
            return libj::xml::Node::null();
        }
    }

    virtual libj::xml::NamedNodeMap::CPtr attributes() const {
        if (nodeType() == I::ELEMENT_NODE) {
            return libj::xml::NamedNodeMap::CPtr(
                new NamedNodeMap(root(), node_));
        } else {
            return NamedNodeMap::null();
        }
    }

    virtual libj::xml::Document::CPtr ownerDocument() const {
        return root();
    }

    virtual Boolean hasChildNodes() const {
        return !!node_.first_child();
    }

    virtual Boolean hasAttributes() const {
        return !!node_.first_attribute();
    }

    virtual String::CPtr toString() const {
#ifdef LIBJ_USE_UTF32
        pugi::xml_encoding encoding = pugi::encoding_utf32;
#else
        pugi::xml_encoding encoding = pugi::encoding_utf16;
#endif
        StringWriter writer;
        node_.print(writer, PUGIXML_TEXT("\t"), pugi::format_default, encoding);
        return writer.result();
    }

 public:
    virtual libj::xml::Attr::CPtr asAttr() const {
        return libj::xml::Attr::null();
    }

    virtual libj::xml::Document::CPtr asDocument() const {
        return libj::xml::Document::null();
    }

    virtual libj::xml::Element::CPtr asElement() const {
        if (nodeType() == I::ELEMENT_NODE) {
            return createElement(root_, node_);
        } else {
            return libj::xml::Element::null();
        }
    }

 public:  // Attr
    virtual String::CPtr name() const {
        return String::null();
    }

    virtual String::CPtr value() const {
        return String::null();
    }

    virtual libj::xml::Element::CPtr ownerElement() const {
        return libj::xml::Element::null();
    }

 public:  // Element
    virtual String::CPtr tagName() const {
        return String::null();
    }

    virtual String::CPtr getAttribute(String::CPtr name) const {
        return String::null();
    }

    virtual libj::xml::Attr::CPtr getAttributeNode(String::CPtr name) const {
        return libj::xml::Attr::null();
    }

    virtual Boolean hasAttribute(String::CPtr name) const {
        return false;
    }

 protected:
    libj::xml::Document::CPtr root() const {
        if (root_) {
            return root_;
        } else {
            assert(this->nodeType() == I::DOCUMENT_NODE);
            return LIBJ_STATIC_CPTR_CAST(libj::xml::Document)(this->self());
        }
    }

 protected:
    libj::xml::Document::CPtr root_;
    pugi::xml_node node_;
    String::CPtr name_;
    String::CPtr value_;
};

inline libj::xml::Node::CPtr createNode(
    libj::xml::Document::CPtr root,
    const pugi::xml_node& node) {
    if (node) {
        return libj::xml::Node::CPtr(new Node<libj::xml::Node>(root, node));
    } else {
        return libj::xml::Node::null();
    }
}

}  // namespace xml
}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_XML_NODE_H_
