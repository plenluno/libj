// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_LIST_H_
#define LIBJ_TYPED_LIST_H_

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

#endif  // LIBJ_TYPED_LIST_H_
