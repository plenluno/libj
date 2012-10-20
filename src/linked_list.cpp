// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/linked_list.h"
#include "libj/detail/generic_linked_list.h"

namespace libj {

class LinkedListImpl : public LinkedList {
 public:
    Boolean add(const Value& v) {
        return list_->addTyped(v);
    }

    Boolean add(Size i, const Value& v) {
        return list_->addTyped(i, v);
    }

    Boolean set(Size i, const Value& v) {
        return list_->setTyped(i, v);
    }

    Value get(Size i) const {
        return list_->get(i);
    }

    Value remove(Size i) {
        return list_->remove(i);
    }

    Boolean remove(const Value& v) {
        return list_->remove(v);
    }

    void clear() {
        list_->clear();
    }

    Size size() const {
        return list_->size();
    }

    Value subList(Size from, Size to) const {
        GenericLinkedList<Value>* sl = list_->subList(from, to);
        if (sl) {
            return Ptr(new LinkedListImpl(sl));
        } else {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }
    }

 private:
    class IteratorImpl : public Iterator {
        friend class LinkedListImpl;

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
        GenericLinkedList<Value>::Iterator itr_;

        IteratorImpl(const GenericLinkedList<Value>* list)
            : itr_(list->iterator()) {}
    };

 public:
    Iterator::Ptr iterator() const {
        return Iterator::Ptr(new IteratorImpl(list_));
    }

 private:
    GenericLinkedList<Value>* list_;

    LinkedListImpl() : list_(new GenericLinkedList<Value>()) {}

    LinkedListImpl(GenericLinkedList<Value>* list) : list_(list) {}

 public:
    static Ptr create() {
        return Ptr(new LinkedListImpl());
    }

    virtual ~LinkedListImpl() {
        delete list_;
    }
};

LinkedList::Ptr LinkedList::create() {
    return LinkedListImpl::create();
}

}  // namespace libj
