// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/xml.h>

namespace libj {
namespace xml {

static String::CPtr error = String::create(
    "<team></member>"
);

static String::CPtr sample = String::create(
    "<team name=\"foo\">\n"
        "\t<member>abc</member>\n"
        "\t<member>xyz</member>\n"
    "</team>\n"
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
    Document::CPtr doc = Document::parse(sample);
    ASSERT_TRUE(doc->toString()->equals(sample));
}

}  // namespace xml
}  // namespace libj
