// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/js_object.h>

namespace libj {

class GTestJsObject : LIBJ_JS_OBJECT(GTestJsObject)
 public:
    static Ptr create() {
        Ptr p(new GTestJsObject());
        return p;
    }

 private:
    JsObject::Ptr jo_;

    GTestJsObject() : jo_(JsObject::create()) {}

    LIBJ_JS_OBJECT_IMPL(jo_);
};

TEST(GTestJsObject, TestToString) {
    JsObject::Ptr obj = JsObject::create();
    ASSERT_TRUE(obj->toString()->equals(String::create("[object Object]")));
}

TEST(GTestJsObject, TestPutAndGet) {
    JsObject::Ptr obj = JsObject::create();
    obj->put(5, String::create("xyz"));
    Value v = obj->get(String::create("5"));
    ASSERT_TRUE(v.equals(String::create("xyz")));
}

TEST(GTestJsObject, TestJsProperty) {
    JsObject::Ptr obj = JsObject::create();
    obj->setProperty(String::create("abc"), 7);
    ASSERT_TRUE(obj->hasProperty(String::create("abc")));
    ASSERT_TRUE(obj->getProperty(String::create("abc")).equals(7));

    obj->deleteProperty(String::create("abc"));
    ASSERT_FALSE(obj->hasProperty(String::create("abc")));
}

TEST(GTestJsObject, TestGetPtr) {
    JsObject::Ptr obj1 = JsObject::create();
    GTestJsObject::Ptr obj2 = GTestJsObject::create();
    obj2->put(obj1, obj1);
    Value v1 = obj2->getPtr<JsObject>(obj1);
    ASSERT_TRUE(v1.equals(obj1));
    Value v2 = obj2->getPtr<JsObject>(String::create("[object Object]"));
    ASSERT_TRUE(v2.equals(obj1));
}

TEST(GTestJsObject, TestGetCPtr) {
    JsObject::Ptr obj = JsObject::create();
    String::CPtr abc = String::create("abc");
    obj->put(abc, abc);
    ASSERT_TRUE(obj->getCPtr<String>(abc)->equals(abc));

    obj = GTestJsObject::create();
    obj->put(abc, abc);
    ASSERT_TRUE(obj->getCPtr<String>(abc)->equals(abc));

    JsObject::Ptr obj2 = JsObject::create();
    obj->put(abc, obj2);
    ASSERT_TRUE(obj->getCPtr<JsObject>(abc)->equals(obj2));
}

}  // namespace libj
