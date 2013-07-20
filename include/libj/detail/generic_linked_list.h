// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GENERIC_LINKED_LIST_H_
#define LIBJ_DETAIL_GENERIC_LINKED_LIST_H_

#include <libj/detail/generic_list.h>

#include <list>

namespace libj {
namespace detail {

template<typename I, typename T>
class GenericLinkedList : public GenericList<I, T> {
 private:
    typedef std::list<T> Container;
    typedef typename Container::iterator Itr;
    typedef typename Container::const_iterator CItr;
    typedef typename Container::reverse_iterator RItr;
    typedef typename Container::const_reverse_iterator CRItr;

 public:
    virtual Size size() const {
        return list_.size();
    }

    virtual Boolean add(const Value& v) {
        T t;
        return convert(v, &t) && addTyped(t);
    }

    virtual Boolean addTyped(const T& t) {
        list_.push_back(t);
        return true;
    }

    virtual Boolean add(Size i, const Value& v) {
        T t;
        return convert(v, &t) && addTyped(i, t);
    }

    virtual Boolean addTyped(Size i, const T& t) {
        if (i > list_.size()) {
            return false;
        } else {
            Itr pos = list_.begin();
            for (; i; i--) ++pos;
            list_.insert(pos, t);
            return true;
        }
    }

    virtual Boolean offer(const Value& v) {
        T t;
        return convert(v, &t, false) && addTyped(t);
    }

    virtual Boolean set(Size i, const Value& v) {
        T t;
        return convert(v, &t) && setTyped(i, t);
    }

    virtual Boolean setTyped(Size i, const T& t) {
        if (i > list_.size()) {
            return false;
        } else {
            Itr pos = list_.begin();
            for (; i; i--) ++pos;
            *pos = t;
            return true;
        }
    }

    virtual Value get(Size i) const {
        if (i >= list_.size()) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            return getAux(i);
        }
    }

    virtual T getTyped(Size i) const {
        if (i >= size()) {
            LIBJ_THROW(Error::INDEX_OUT_OF_BOUNDS);
        }
        return getAux(i);
    }

    virtual Value element() const {
        if (!list_.size()) {
            LIBJ_HANDLE_ERROR(Error::NO_SUCH_ELEMENT);
        } else {
            return getAux(0);
        }
    }

    virtual Value peek() const {
        if (!list_.size()) {
            return UNDEFINED;
        } else {
            return getAux(0);
        }
    }

    virtual Value poll() {
        if (!list_.size()) {
            return UNDEFINED;
        } else {
            return removeAux(0);
        }
    }

    virtual void put(const Value& v) {
        offer(v);
    }

    virtual Value remove() {
        if (!list_.size()) {
            LIBJ_HANDLE_ERROR(Error::NO_SUCH_ELEMENT);
        } else {
            return removeAux(0);
        }
    }

    virtual Value remove(Size i) {
        if (i >= list_.size()) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            return removeAux(i);
        }
    }

    virtual T removeTyped(Size i) {
        if (i >= list_.size()) {
            LIBJ_THROW(Error::INDEX_OUT_OF_BOUNDS);
        }
        return removeAux(i);
    }

    virtual Boolean remove(const Value& v) {
        for (Itr i = list_.begin(), e = list_.end(); i != e; ++i) {
            if (v.equals(*i)) {
                list_.erase(i);
                return true;
            }
        }
        return false;
    }

    virtual Boolean removeTyped(const T& t) {
        for (Itr i = list_.begin(), e = list_.end(); i != e; ++i) {
            if (*i == t) {
                list_.erase(i);
                return true;
            }
        }
        return false;
    }

    virtual Value take() {
        return poll();
    }

    virtual void clear() {
        list_.clear();
    }

    virtual Value subList(Size from, Size to) const {
        if (to > size() || from > to) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
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
        return typename GenericList<I, T>::Ptr(l);
    }

    virtual Iterator::Ptr iterator() const {
        return Iterator::Ptr(new ObverseIterator(list_));
    }

    virtual Iterator::Ptr reverseIterator() const {
        return Iterator::Ptr(new ReverseIterator(list_));
    }

    virtual typename TypedIterator<T>::Ptr iteratorTyped() const {
        return typename TypedIterator<T>::Ptr(new TypedObverseIterator(list_));
    }

    virtual typename TypedIterator<T>::Ptr reverseIteratorTyped() const {
        return typename TypedIterator<T>::Ptr(new TypedReverseIterator(list_));
    }

 private:
    class ObverseIterator : public Iterator {
        friend class GenericLinkedList;

     public:
        virtual Boolean hasNext() const {
            return pos_ != end_;
        }

        virtual Value next() {
            if (pos_ == end_) {
                LIBJ_HANDLE_ERROR(Error::NO_SUCH_ELEMENT);
            } else {
                T t = *pos_;
                ++pos_;
                return t;
            }
        }

        virtual String::CPtr toString() const {
            return String::create();
        }

     private:
        CItr pos_;
        CItr end_;

        ObverseIterator(const Container& list)
            : pos_(list.begin())
            , end_(list.end()) {}
    };

    class ReverseIterator : public Iterator {
        friend class GenericLinkedList;

     public:
        virtual Boolean hasNext() const {
            return pos_ != end_;
        }

        virtual Value next() {
            if (pos_ == end_) {
                LIBJ_HANDLE_ERROR(Error::NO_SUCH_ELEMENT);
            }

            T t = *pos_;
            ++pos_;
            return t;
        }

        virtual String::CPtr toString() const {
            return String::create();
        }

     private:
        CRItr pos_;
        CRItr end_;

        ReverseIterator(const Container& list)
            : pos_(list.rbegin())
            , end_(list.rend()) {}
    };

    class TypedObverseIterator : public TypedIterator<T> {
        friend class GenericLinkedList;

     public:
        virtual Boolean hasNext() const {
            return pos_ != end_;
        }

        virtual T next() {
            if (pos_ == end_) {
                LIBJ_THROW(Error::NO_SUCH_ELEMENT);
            }

            T t = *pos_;
            ++pos_;
            return t;
        }

        virtual String::CPtr toString() const {
            return String::create();
        }

     private:
        CItr pos_;
        CItr end_;

        TypedObverseIterator(const Container& list)
            : pos_(list.begin())
            , end_(list.end()) {}
    };

    class TypedReverseIterator : public TypedIterator<T> {
        friend class GenericLinkedList;

     public:
        virtual Boolean hasNext() const {
            return pos_ != end_;
        }

        virtual T next() {
            if (pos_ == end_) {
                LIBJ_THROW(Error::NO_SUCH_ELEMENT);
            }

            T t = *pos_;
            ++pos_;
            return t;
        }

        virtual String::CPtr toString() const {
            return String::create();
        }

     private:
        CRItr pos_;
        CRItr end_;

        TypedReverseIterator(const Container& list)
            : pos_(list.rbegin())
            , end_(list.rend()) {}
    };

 private:
    Container list_;

    T getAux(Size i) const {
        Size len = size();
        if (i <= (len >> 1)) {
            CItr pos = list_.begin();
            for (; i; i--) ++pos;
            return *pos;
        } else {
            CRItr rpos = list_.rbegin();
            i = len - i - 1;
            for (; i; i--) ++rpos;
            return *rpos;
        }
    }

    T removeAux(Size i) {
        Itr pos;
        Size len = size();
        if (i <= (size() >> 1)) {
            pos = list_.begin();
            for (; i; i--) ++pos;
        } else {
            RItr rpos = list_.rbegin();
            i = len - i - 1;
            for (; i; i--) ++rpos;
            pos = (++rpos).base();
        }
        T t = *pos;
        list_.erase(pos);
        return t;
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_GENERIC_LINKED_LIST_H_
