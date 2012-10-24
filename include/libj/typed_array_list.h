// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_ARRAY_LIST_H_
#define LIBJ_TYPED_ARRAY_LIST_H_

#include "libj/array_list.h"
#include "libj/typed_list.h"
#include "libj/typed_iterator.h"
#include "libj/detail/generic_array_list.h"

namespace libj {

template<typename T>
class TypedArrayList : LIBJ_ARRAY_LIST_TEMPLATE(TypedArrayList<T>)
 public:
    Value subList(Size from, Size to) const {
        GenericArrayList<T>* sl = list_->subList(from, to);
        if (sl) {
            return Ptr(new TypedArrayList(sl));
        } else {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }
    }

 private:
    class IteratorImpl : public Iterator {
        friend class TypedArrayList;

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
        typename GenericArrayList<T>::Iterator itr_;

        IteratorImpl(const GenericArrayList<T>* list)
            : itr_(list->iterator()) {}
    };

    class ReverseIteratorImpl : public Iterator {
        friend class TypedArrayList;

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
        typename GenericArrayList<T>::ReverseIterator itr_;

        ReverseIteratorImpl(const GenericArrayList<T>* list)
            : itr_(list->reverseIterator()) {}
    };

    class TypedIteratorImpl : public TypedIterator<T> {
        friend class TypedArrayList;

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
        typename GenericArrayList<T>::Iterator itr_;

        TypedIteratorImpl(const GenericArrayList<T>* list)
            : itr_(list->iterator()) {}
    };

    class TypedReverseIteratorImpl : public TypedIterator<T> {
        friend class TypedArrayList;

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
        typename GenericArrayList<T>::ReverseIterator itr_;

        TypedReverseIteratorImpl(const GenericArrayList<T>* list)
            : itr_(list->reverseIterator()) {}
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

    typename TypedIterator<T>::Ptr reverseIteratorTyped() const {
        return typename TypedIterator<T>::Ptr(
                    new TypedReverseIteratorImpl(list_));
    }

    static Ptr create() {
        return Ptr(new TypedArrayList());
    }

    static Ptr create(Collection::CPtr c) {
        Ptr list(new TypedArrayList());
        Iterator::Ptr itr = c->iterator();
        while (itr->hasNext()) {
            Value v = itr->next();
            T t;
            if (GenericArrayList<T>::convert(v, &t)) {
                list->addTyped(t);
            } else {
                return null();
            }
        }
        return list;
    }

    virtual ~TypedArrayList() {
        delete list_;
    }

 protected:
    GenericArrayList<T>* list_;

    TypedArrayList() : list_(new GenericArrayList<T>()) {}

    TypedArrayList(GenericArrayList<T>* list) : list_(list) {}

    LIBJ_TYPED_LIST_IMPL(list_);
};

#define LIBJ_TYPED_ARRAY_LIST_TEMPLATE(D, T) public libj::TypedArrayList<T> { \
    LIBJ_MUTABLE_TEMPLATE_DEFS(D<T>, libj::TypedArrayList<T>)

}  // namespace libj

#endif  // LIBJ_TYPED_ARRAY_LIST_H_
