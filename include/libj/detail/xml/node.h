// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_XML_NODE_H_
#define LIBJ_DETAIL_XML_NODE_H_

#include <libj/endian.h>
#include <libj/xml/document.h>
#include <libj/xml/node_list.h>
#include <libj/xml/named_node_map.h>
#include <libj/detail/xml/node_list.h>
#include <libj/detail/xml/named_node_map.h>

#include <pugixml.hpp>

#include <assert.h>

namespace libj {
namespace detail {
namespace xml {

class StringWriter : public pugi::xml_writer {
 public:
    StringWriter() : str_(String::create()) {}

    virtual void write(const void* data, size_t size) {
        static const Boolean bigEndian = endian() == BIG;

        String::CPtr d;
#ifdef LIBJ_USE_UTF32
        if (bigEndian) {
            d = String::create(data, String::UTF32BE, size >> 2);
        } else {
            d = String::create(data, String::UTF32LE, size >> 2);
        }
#else
        if (bigEndian) {
            d = String::create(data, String::UTF16BE, size >> 1);
        } else {
            d = String::create(data, String::UTF16LE, size >> 1);
        }
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
        , node_() {}

    Node(
        libj::xml::Document::CPtr root,
        const pugi::xml_node& node)
        : root_(root)
        , node_(node.internal_object()) {}

    virtual String::CPtr nodeName() const {
        return createString(node_.name());
    }

    virtual String::CPtr nodeValue() const {
        return createString(node_.value());
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
        case pugi::node_declaration:
            // TODO(plenluno): implement
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
        pugi::xml_node child = node_.first_child();
        if (child) {
            return libj::xml::Node::CPtr(new Node(root(), child));
        } else {
            return libj::xml::Node::null();
        }
    }

    virtual libj::xml::Node::CPtr lastChild() const {
        pugi::xml_node child = node_.last_child();
        if (child) {
            return libj::xml::Node::CPtr(new Node(root(), child));
        } else {
            return libj::xml::Node::null();
        }
    }

    virtual libj::xml::Node::CPtr previousSibling() const {
        pugi::xml_node node = node_.previous_sibling();
        if (node) {
            return libj::xml::Node::CPtr(new Node(root(), node));
        } else {
            return libj::xml::Node::null();
        }
    }

    virtual libj::xml::Node::CPtr nextSibling() const {
        pugi::xml_node node = node_.next_sibling();
        if (node) {
            return libj::xml::Node::CPtr(new Node(root(), node));
        } else {
            return libj::xml::Node::null();
        }
    }

    virtual libj::xml::NamedNodeMap::CPtr attributes() const {
        if (node_.type() == pugi::node_element) {
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

 public:  // Document
    virtual libj::xml::Attr::CPtr createAttribute(String::CPtr name) const {
        return libj::xml::Attr::null();
    }

 public:  // Attr
    virtual String::CPtr name() const {
        return String::null();
    }

    virtual String::CPtr value() const {
        return String::null();
    }

 protected:
    static String::CPtr createString(const pugi::char_t* s) {
        static const Boolean bigEndian = endian() == BIG;

        assert(sizeof(pugi::char_t) == sizeof(Char));
#ifdef LIBJ_USE_UTF32
        if (bigEndian) {
            return String::create(s, String::UTF32BE);
        } else {
            return String::create(s, String::UTF32LE);
        }
#else
        if (bigEndian) {
            return String::create(s, String::UTF16BE);
        } else {
            return String::create(s, String::UTF16LE);
        }
#endif
    }

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
};

inline libj::xml::Node::CPtr createNode(
    libj::xml::Document::CPtr root,
    const pugi::xml_node& node) {
    return libj::xml::Node::CPtr(new Node<libj::xml::Node>(root, node));
}

}  // namespace xml
}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_XML_NODE_H_
