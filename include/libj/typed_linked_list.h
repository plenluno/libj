// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_LINKED_LIST_H_
#define LIBJ_TYPED_LINKED_LIST_H_

#include "libj/linked_list.h"
#include "libj/exception.h"
#include "libj/string.h"
#include "libj/typed_iterator.h"

namespace libj {

template<typename T>
class TypedLinkedList : LIBJ_LINKED_LIST_TEMPLATE(TypedLinkedList<T>)
 protected:
    Boolean match(const Value& v) {
        TypeId id = Type<T>::id();
        Boolean result = v.type() == id;
#ifdef LIBJ_USE_EXCEPTION
        if (!result)
            LIBJ_THROW(Error::ILLEGAL_TYPE);
#endif  // LIBJ_USE_EXCEPTION
        return result;
    }

 public:
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

    Value subList(Size from, Size to) const {
        if (to > size() || from > to) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }

        TypedLinkedList* a = new TypedLinkedList();
        for (Size i = from; i < to; i++) {
            a->list_->add(get(i));
        }
        return Ptr(a);
    }

    void clear() {
        return list_->clear();
    }

    Value get(Size i) const {
        return list_->get(i);
    }

    Iterator::Ptr iterator() const {
        return list_->iterator();
    }

    Value remove(Size i) {
        return list_->remove(i);
    }

    Boolean remove(const Value& v) {
        return list_->remove(v);
    }

    Size size() const {
        return list_->size();
    }

    String::CPtr toString() const {
        return list_->toString();
    }

#ifdef LIBJ_USE_EXCEPTION
    T getTyped(Size i) const {
        if (i >= size()) {
            LIBJ_THROW(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            Value v = list_->get(i);
            T t;
            if (to<T>(v, &t)) {
                return t;
            } else {
                LIBJ_THROW(Error::ILLEGAL_STATE);
            }
        }
    }

    typename TypedIterator<T>::Ptr iteratorTyped() const {
        return TypedIterator<T>::create(iterator());
    }
#endif  // LIBJ_USE_EXCEPTION

 public:
    static Ptr create() {
        return Ptr(new TypedLinkedList());
    }

    static Ptr create(LinkedList::CPtr a) {
        Ptr ta(new TypedLinkedList());
        Iterator::Ptr itr = a->iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            if (ta->match(v)) {
                ta->add(v);
            } else {
                return null();
            }
        }
        return ta;
    }

 protected:
    TypedLinkedList() : list_(LinkedList::create()) {}

    LinkedList::Ptr list_;
};

}  // namespace libj

#endif  // LIBJ_TYPED_LINKED_LIST_H_
