// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GENERIC_ARRAY_LIST_H_
#define LIBJ_DETAIL_GENERIC_ARRAY_LIST_H_

#include <libj/detail/generic_list.h>

#include <vector>

namespace libj {
namespace detail {

template<typename I, typename T>
class GenericArrayList : public GenericList<I, T> {
 private:
    typedef std::vector<T> Container;
    typedef typename Container::iterator Itr;
    typedef typename Container::const_iterator CItr;
    typedef typename Container::reverse_iterator RItr;
    typedef typename Container::const_reverse_iterator CRItr;

 public:
    virtual Size size() const {
        return vec_.size();
    }

    virtual Boolean add(const Value& v) {
        T t;
        return convert(v, &t) && addTyped(t);
    }

    virtual Boolean addTyped(const T& t) {
        vec_.push_back(t);
        return true;
    }

    virtual Boolean add(Size i, const Value& v) {
        T t;
        return convert(v, &t) && addTyped(i, t);
    }

    virtual Boolean addTyped(Size i, const T& t) {
        if (i > vec_.size()) {
            return false;
        } else {
            vec_.insert(vec_.begin() + i, t);
            return true;
        }
    }

    virtual Boolean set(Size i, const Value& v) {
        T t;
        return convert<T>(v, &t) && setTyped(i, t);
    }

    virtual Boolean setTyped(Size i, const T& t) {
        if (i > vec_.size()) {
            return false;
        } else {
            vec_[i] = t;
            return true;
        }
    }

    virtual Value get(Size i) const {
        if (i >= vec_.size()) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            return vec_[i];
        }
    }

    virtual T getTyped(Size i) const {
        if (i >= size()) {
            LIBJ_THROW(Error::INDEX_OUT_OF_BOUNDS);
        }
        return vec_[i];
    }

    virtual Value remove(Size i) {
        if (i >= vec_.size()) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            return removeAux(i);
        }
    }

    virtual T removeTyped(Size i) {
        if (i >= vec_.size()) {
            LIBJ_THROW(Error::INDEX_OUT_OF_BOUNDS);
        }
        return removeAux(i);
    }

    virtual Boolean remove(const Value& v) {
        for (Itr i = vec_.begin(), e = vec_.end(); i != e; ++i) {
            if (v.equals(*i)) {
                vec_.erase(i);
                return true;
            }
        }
        return false;
    }

    virtual Boolean removeTyped(const T& t) {
        for (Itr i = vec_.begin(), e = vec_.end(); i != e; ++i) {
            if (*i == t) {
                vec_.erase(i);
                return true;
            }
        }
        return false;
    }

    virtual void clear() {
        vec_.clear();
    }

    virtual Value subList(Size from, Size to) const {
        if (to > size() || from > to) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        }

        GenericArrayList* l = new GenericArrayList();
        for (Size i = from; i < to; i++) {
            l->addTyped(vec_[i]);
        }
        return typename GenericList<I, T>::Ptr(l);
    }

    virtual Iterator::Ptr iterator() const {
        return Iterator::Ptr(new TypedObverseIterator(vec_));
    }

    virtual Iterator::Ptr reverseIterator() const {
        return Iterator::Ptr(new TypedReverseIterator(vec_));
    }

    virtual typename TypedIterator<T>::Ptr iteratorTyped() const {
        return typename TypedIterator<T>::Ptr(new TypedObverseIterator(vec_));
    }

    virtual typename TypedIterator<T>::Ptr reverseIteratorTyped() const {
        return typename TypedIterator<T>::Ptr(new TypedReverseIterator(vec_));
    }

 public:
    virtual Boolean hasProperty(const Value& name) const {
        return false;
    }

    virtual Value getProperty(const Value& name) const {
        return UNDEFINED;
    }

    virtual Value setProperty(const Value& name, const Value& val) {
        return UNDEFINED;
    }

    virtual Value deleteProperty(const Value& name) {
        return UNDEFINED;
    }

 private:
    class TypedObverseIterator : public TypedIterator<T> {
        friend class GenericArrayList;

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

        TypedObverseIterator(const Container& list)
            : pos_(list.begin())
            , end_(list.end()) {}
    };

    class TypedReverseIterator : public TypedIterator<T> {
        friend class GenericArrayList;

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
        CRItr pos_;
        CRItr end_;

        TypedReverseIterator(const Container& list)
            : pos_(list.rbegin())
            , end_(list.rend()) {}
    };

 private:
    Container vec_;

    T removeAux(Size i) {
        // destruct the shared object!
        // return *vec_.erase(vec_.begin() + i);
        T t = vec_[i];
        vec_.erase(vec_.begin() + i);
        return t;
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_GENERIC_ARRAY_LIST_H_
