// Copyright (c) 2012 Plenluno All rights reserved.

#include <list>
//#include <forward_list>   // since c++11
#include "libj/linked_list.h"
#include "libj/error.h"
#include "libj/exception.h"
#include "libj/string_buffer.h"

namespace libj {

class LinkedListImpl : public LinkedList {
    typedef std::list<Value> container;
//  typedef std::forward_list<Value> container;
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
#ifdef LIBJ_USE_EXCEPTION
            LIBJ_THROW(Error::INDEX_OUT_OF_BOUNDS);
#else
            return Error::create(Error::INDEX_OUT_OF_BOUNDS);
#endif  // LIBJ_USE_EXCEPTION
        } else {
            cit pos = list_.begin();
            for (; i; i--) ++pos;
            return *pos;
        }
    }

    Value remove(Size i) {
        if (i >= list_.size()) {
#ifdef LIBJ_USE_EXCEPTION
            LIBJ_THROW(Error::INDEX_OUT_OF_BOUNDS);
#else
            return Error::create(Error::INDEX_OUT_OF_BOUNDS);
#endif  // LIBJ_USE_EXCEPTION
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

    LinkedList::Ptr clone() const {
        LinkedListImpl* ls = new LinkedListImpl();
        LinkedList::Ptr p (ls);
        for (cit i = list_.begin(), e = list_.end(); i != e; ++i) {
            ls->add(*i);
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
#ifdef LIBJ_USE_EXCEPTION
                LIBJ_THROW(Error::NO_SUCH_ELEMENT);
#else
                return Error::create(Error::NO_SUCH_ELEMENT);
#endif  // LIBJ_USE_EXCEPTION
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
}; // LinkedListImpl

LinkedList::Ptr LinkedList::create() {
    return LinkedListImpl::create();
}

}  // namespace libj
