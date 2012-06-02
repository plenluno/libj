// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/typed_array_list.h"

namespace libj {

template<typename T>
class TypedArrayListImpl : public TypedArrayList<T> {
 private:
    Boolean match(const Value& v) {
        TypeId id = Type<T>::id();
        return v.type() == id || v.instanceOf(id);
    }

 public:
    Size size() const {
        return list_->size();
    }

    Boolean add(const Value& v) {
        if (match(v)) {
            return list_->add(v);
        } else {
            return false;
        }
    }

    Boolean add(Size i, const Value& v) {
        if (match(v)) {
            return list_->add(i, v);
        } else {
            return false;
        }
    }

    Boolean set(Size i, const Value& v) {
        if (match(v)) {
            return list_->set(i, v);
        } else {
            return false;
        }
    }

    Value get(Size i) const {
        return list_->get(i);
    }

    /*
    T getTyped(Size i) const {
    }
    */

    Value remove(Size i) {
        return list_->remove(i);
    }

    bool remove(const Value& v) {
        return list_->remove(v);
    }

    void clear() {
        return list_->clear();
    }

    ArrayList::Ptr clone() const {
        return list_->clone();
    }

    String::CPtr toString() const {
        return list_->toString();
    }

    Iterator::Ptr iterator() const {
        return list_->iterator();
    }

 public:
    static typename TypedArrayList<T>::Ptr create() {
        typename TypedArrayList<T>::Ptr p(new TypedArrayListImpl());
        return p;
    }

 private:
    TypedArrayListImpl()
        : list_(ArrayList::create()) {}

    ArrayList::Ptr list_;
};

template<typename T>
typename TypedArrayList<T>::Ptr TypedArrayList<T>::create() {
    typename TypedArrayList<T>::Ptr p(new TypedArrayListImpl<T>());
    return p;
}

}  // namespace libj

