// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_BRIDGE_DEPRECATED_MACRO_H_
#define LIBJ_BRIDGE_DEPRECATED_MACRO_H_

#define LIBJ_STATUS_IMPL(S) \
public: \
    Int code() const { \
        return S->code(); \
    } \
    String::CPtr message() const { \
        return S->message(); \
    } \
    String::CPtr toString() const { \
        return S->toString(); \
    }

#define LIBJ_COLLECTION_IMPL(C) \
public: \
    Boolean add(const Value& v) { \
        return C->add(v); \
    } \
    void clear() { \
        C->clear(); \
    } \
    Iterator::Ptr iterator() const { \
        return C->iterator(); \
    } \
    Boolean remove(const Value& v) { \
        return C->remove(v); \
    } \
    Size size() const { \
        return C->size(); \
    }

#define LIBJ_LIST_IMPL(L) \
    LIBJ_COLLECTION_IMPL(L) \
public: \
    Boolean add(Size i, const Value& v) { \
        return L->add(i, v); \
    } \
    Value get(Size i) const { \
        return L->get(i); \
    } \
    Value remove(Size i) { \
        return L->remove(i); \
    } \
    Iterator::Ptr reverseIterator() const { \
        return L->reverseIterator(); \
    } \
    Boolean set(Size i, const Value& v) { \
        return L->set(i, v); \
    }

#define LIBJ_MAP_IMPL(M) \
public: \
    void clear() { \
        M->clear(); \
    } \
    Boolean containsKey(const Value& key) const { \
        return M->containsKey(key); \
    } \
    Boolean containsValue(const Value& val) const { \
        return M->containsValue(val); \
    } \
    Value get(const Value& key) const { \
        return M->get(key); \
    } \
    Set::CPtr keySet() const { \
        return M->keySet(); \
    } \
    Value put(const Value& key, const Value& val) { \
        return M->put(key, val); \
    } \
    Value remove(const Value& key) { \
        return M->remove(key); \
    } \
    Size size() const { \
        return M->size(); \
    } \
    Boolean isEmpty() const { \
        return M->isEmpty(); \
    }

#define LIBJ_JS_OBJECT_IMPL(JO) \
    LIBJ_MAP_IMPL(JO) \
public: \
    String::CPtr toString() const { \
        return JO->toString(); \
    } \
    virtual Boolean hasProperty(const Value& name) const { \
        return JO->hasProperty(name); \
    } \
    virtual Value getProperty(const Value& name) const { \
        return JO->getProperty(name); \
    } \
    virtual Value setProperty(const Value& name, const Value& val) { \
        return JO->setProperty(name, val); \
    } \
    virtual Value deleteProperty(const Value& name) { \
        return JO->deleteProperty(name); \
    }

#define LIBJ_JS_ARRAY_BUFFER_IMPL(B) \
public: \
    Size length() const { \
        return B->length(); \
    } \
    const void* data() const { \
        return B->data(); \
    } \
    Boolean shrink(Size length) { \
        return B->shrink(length); \
    } \
    Boolean getInt8( \
        Size byteOffset, Byte* value) const { \
        return B->getInt8(byteOffset, value); \
    } \
    Boolean getUInt8( \
        Size byteOffset, UByte* value) const { \
        return B->getUInt8(byteOffset, value); \
    } \
    Boolean getInt16( \
        Size byteOffset, Short* value, Boolean littleEndian = false) const { \
        return B->getInt16(byteOffset, value, littleEndian); \
    } \
    Boolean getUInt16( \
        Size byteOffset, UShort* value, Boolean littleEndian = false) const { \
        return B->getUInt16(byteOffset, value, littleEndian); \
    } \
    Boolean getInt32( \
        Size byteOffset, Int* value, Boolean littleEndian = false) const { \
        return B->getInt32(byteOffset, value, littleEndian); \
    } \
    Boolean getUInt32( \
        Size byteOffset, UInt* value, Boolean littleEndian = false) const { \
        return B->getUInt32(byteOffset, value, littleEndian); \
    } \
    Boolean getFloat32( \
        Size byteOffset, Float* value, Boolean littleEndian = false) const { \
        return B->getFloat32(byteOffset, value, littleEndian); \
    } \
    Boolean getFloat64( \
        Size byteOffset, Double* value, Boolean littleEndian = false) const { \
        return B->getFloat64(byteOffset, value, littleEndian); \
    } \
    Boolean setInt8( \
        Size byteOffset, Byte value) { \
        return B->setInt8(byteOffset, value); \
    } \
    Boolean setUInt8( \
        Size byteOffset, UByte value) { \
        return B->setUInt8(byteOffset, value); \
    } \
    Boolean setInt16( \
        Size byteOffset, Short value, Boolean littleEndian = false) { \
        return B->setInt16(byteOffset, value, littleEndian); \
    } \
    Boolean setUInt16( \
        Size byteOffset, UShort value, Boolean littleEndian = false) { \
        return B->setUInt16(byteOffset, value, littleEndian); \
    } \
    Boolean setInt32( \
        Size byteOffset, Int value, Boolean littleEndian = false) { \
        return B->setInt32(byteOffset, value, littleEndian); \
    } \
    Boolean setUInt32( \
        Size byteOffset, UInt value, Boolean littleEndian = false) { \
        return B->setUInt32(byteOffset, value, littleEndian); \
    } \
    Boolean setFloat32( \
        Size byteOffset, Float value, Boolean littleEndian = false) { \
        return B->setFloat32(byteOffset, value, littleEndian); \
    } \
    Boolean setFloat64( \
        Size byteOffset, Double value, Boolean littleEndian = false) { \
        return B->setFloat64(byteOffset, value, littleEndian); \
    } \
    String::CPtr toString() const { \
        return B->toString(); \
    }

#define LIBJ_TYPED_LIST_IMPL(L) \
public: \
    Boolean add(const Value& v) { \
        return list_->add(v); \
    } \
    Boolean addTyped(const T& t) { \
        return list_->addTyped(t); \
    } \
    Boolean add(Size i, const Value& v) { \
        return list_->add(i, v); \
    } \
    Boolean addTyped(Size i, const T& t) { \
        return list_->addTyped(i, t); \
    } \
    Boolean set(Size i, const Value& v) { \
        return list_->set(i, v); \
    } \
    Boolean setTyped(Size i, const T& t) { \
        return list_->set(i, t); \
    } \
    Value get(Size i) const { \
        return list_->get(i); \
    } \
    T getTyped(Size i) const { \
        return list_->getTyped(i); \
    } \
    Value remove(Size i) { \
        return list_->remove(i); \
    } \
    T removeTyped(Size i) { \
        return list_->removeTyped(i); \
    } \
    Boolean remove(const Value& v) { \
        return list_->remove(v); \
    } \
    Boolean removeTyped(const T& t) { \
        return list_->removeTyped(t); \
    } \
    T shiftTyped() { \
        return removeTyped(static_cast<Size>(0)); \
    } \
    Size unshiftTyped(const T& t) { \
        addTyped(0, t); \
        return size(); \
    } \
    Size pushTyped(const T& t) { \
        addTyped(t); \
        return size(); \
    } \
    T popTyped() { \
        return removeTyped(size() - 1); \
    } \
    void clear() { \
        return list_->clear(); \
    } \
    Size size() const { \
        return list_->size(); \
    }

#endif  // LIBJ_BRIDGE_DEPRECATED_MACRO_H_
