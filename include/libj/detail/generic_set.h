// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GENERIC_SET_H_
#define LIBJ_DETAIL_GENERIC_SET_H_

#include <libj/detail/generic_collection.h>

#include <set>

namespace libj {
namespace detail {

template<typename I, typename T>
class GenericSet : public GenericCollection<I, T> {
 private:
    typedef std::set<T> Container;
    typedef typename Container::iterator Itr;
    typedef typename Container::const_iterator CItr;

 public:
    virtual Size size() const {
        return set_.size();
    }

    virtual Boolean add(const Value& v) {
        T t;
        return convert(v, &t) && addTyped(t);
    }

    virtual Boolean addTyped(const T& t) {
        std::pair<Itr, Boolean> p = set_.insert(t);
        return p.second;
    }

    virtual Boolean remove(const Value& v) {
        T t;
        return convert(v, &t) && removeTyped(t);
    }

    virtual Boolean removeTyped(const T& t) {
        return set_.erase(t) > 0;
    }

    virtual void clear() {
        set_.clear();
    }

    virtual Iterator::Ptr iterator() const {
        return Iterator::Ptr(new SetIterator(set_));
    }

    virtual typename TypedIterator<T>::Ptr iteratorTyped() const {
        return typename TypedIterator<T>::Ptr(new TypedSetIterator(set_));
    }

 private:
    class SetIterator : public Iterator {
        friend class GenericSet;

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

        SetIterator(const Container& set)
            : pos_(set.begin())
            , end_(set.end()) {}
    };

    class TypedSetIterator : public TypedIterator<T> {
        friend class GenericSet;

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

        virtual T nextTyped() {
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

        TypedSetIterator(const Container& set)
            : pos_(set.begin())
            , end_(set.end()) {}
    };

 private:
    Container set_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_GENERIC_SET_H_
