// Copyright (c) 2012 Plenluno All rights reserved.

#include <list>

#include "libj/linked_list.h"
#include "libj/error.h"
#include "libj/exception.h"
#include "libj/string_buffer.h"

namespace libj {

class LinkedListImpl : public LinkedList {
    typedef std::list<Value> container;
    typedef container::iterator it;
    typedef container::const_iterator cit;

 public:
    Size size() const {
        return list_.size();
    }

    Boolean add(const Value& v) {
        list_.push_back(v);
        return true;
    }

    Boolean add(Size i, const Value& v) {
        if (i > list_.size()) {
            return false;
        } else {
            it pos = list_.begin();
            for (; i; i--) ++pos;
            list_.insert(pos, v);
            return true;
        }
    }

    Boolean set(Size i, const Value& v) {
        if (i > list_.size()) {
            return false;
        } else {
            it pos = list_.begin();
            for (; i; i--) ++pos;
            *pos = v;
            return true;
        }
    }

    Value get(Size i) const {
        if (i >= list_.size()) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            cit pos = list_.begin();
            for (; i; i--) ++pos;
            return *pos;
        }
    }

    Value remove(Size i) {
        if (i >= list_.size()) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            it pos = list_.begin();
            for (; i; i--) ++pos;
            Value v = *pos;
            list_.erase(pos);
            return v;
        }
    }

    Boolean remove(const Value& v) {
        for (it i = list_.begin(), e = list_.end(); i != e; ++i) {
            if (!i->compareTo(v)) {
                list_.erase(i);
                return true;
            }
        }
        return false;
    }

    void clear() {
        list_.clear();
    }

    Value subList(Size from, Size to) const {
        if (to > size() || from > to) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }

        LinkedListImpl* ls = new LinkedListImpl();
        LinkedList::Ptr p(ls);
        cit itr = list_.begin();
        for (Size index = 0; index < to; index++, itr++) {
            if (index >= from)
                ls->add(*itr);
        }
        return p;
    }

 private:
    class IteratorImpl : public Iterator {
        friend class LinkedListImpl;
        const container* list_;
        container::const_iterator itr_;

        IteratorImpl(const container *l)
            : list_(l)
            , itr_(l->begin()) {}

     public:
        Boolean hasNext() const {
            return itr_ != list_->end();
        }

        Value next() {
            if (itr_ == list_->end()) {
                LIBJ_HANDLE_ERROR(Error::NO_SUCH_ELEMENT);
            } else {
                Value v = *itr_;
                ++itr_;
                return v;
            }
        }

        String::CPtr toString() const {
            return String::create();
        }
    };

 public:
    Iterator::Ptr iterator() const {
        Iterator::Ptr p(new IteratorImpl(&list_));
        return p;
    }

 private:
    container list_;
    LinkedListImpl() : list_(container()) {}

 public:
    static LinkedList::Ptr create() {
        LinkedList::Ptr p(new LinkedListImpl());
        return p;
    }
};

LinkedList::Ptr LinkedList::create() {
    return LinkedListImpl::create();
}

}  // namespace libj
