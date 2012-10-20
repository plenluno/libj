// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GENERIC_LINKED_LIST_H_
#define LIBJ_DETAIL_GENERIC_LINKED_LIST_H_

#include <list>

#include "libj/exception.h"
#include "libj/value.h"

namespace libj {

template<typename T>
class GenericLinkedList {
 private:
    typedef std::list<T> Container;
    typedef typename Container::iterator Itr;
    typedef typename Container::const_iterator CItr;

 public:
    static Boolean convert(const Value& v, T* t) {
        Boolean result = to<T>(v, t);
#ifdef LIBJ_USE_EXCEPTION
        if (!result)
            LIBJ_THROW(Error::ILLEGAL_TYPE);
#endif  // LIBJ_USE_EXCEPTION
        return result;
    }

    Size size() const {
        return list_.size();
    }

    Boolean add(const Value& v) {
        T t;
        return convert(v, &t) && addTyped(t);
    }

    Boolean addTyped(const T& t) {
        list_.push_back(t);
        return true;
    }

    Boolean add(Size i, const Value& v) {
        T t;
        return convert(v, &t) && addTyped(i, t);
    }

    Boolean addTyped(Size i, const T& t) {
        if (i > list_.size()) {
            return false;
        } else {
            Itr pos = list_.begin();
            for (; i; i--) ++pos;
            list_.insert(pos, t);
            return true;
        }
    }

    Boolean set(Size i, const Value& v) {
        T t;
        return convert(v, &t) && setTyped(i, t);
    }

    Boolean setTyped(Size i, const T& t) {
        if (i > list_.size()) {
            return false;
        } else {
            Itr pos = list_.begin();
            for (; i; i--) ++pos;
            *pos = t;
            return true;
        }
    }

    Value get(Size i) const {
        if (i >= list_.size()) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            return getAux(i);
        }
    }

    T getTyped(Size i) const {
        if (i >= size()) {
            LIBJ_THROW(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            return getAux(i);
        }
    }

    Value remove(Size i) {
        if (i >= list_.size()) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            return removeAux(i);
        }
    }

    T removeTyped(Size i) {
        if (i >= list_.size()) {
            LIBJ_THROW(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            return removeAux(i);
        }
    }

    Boolean remove(const Value& v) {
        for (Itr i = list_.begin(), e = list_.end(); i != e; ++i) {
            if (v.equals(*i)) {
                list_.erase(i);
                return true;
            }
        }
        return false;
    }

    Boolean removeTyped(const T& t) {
        for (Itr i = list_.begin(), e = list_.end(); i != e; ++i) {
            if (*i == t) {
                list_.erase(i);
                return true;
            }
        }
        return false;
    }

    void clear() {
        list_.clear();
    }

    GenericLinkedList* subList(Size from, Size to) const {
        if (to > size() || from > to) {
            return NULL;
        }

        GenericLinkedList* l = new GenericLinkedList();
        Size i = 0;
        for (CItr pos = list_.begin();
             pos != list_.end() && i < to;
             pos++, i++) {
            if (i >= from) {
                l->addTyped(*pos);
            }
        }
        return l;
    }

    class Iterator {
        friend class GenericLinkedList;

     public:
        Boolean hasNext() const {
            return pos_ != end_;
        }

        Value next() {
            if (pos_ == end_) {
                LIBJ_HANDLE_ERROR(Error::NO_SUCH_ELEMENT);
            } else {
                T t = *pos_;
                ++pos_;
                return t;
            }
        }

        T nextTyped() {
            if (pos_ == end_) {
                LIBJ_THROW(Error::NO_SUCH_ELEMENT);
            } else {
                T t = *pos_;
                ++pos_;
                return t;
            }
        }

     private:
        CItr pos_;
        CItr end_;

        Iterator(const Container& list)
            : pos_(list.begin())
            , end_(list.end()) {}
    };

    Iterator iterator() const {
        return Iterator(list_);
    }

    GenericLinkedList() : list_() {}

 private:
    Container list_;

    T getAux(Size i) const {
        CItr pos = list_.begin();
        for (; i; i--) ++pos;
        return *pos;
    }

    T removeAux(Size i) {
        Itr pos = list_.begin();
        for (; i; i--) ++pos;
        T t = *pos;
        list_.erase(pos);
        return t;
    }
};

}  // namespace libj

#endif  // LIBJ_DETAIL_GENERIC_LINKED_LIST_H_
