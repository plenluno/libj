// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_XML_NODE_LIST_H_
#define LIBJ_DETAIL_XML_NODE_LIST_H_

#include <libj/xml/document.h>
#include <libj/xml/node_list.h>
#include <libj/detail/xml/util.h>

namespace libj {
namespace detail {
namespace xml {

libj::xml::Node::CPtr createNode(
    libj::xml::Document::CPtr root,
    const pugi::xml_node& node);

class NodeList : public libj::xml::NodeList {
 public:
    NodeList(
        libj::xml::Document::CPtr root,
        const pugi::xml_node& node)
        : root_(root)
        , node_(node.internal_object()) {
        assert(!!root_);
    }

    virtual Size length() const {
        if (!node_) return 0;

        Size len = 0;
        pugi::xml_node node = findNode(node_.first_child());
        while (node) {
            len++;
            node = findNode(node.next_sibling());
        }
        return len;
    }

    virtual libj::xml::Node::CPtr item(Size index) const {
        if (!node_) return libj::xml::Node::null();

        pugi::xml_node node = findNode(node_.first_child());
        for (Size i = 0; node; i++) {
            if (i == index) {
                return createNode(root_, node);
            } else {
                node = findNode(node.next_sibling());
            }
        }
        return libj::xml::Node::null();
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

#endif  // LIBJ_DETAIL_XML_NODE_LIST_H_
