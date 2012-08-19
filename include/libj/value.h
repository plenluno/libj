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
 public:
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

 public:
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

 public:
    Boolean isEmpty() const {
        return !content;
    }

    TypeId type() const {
        return content ? content->type() : Type<void>::id();
    }

    Boolean instanceof(TypeId id) const {
        return content ? content->instanceof(id) : false;
    }

    Boolean isPtr() const {
        return content ? content->isPtr() : false;
    }

    Boolean isCPtr() const {
        return content ? content->isCPtr() : false;
    }

    Int compareTo(const Value& val) const {
        if (content) {
            if (val.content) {
                return content->compareTo(val.content);
            } else {
                return TYPE_CMP_NA;
            }
        } else {
            if (val.content) {
                return -TYPE_CMP_NA;
            } else {
                return 0;
            }
        }
    }

    Boolean equals(Value val) const {
        return !compareTo(val);
    }

 private:
    class placeholder {
     public:
        virtual ~placeholder() {
        }

     public:
        virtual TypeId type() const = 0;

        virtual TypeId objectType() const = 0;

        virtual Boolean instanceof(TypeId id) const = 0;

        virtual Boolean isPtr() const = 0;

        virtual Boolean isCPtr() const = 0;

        virtual Int compareTo(placeholder * other) const = 0;

        virtual placeholder * clone() const = 0;
    };

    template<
        typename ValueType,
        Boolean IsObject = Classify<ValueType>::isObject,
        Boolean IsCPtr   = Classify<ValueType>::isCPtr>
    class holder : public placeholder {
     public:
        holder(const ValueType & value)
          : held(value) {
        }

     public:
        virtual TypeId type() const {
            return Type<ValueType>::id();
        }

        virtual TypeId objectType() const {
            return held ? held->type() : 0;
        }

        virtual Boolean instanceof(TypeId id) const {
            return held ? held->instanceof(id) : false;
        }

        virtual Boolean isPtr() const {
            return !IsCPtr;
        }

        virtual Boolean isCPtr() const {
            return IsCPtr;
        }

        virtual Int compareTo(placeholder * that) const {
            TypeId thisId = this->objectType();
            TypeId thatId = that->objectType();
            if (thisId == thatId) {
                ValueType thatHeld =
                    static_cast<holder<ValueType>*>(that)->held;
                return this->held->compareTo(thatHeld);
            } else if (this->instanceof(thatId)) {
                return TYPE_CMP_DERIVED;
            } else if (that->instanceof(thisId)) {
                return -TYPE_CMP_DERIVED;
            } else {
                thisId = this->type();
                thatId = that->type();
                return thisId < thatId
                        ? -TYPE_CMP_NOT_DERIVED
                        : TYPE_CMP_NOT_DERIVED;
            }
        }

        virtual placeholder * clone() const {
            return new holder(held);
        }

     public:
        ValueType held;

     private:
        holder & operator=(const holder &);
    };

    template<typename ValueType>
    class holder<ValueType, false, false> : public placeholder {
     public:
        holder(const ValueType & value)
          : held(value) {
        }

     public:
        virtual TypeId type() const {
            return Type<ValueType>::id();
        }

        virtual TypeId objectType() const {
            return 0;
        }

        virtual Boolean instanceof(TypeId id) const {
            return false;
        }

        virtual Boolean isPtr() const {
            return false;
        }

        virtual Boolean isCPtr() const {
            return false;
        }

        virtual Int compareTo(placeholder * that) const {
            TypeId thisId = this->type();
            TypeId thatId = that->type();
            if (thisId == thatId) {
                ValueType thatHeld =
                    static_cast<holder<ValueType>*>(that)->held;
                if (this->held < thatHeld) {
                    return -TYPE_CMP_SAME;
                } else if (this->held > thatHeld) {
                    return TYPE_CMP_SAME;
                } else {
                    return 0;
                }
            } else {
                return thisId < thatId
                    ? -TYPE_CMP_NOT_DERIVED
                    : TYPE_CMP_NOT_DERIVED;
            }
        }

        virtual placeholder * clone() const {
            return new holder(held);
        }

     public:
        ValueType held;

     private:
        holder & operator=(const holder &);
    };

 private:
    template<typename ValueType>
    friend Boolean to(
        Value * operand,
        ValueType** out,
        Boolean instanceof = false);

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
Boolean to(Value* operand, ValueType** out, Boolean instanceof) {
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
inline Boolean to(
    const Value* operand,
    const ValueType** out,
    Boolean instanceof = false) {
    typedef typename remove_const<ValueType>::type NonConst;
    return to<NonConst>(
        const_cast<Value*>(operand),
        const_cast<ValueType**>(out),
        instanceof);
}

template<typename ValueType>
Boolean to(
    const Value & operand,
    typename remove_reference_and_const<ValueType>::type* out,
    Boolean instanceof = false) {
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
    LIBJ_PTR_TYPE(T) p;
    if (v.instanceof(Type<T>::id()) &&
        !v.isCPtr() &&
        to<typename Type<T>::Ptr>(v, &p, true)) {
        return p;
    } else {
        LIBJ_NULL_PTR_TYPE_DEF(T, nullp);
        return nullp;
    }
}

template<typename T>
typename Type<T>::CPtr toCPtr(const Value& v) {
    LIBJ_CPTR_TYPE(T) p;
    if (v.instanceof(Type<T>::id()) &&
        to<typename Type<T>::CPtr>(v, &p, true)) {
        return p;
    } else {
        LIBJ_NULL_CPTR_TYPE_DEF(T, nullp);
        return nullp;
    }
}

}  // namespace libj

#endif  // LIBJ_VALUE_H_
