// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/array_list.h"
#include "libj/detail/generic_array_list.h"

namespace libj {

class ArrayListImpl : public ArrayList {
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
        GenericArrayList<Value>* sl = list_->subList(from, to);
        if (sl) {
            return Ptr(new ArrayListImpl(sl));
        } else {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }
    }

 private:
    class IteratorImpl : public Iterator {
        friend class ArrayListImpl;

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
        GenericArrayList<Value>::Iterator itr_;

        IteratorImpl(const GenericArrayList<Value>* list)
            : itr_(list->iterator()) {}
    };

    class ReverseIteratorImpl : public Iterator {
        friend class ArrayListImpl;

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
        GenericArrayList<Value>::ReverseIterator itr_;

        ReverseIteratorImpl(const GenericArrayList<Value>* list)
            : itr_(list->reverseIterator()) {}
    };

 public:
    Iterator::Ptr iterator() const {
        return Iterator::Ptr(new IteratorImpl(list_));
    }

    Iterator::Ptr reverseIterator() const {
        return Iterator::Ptr(new ReverseIteratorImpl(list_));
    }

 private:
    GenericArrayList<Value>* list_;

    ArrayListImpl() : list_(new GenericArrayList<Value>()) {}

    ArrayListImpl(GenericArrayList<Value>* list) : list_(list) {}

 public:
    static Ptr create() {
        return Ptr(new ArrayListImpl());
    }

    virtual ~ArrayListImpl() {
        delete list_;
    }
};

ArrayList::Ptr ArrayList::create() {
    return ArrayListImpl::create();
}

}  // namespace libj
