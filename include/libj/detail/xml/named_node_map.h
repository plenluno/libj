// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_XML_NAMED_NODE_MAP_H_
#define LIBJ_DETAIL_XML_NAMED_NODE_MAP_H_

#include <libj/xml/attr.h>
#include <libj/xml/document.h>
#include <libj/xml/named_node_map.h>

#include <pugixml.hpp>

#include <assert.h>

namespace libj {
namespace detail {
namespace xml {

libj::xml::Attr::Ptr createAttr(
    libj::xml::Document::CPtr root,
    const pugi::xml_attribute& attr);

class NamedNodeMap : public libj::xml::NamedNodeMap {
 public:
    NamedNodeMap(
        libj::xml::Document::CPtr root,
        const pugi::xml_node& node)
        : root_(root)
        , node_(node.internal_object()) {
        assert(!!root_);
    }

    virtual Size length() const {
        if (!node_) return 0;

        Size len = 0;
        pugi::xml_attribute attr = node_.first_attribute();
        while (attr) {
            len++;
            attr = attr.next_attribute();
        }
        return len;
    }

    virtual libj::xml::Node::Ptr item(Size index) const {
        if (!node_) return libj::xml::Attr::null();

        pugi::xml_attribute attr = node_.first_attribute();
        for (Size i = 0; attr; i++) {
            if (i == index) {
                return createAttr(root_, attr);
            } else {
                attr = attr.next_attribute();
            }
        }

        return libj::xml::Attr::null();
    }

    virtual libj::xml::Node::Ptr getNamedItem(String::CPtr name) const {
        if (!name || !node_) return libj::xml::Attr::null();

        pugi::xml_attribute attr = node_.attribute(
            reinterpret_cast<const pugi::char_t*>(name->data()));
        if (attr) {
            return createAttr(root_, attr);
        } else {
            return libj::xml::Attr::null();
        }
    }

    virtual String::CPtr toString() const {
        return String::create();
    }

 private:
    libj::xml::Document::CPtr root_;
    pugi::xml_node node_;
};

}  // namespace xml
}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_XML_NAMED_NODE_MAP_H_
