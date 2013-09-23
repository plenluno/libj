// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/xml.h>

namespace libj {
namespace xml {

LIBJ_STATIC_CONST_STRING_DEF(error,
    "<team></member>"
);

LIBJ_STATIC_CONST_STRING_DEF(sample,
    "<team name=\"foo\">  "
        "\t<member>abc</member>  "
        "\t<member>xyz</member>  "
    "</team>  "
);

LIBJ_STATIC_CONST_STRING_DEF(xhtml,
    "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
    "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\""
        "\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">"
    "<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"ja\" xml:lang=\"ja\">"
        "<head><title>title</title></head>"
        "<body></body>"
    "</html>"
);

TEST(GTestXmlDom, TestParse) {
    Document::CPtr doc = Document::parse(String::null());
    ASSERT_TRUE(!doc);

    doc = Document::parse(error);
    ASSERT_TRUE(!doc);

    doc = Document::parse(sample);
    ASSERT_TRUE(!!doc);
    ASSERT_EQ(Node::DOCUMENT_NODE, doc->nodeType());
}

TEST(GTestXmlDom, TestNodeList) {
    Document::CPtr doc = Document::parse(sample);
    NodeList::CPtr list = doc->childNodes();
    ASSERT_EQ(1, list->length());

    Node::CPtr node = list->item(0);
    ASSERT_EQ(Node::ELEMENT_NODE, node->nodeType());
    ASSERT_TRUE(node->nodeName()->equals(String::create("team")));
    ASSERT_TRUE(!list->item(1));

    list = node->childNodes();
    ASSERT_EQ(2, list->length());
    node = list->item(1);
    ASSERT_EQ(Node::ELEMENT_NODE, node->nodeType());
    ASSERT_TRUE(node->nodeName()->equals(String::create("member")));
    ASSERT_TRUE(!list->item(2));

    list = node->childNodes();
    ASSERT_EQ(1, list->length());
    node = list->item(0);
    ASSERT_EQ(Node::TEXT_NODE, node->nodeType());
    ASSERT_TRUE(node->nodeValue()->equals(String::create("xyz")));
}

TEST(GTestXmlDom, TestNamedNodeMap) {
    Document::CPtr doc = Document::parse(sample);
    ASSERT_TRUE(!doc->attributes());

    NamedNodeMap::CPtr map = doc->firstChild()->attributes();
    ASSERT_TRUE(!!map);
    ASSERT_EQ(1, map->length());

    Node::CPtr node = map->item(0);
    ASSERT_TRUE(!!node);
    ASSERT_TRUE(node->nodeName()->equals(String::create("name")));
    ASSERT_TRUE(node->nodeValue()->equals(String::create("foo")));
    ASSERT_TRUE(!map->item(1));

    node = map->getNamedItem(String::create("name"));
    ASSERT_TRUE(!!node);
    ASSERT_TRUE(node->nodeName()->equals(String::create("name")));
    ASSERT_TRUE(node->nodeValue()->equals(String::create("foo")));

    node = map->getNamedItem(String::create("foo"));
    ASSERT_TRUE(!node);
}

TEST(GTestXmlDom, TestElement) {
    Document::CPtr doc = Document::parse(sample);
    ASSERT_TRUE(!doc->asAttr());
    ASSERT_TRUE(!doc->asElement());
    ASSERT_TRUE(!!doc->asDocument());

    Node::CPtr node = doc->firstChild();
    ASSERT_TRUE(!node->asAttr());
    ASSERT_TRUE(!!node->asElement());
    ASSERT_TRUE(!node->asDocument());

    Element::CPtr element = node->asElement();
    String::CPtr tag = element->tagName();
    String::CPtr attrVal1 = element->getAttribute(String::create("name"));
    String::CPtr attrVal2 = element->getAttribute(String::create("foo"));
    String::CPtr attrVal3 = element->getAttribute(String::null());
    ASSERT_TRUE(tag->equals(String::create("team")));
    ASSERT_TRUE(attrVal1->equals(String::create("foo")));
    ASSERT_TRUE(attrVal2->equals(String::create()));
    ASSERT_TRUE(!attrVal3);
    ASSERT_TRUE(element->hasAttribute(String::create("name")));
    ASSERT_FALSE(element->hasAttribute(String::create("foo")));
    ASSERT_FALSE(element->hasAttribute(String::null()));

    Attr::CPtr attr1 = element->getAttributeNode(String::create("name"));
    Attr::CPtr attr2 = element->getAttributeNode(String::create("foo"));
    Attr::CPtr attr3 = element->getAttributeNode(String::null());
    ASSERT_TRUE(!!attr1);
    ASSERT_TRUE(!attr2);
    ASSERT_TRUE(!attr3);
}

TEST(GTestXmlDom, TestAttr) {
    Document::CPtr doc = Document::parse(sample);
    Element::CPtr element = doc->firstChild()->asElement();
    Attr::CPtr attr = element->getAttributeNode(String::create("name"));
    ASSERT_TRUE(!!attr->asAttr());
    ASSERT_TRUE(!attr->asElement());
    ASSERT_TRUE(!attr->asDocument());

    ASSERT_TRUE(attr->name()->equals(String::create("name")));
    ASSERT_TRUE(attr->value()->equals(String::create("foo")));

    Element::CPtr owner = attr->ownerElement();
    ASSERT_TRUE(owner->tagName()->equals(String::create("team")));
}

TEST(GTestXmlDom, TestFirstChild) {
    Document::CPtr doc = Document::parse(sample);
    Node::CPtr node = doc->firstChild()->firstChild()->firstChild();
    ASSERT_TRUE(node->nodeValue()->equals(String::create("abc")));
    ASSERT_TRUE(!node->firstChild());
}

TEST(GTestXmlDom, TestLastChild) {
    Document::CPtr doc = Document::parse(sample);
    Node::CPtr node = doc->lastChild()->lastChild()->lastChild();
    ASSERT_TRUE(node->nodeValue()->equals(String::create("xyz")));
    ASSERT_TRUE(!node->lastChild());
}

TEST(GTestXmlDom, TestParentNode) {
    Document::CPtr doc = Document::parse(sample);
    Node::CPtr node = doc->firstChild()->lastChild()->firstChild();
    node = node->parentNode()->parentNode()->parentNode();
    ASSERT_EQ(Node::DOCUMENT_NODE, node->nodeType());
}

TEST(GTestXmlDom, TestNextSiblingAndPreviousSibling) {
    Document::CPtr doc = Document::parse(sample);
    ASSERT_TRUE(!doc->nextSibling());
    ASSERT_TRUE(!doc->previousSibling());

    Node::CPtr node = doc->firstChild();
    ASSERT_TRUE(!node->nextSibling());
    ASSERT_TRUE(!node->previousSibling());

    Node::CPtr node1 = node->firstChild();
    ASSERT_TRUE(!!node1->nextSibling());
    ASSERT_TRUE(!node1->previousSibling());

    Node::CPtr node2 = node->lastChild();
    ASSERT_TRUE(!node2->nextSibling());
    ASSERT_TRUE(!!node2->previousSibling());
}

TEST(GTestXmlDom, TestHasChildNodes) {
    Document::CPtr doc = Document::parse(sample);
    ASSERT_TRUE(doc->hasChildNodes());

    Node::CPtr node = doc->firstChild();
    ASSERT_TRUE(node->hasChildNodes());

    node = node->firstChild();
    ASSERT_TRUE(node->hasChildNodes());

    node = node->firstChild();
    ASSERT_FALSE(node->hasChildNodes());
}

TEST(GTestXmlDom, TestHasAttributes) {
    Document::CPtr doc = Document::parse(sample);
    ASSERT_FALSE(doc->hasAttributes());

    Node::CPtr node = doc->firstChild();
    ASSERT_TRUE(node->hasAttributes());
}

TEST(GTestXmlDom, TestToString) {
    String::CPtr sample2 =
        sample->replace(String::create("  "), String::create('\n'));

    Document::CPtr doc = Document::parse(sample);
    ASSERT_TRUE(doc->toString()->equals(sample2));

    doc = Document::parse(sample2);
    ASSERT_TRUE(doc->toString()->equals(sample2));
}

TEST(GTestXmlDom, TestXmlDeclaration) {
    Document::CPtr doc = Document::parse(xhtml);
    ASSERT_TRUE(!!doc);
    ASSERT_TRUE(doc->firstChild()->nodeType() == Node::DOCUMENT_TYPE_NODE);
    ASSERT_EQ(2, doc->childNodes()->length());
}

}  // namespace xml
}  // namespace libj
