// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_XML_UTIL_H_
#define LIBJ_DETAIL_XML_UTIL_H_

#include <libj/string.h>

#include <assert.h>
#include <pugixml.hpp>

namespace libj {
namespace detail {
namespace xml {

inline String::CPtr createString(const pugi::char_t* s) {
    assert(sizeof(pugi::char_t) == sizeof(Char));

#ifdef LIBJ_USE_UTF32
    return String::create(s, String::UTF32);
#else
    return String::create(s, String::UTF16);
#endif
}

inline pugi::xml_node findNode(const pugi::xml_node& from) {
    pugi::xml_node node = from;
    while (node) {
        if (node.type() == pugi::node_declaration) {
            node = node.next_sibling();
        } else {
            return node;
        }
    }
    return node;
}

inline pugi::xml_node rfindNode(const pugi::xml_node& from) {
    pugi::xml_node node = from;
    while (node) {
        if (node.type() == pugi::node_declaration) {
            node = node.previous_sibling();
        } else {
            return node;
        }
    }
    return node;
}

}  // namespace xml
}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_XML_UTIL_H_
