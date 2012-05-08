// Copyright Kevlin Henney, 2000, 2001, 2002. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// modified for libj by Plenluno

#ifndef LIBJ_VALUE_H_
#define LIBJ_VALUE_H_

#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <algorithm>
#include "libj/type.h"

namespace libj {

class Value {
 public:  // structors
    Value()
      : content(0) {
    }

    template<typename ValueType>
    Value(const ValueType & value)
      : content(new holder<ValueType>(value)) {
    }

    Value(const Value & other)
      : content(other.content ? other.content->clone() : 0) {
    }

    ~Value() {
        delete content;
    }

 public:  // modifiers
    Value & swap(Value & rhs) {
        std::swap(content, rhs.content);
        return *this;
    }

    template<typename ValueType>
    Value & operator=(const ValueType & rhs) {
        Value(rhs).swap(*this);
        return *this;
    }

    Value & operator=(Value rhs) {
        rhs.swap(*this);
        return *this;
    }

 public:  // queries
    bool empty() const {
        return !content;
    }

    TypeId type() const {
        return content ? content->type() : Type<void>::id();
    }

    bool instanceOf(TypeId id) const {
        return content ? content->instanceOf(id) : false;
    }

    bool isCptr() const {
        return content ? content->isCptr() : false;
    }

    int compareTo(Value val) const {
        if (content) {
            if (val.content)
                return content->compareTo(val.content);
            else
                return 1;
        } else {
            return val.content ? -1 : 0;
        }
    }

 private:  // types
    class placeholder {
     public:  // structors
        virtual ~placeholder() {
        }

     public:  // queries
        virtual TypeId type() const = 0;

        virtual bool instanceOf(TypeId id) const = 0;

        virtual bool isCptr() const = 0;

        virtual int compareTo(placeholder * other) const = 0;

        virtual placeholder * clone() const = 0;
    };

    template<
        typename ValueType,
        bool IsObject = Classify<ValueType>::isObject,
        bool IsCptr   = Classify<ValueType>::isCptr>
    class holder : public placeholder {
     public:  // structors
        holder(const ValueType & value)
          : held(value) {
        }

     public:  // queries
        virtual TypeId type() const {
            return Type<ValueType>::id();
        }

        virtual bool instanceOf(TypeId id) const {
            return held ? held->instanceOf(id) : false;
        }

        virtual bool isCptr() const {
            return IsCptr;
        }

        virtual int compareTo(placeholder * that) const {
            TypeId thisId = this->type();
            TypeId thatId = that->type();
            if (thisId == thatId) {
                ValueType thatHeld =
                    static_cast<holder<ValueType>*>(that)->held;
                return this->held->compareTo(thatHeld);
            } else if (this->instanceOf(thatId)) {
                return 1;
            } else if (that->instanceOf(thisId)) {
                return -1;
            } else {
                return thisId < thatId ? -1 : 1;
            }
        }

        virtual placeholder * clone() const {
            return new holder(held);
        }

     public:  // representation
        ValueType held;

     private:  // intentionally left unimplemented
        holder & operator=(const holder &);
    };

    template<typename ValueType>
    class holder<ValueType, false, false> : public placeholder {
     public:  // structors
        holder(const ValueType & value)
          : held(value) {
        }

     public:  // queries
        virtual TypeId type() const {
            return Type<ValueType>::id();
        }

        virtual bool instanceOf(TypeId id) const {
            return false;
        }

        virtual bool isCptr() const {
            return true;
        }

        virtual int compareTo(placeholder * that) const {
            TypeId thisId = this->type();
            TypeId thatId = that->type();
            if (thisId == thatId) {
                ValueType thatHeld =
                    static_cast<holder<ValueType>*>(that)->held;
                return this->held < thatHeld
                        ? -1
                        : this->held > thatHeld
                            ? 1
                            : 0;
            } else {
                return thisId < thatId ? -1 : 1;
            }
        }

        virtual placeholder * clone() const {
            return new holder(held);
        }

     public:  // representation
        ValueType held;

     private:  // intentionally left unimplemented
        holder & operator=(const holder &);
    };

 private:  // representation
    template<typename ValueType>
    friend bool to(Value * operand, ValueType** out, bool instanceof = false);

    placeholder * content;
};

template<typename T>
class remove_const {
 public:
    typedef typename boost::remove_const<T>::type type;
};

template<typename T>
class remove_reference {
 public:
    typedef typename boost::remove_reference<T>::type type;
};

template<typename T>
class remove_reference_and_const {
 private:
    typedef typename boost::remove_reference<T>::type nonref;

 public:
    typedef typename boost::remove_const<nonref>::type type;
};

template<typename ValueType>
bool to(Value* operand, ValueType** out, bool instanceof) {
    if (operand && (operand->type() == Type<ValueType>::id() || instanceof)) {
        Value::holder<ValueType>* content =
            static_cast<Value::holder<ValueType>*>(operand->content);
        *out = &content->held;
        return true;
    } else {
        return false;
    }
}

template<typename ValueType>
inline bool to(
    const Value* operand,
    const ValueType** out,
    bool instanceof = false) {
    typedef typename remove_const<ValueType>::type NonConst;
    return to<NonConst>(
        const_cast<Value*>(operand),
        const_cast<ValueType**>(out),
        instanceof);
}

template<typename ValueType>
bool to(
    const Value & operand,
    typename remove_reference_and_const<ValueType>::type* out,
    bool instanceof = false) {
    typedef typename remove_reference_and_const<ValueType>::type NonRefConst;
    NonRefConst* result;
    if (to<NonRefConst>(&const_cast<Value&>(operand), &result, instanceof)) {
        NonRefConst* o = const_cast<NonRefConst*>(out);
        *o = *result;
        return true;
    } else {
        return false;
    }
}

template<typename T>
typename Type<T>::Ptr toPtr(const Value& v) {
    if (v.instanceOf(Type<T>::id()) && !v.isCptr()) {
        LIBJ_PTR_TYPE(T) p;
        if (to<typename Type<T>::Ptr>(v, &p, true)) {
            return p;
        } else {
            LIBJ_NULL_PTR_TYPE(T, nullp);
            return nullp;
        }
    } else {
        LIBJ_NULL_PTR_TYPE(T, nullp);
        return nullp;
    }
}

template<typename T>
typename Type<T>::Cptr toCptr(const Value& v) {
    if (v.instanceOf(Type<T>::id())) {
        LIBJ_CPTR_TYPE(T) p;
        if (to<typename Type<T>::Cptr>(v, &p, true)) {
            return p;
        } else {
            LIBJ_NULL_CPTR_TYPE(T, nullp);
        }
    } else {
        LIBJ_NULL_CPTR_TYPE(T, nullp);
        return nullp;
    }
}

}  // namespace libj

#endif  // LIBJ_VALUE_H_
