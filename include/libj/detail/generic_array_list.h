// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GENERIC_ARRAY_LIST_H_
#define LIBJ_DETAIL_GENERIC_ARRAY_LIST_H_

#include <vector>

#include "libj/exception.h"
#include "libj/value.h"

namespace libj {

template<typename T>
class GenericArrayList {
 private:
    typedef std::vector<T> Container;
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
        return vec_.size();
    }

    Boolean add(const Value& v) {
        T t;
        return convert(v, &t) && addTyped(t);
    }

    Boolean addTyped(const T& t) {
        vec_.push_back(t);
        return true;
    }

    Boolean add(Size i, const Value& v) {
        T t;
        return convert(v, &t) && addTyped(i, t);
    }

    Boolean addTyped(Size i, const T& t) {
        if (i > vec_.size()) {
            return false;
        } else {
            vec_.insert(vec_.begin() + i, t);
            return true;
        }
    }

    Boolean set(Size i, const Value& v) {
        T t;
        return convert(v, &t) && setTyped(i, t);
    }

    Boolean setTyped(Size i, const T& t) {
        if (i > vec_.size()) {
            return false;
        } else {
            vec_[i] = t;
            return true;
        }
    }

    Value get(Size i) const {
        if (i >= vec_.size()) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            return vec_[i];
        }
    }

    T getTyped(Size i) const {
        if (i >= size()) {
            LIBJ_THROW(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            return vec_[i];
        }
    }

    Value remove(Size i) {
        if (i >= vec_.size()) {
            LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            return removeAux(i);
        }
    }

    T removeTyped(Size i) {
        if (i >= vec_.size()) {
            LIBJ_THROW(Error::INDEX_OUT_OF_BOUNDS);
        } else {
            return removeAux(i);
        }
    }

    Boolean remove(const Value& v) {
        for (Itr i = vec_.begin(), e = vec_.end(); i != e; ++i) {
            if (v.equals(*i)) {
                vec_.erase(i);
                return true;
            }
        }
        return false;
    }

    Boolean removeTyped(const T& t) {
        for (Itr i = vec_.begin(), e = vec_.end(); i != e; ++i) {
            if (*i == t) {
                vec_.erase(i);
                return true;
            }
        }
        return false;
    }

    void clear() {
        vec_.clear();
    }

    GenericArrayList* subList(Size from, Size to) const {
        if (to > size() || from > to) {
            return NULL;
        }

        GenericArrayList* l = new GenericArrayList();
        for (Size i = from; i < to; i++) {
            l->addTyped(vec_[i]);
        }
        return l;
    }

    class Iterator {
        friend class GenericArrayList;

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

        Iterator(const Container& vec)
            : pos_(vec.begin())
            , end_(vec.end()) {}
    };

    Iterator iterator() const {
        return Iterator(vec_);
    }

    GenericArrayList() : vec_() {}

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

}  // namespace libj

#endif  // LIBJ_DETAIL_GENERIC_ARRAY_LIST_H_
