// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_LINKED_LIST_H_
#define LIBJ_TYPED_LINKED_LIST_H_

#include "libj/linked_list.h"
#include "libj/typed_iterator.h"
#include "libj/detail/generic_linked_list.h"

namespace libj {

template<typename T>
class TypedLinkedList : LIBJ_LINKED_LIST_TEMPLATE(TypedLinkedList<T>)
 public:
    Boolean add(const Value& v) {
        return list_->add(v);
    }

    Boolean addTyped(const T& t) {
        return list_->addTyped(t);
    }

    Boolean add(Size i, const Value& v) {
        return list_->add(i, v);
    }

    Boolean addTyped(Size i, const T& t) {
        return list_->addTyped(i, t);
    }

    Boolean set(Size i, const Value& v) {
        return list_->set(i, v);
    }

    Boolean setTyped(Size i, const T& t) {
        return list_->set(i, t);
    }

    Value get(Size i) const {
        return list_->get(i);
    }

    T getTyped(Size i) const {
        return list_->getTyped(i);
    }

    Value remove(Size i) {
        return list_->remove(i);
    }

    T removeTyped(Size i) {
        return list_->removeTyped(i);
    }

    Boolean remove(const Value& v) {
        return list_->remove(v);
    }

    Boolean removeTyped(const T& t) {
        return list_->removeTyped(t);
    }

    void clear() {
        return list_->clear();
    }

    Size size() const {
        return list_->size();
    }

    Value subList(Size from, Size to) const {
        GenericLinkedList<T>* sl = list_->subList(from, to);
        if (sl) {
            return Ptr(new TypedLinkedList(sl));
        } else {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }
    }

 private:
    class IteratorImpl : public Iterator {
        friend class TypedLinkedList;

     public:
        Boolean hasNext() const {
            return itr_.hasNext();
        }

        Value next() {
            return itr_.next();
        }

        String::CPtr toString() const {
            return String::create();
        }

     private:
        typename GenericLinkedList<T>::Iterator itr_;

        IteratorImpl(const GenericLinkedList<T>* list)
            : itr_(list->iterator()) {}
    };

    class ReverseIteratorImpl : public Iterator {
        friend class TypedLinkedList;

     public:
        Boolean hasNext() const {
            return itr_.hasNext();
        }

        Value next() {
            return itr_.next();
        }

        String::CPtr toString() const {
            return String::create();
        }

     private:
        typename GenericLinkedList<T>::ReverseIterator itr_;

        ReverseIteratorImpl(const GenericLinkedList<T>* list)
            : itr_(list->reverseIterator()) {}
    };

    class TypedIteratorImpl : public TypedIterator<T> {
        friend class TypedLinkedList;

     public:
        Boolean hasNext() const {
            return itr_.hasNext();
        }

        T next() {
            return itr_.nextTyped();
        }

        String::CPtr toString() const {
            return String::create();
        }

     private:
        typename GenericLinkedList<T>::Iterator itr_;

        TypedIteratorImpl(const GenericLinkedList<T>* list)
            : itr_(list->iterator()) {}
    };

 public:
    Iterator::Ptr iterator() const {
        return Iterator::Ptr(new IteratorImpl(list_));
    }

    Iterator::Ptr reverseIterator() const {
        return Iterator::Ptr(new ReverseIteratorImpl(list_));
    }

    typename TypedIterator<T>::Ptr iteratorTyped() const {
        return typename TypedIterator<T>::Ptr(
                    new TypedIteratorImpl(list_));
    }

    static Ptr create() {
        return Ptr(new TypedLinkedList());
    }

    static Ptr create(Collection::CPtr c) {
        Ptr list(new TypedLinkedList());
        Iterator::Ptr itr = c->iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            T t;
            if (GenericLinkedList<T>::convert(v, &t)) {
                list->addTyped(t);
            } else {
                return null();
            }
        }
        return list;
    }

    virtual ~TypedLinkedList() {
        delete list_;
    }

 protected:
    GenericLinkedList<T>* list_;

    TypedLinkedList() : list_(new GenericLinkedList<T>()) {}

    TypedLinkedList(GenericLinkedList<T>* list) : list_(list) {}
};

}  // namespace libj

#endif  // LIBJ_TYPED_LINKED_LIST_H_
