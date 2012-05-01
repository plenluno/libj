// Copyright Kevlin Henney, 2000, 2001, 2002. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

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

 private:  // types
    class placeholder {
     public:  // structors
        virtual ~placeholder() {
        }

     public:  // queries
        virtual TypeId type() const = 0;

        virtual placeholder * clone() const = 0;
    };

    template<typename ValueType>
    class holder : public placeholder {
     public:  // structors
        holder(const ValueType & value)
          : held(value) {
        }

     public:  // queries
        virtual TypeId type() const {
            return Type<ValueType>::id();
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
    friend bool to(Value * operand, ValueType** out);

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
bool to(Value* operand, ValueType** out) {
    if (operand && operand->type() == Type<ValueType>::id()) {
        Value::holder<ValueType>* content =
            static_cast<Value::holder<ValueType>*>(operand->content);
        *out = &content->held;
        return true;
    } else {
        return false;
    }
}

template<typename ValueType>
inline bool to(const Value* operand, const ValueType** out) {
    typedef typename remove_const<ValueType>::type NonConst;
    return to<NonConst>(
        const_cast<Value*>(operand),
        const_cast<ValueType**>(out));
}

template<typename ValueType>
bool to(
    const Value & operand,
    typename remove_reference_and_const<ValueType>::type* out) {
    typedef typename remove_reference_and_const<ValueType>::type NonRefConst;
    NonRefConst* result;
    if (to<NonRefConst>(&const_cast<Value&>(operand), &result)) {
        NonRefConst* o = const_cast<NonRefConst*>(out);
        *o = *result;
        return true;
    } else {
        return false;
    }
}

}  // namespace libj

#endif  // LIBJ_VALUE_H_
