// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_XML_DOCUMENT_H_
#define LIBJ_DETAIL_XML_DOCUMENT_H_

#include <libj/xml/document.h>
#include <libj/detail/xml/attr.h>

namespace libj {
namespace detail {
namespace xml {

class Document : public Node<libj::xml::Document> {
 public:
    static CPtr parse(String::CPtr str) {
        if (!str) return null();

        Document* doc(new Document());
#ifdef LIBJ_USE_UTF32
        pugi::xml_encoding encoding = pugi::encoding_utf32;
#else
        pugi::xml_encoding encoding = pugi::encoding_utf16;
#endif
        pugi::xml_parse_result res = doc->doc_.load_buffer(
            str->data(),
            str->length() * sizeof(Char),
            pugi::parse_full,
            encoding);

        if (res.status == pugi::status_ok) {
            return CPtr(doc);
        } else {
            delete doc;
            return null();
        }
    }

    Document() {
        node_ = doc_;
    }

 private:
    pugi::xml_document doc_;
};

}  // namespace xml
}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_XML_DOCUMENT_H_
