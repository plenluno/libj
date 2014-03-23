// Copyright Kevlin Henney, 2000, 2001, 2002. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Copyright (c) 2012-2013 Plenluno All rights reserved.
// modified boost::any for libj

#ifndef LIBJ_DETAIL_VALUE_H_
#define LIBJ_DETAIL_VALUE_H_

#include <libj/detail/classify.h>

#ifdef LIBJ_USE_CXX11
# include <type_traits>
#else
# include <boost/functional/hash.hpp>
# include <boost/type_traits/remove_const.hpp>
# include <boost/type_traits/remove_reference.hpp>
#endif

namespace libj {
namespace detail {

class Value {
 public:
    Value() : content(0) {}

    template<typename T>
    Value(const T& value)
        : content(new holder<T>(value)) {}

    Value(const Value& other)
        : content(other.content ? other.content->clone() : 0) {}

    ~Value() {
        delete content;
    }

 public:
    Value& swap(Value& rhs) {
        std::swap(content, rhs.content);
        return *this;
    }

    template<typename T>
    Value& operator=(const T& rhs) {
        Value(rhs).swap(*this);
        return *this;
    }

    Value& operator=(Value rhs) {
        rhs.swap(*this);
        return *this;
    }

 public:
    TypeId type() const {
        return content ? content->type() : 0;
    }

    Boolean instanceof(TypeId id) const {
        return content ? content->instanceof(id) : false;
    }

    Boolean isUndefined() const {
        return !content;
    }

    Boolean isNull() const {
        return content ? content->isNull() : false;
    }

    Boolean isPrimitive() const {
        return content ? content->isPrimitive() : false;
    }

    Boolean isObject() const {
        return content ? content->isObject() : false;
    }

    Boolean isPtr() const {
        return content ? content->isPtr() : false;
    }

    Boolean isCPtr() const {
        return content ? content->isCPtr() : false;
    }

    template<typename T>
    Boolean is() const {
        if (isNull()) {
            return false;
        } else if (isObject()) {
            return instanceof(Type<T>::id());
        } else {
            return type() == Type<T>::id();
        }
    }

    Size hashCode() const {
        return content ? content->hashCode() : -1;
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

    Boolean equals(const Value& val) const {
        return !compareTo(val);
    }

    Boolean operator==(const Value& val) const {
        return equals(val);
    }

    Boolean operator!=(const Value& val) const {
        return !equals(val);
    }

    Boolean operator<(const Value& val) const {
        return compareTo(val) < 0;
    }

    Boolean operator<=(const Value& val) const {
        return compareTo(val) <= 0;
    }

    Boolean operator>(const Value& val) const {
        return compareTo(val) > 0;
    }

    Boolean operator>=(const Value& val) const {
        return compareTo(val) >= 0;
    }

 private:
    class placeholder {
     public:
        virtual ~placeholder() {}

     public:
        virtual TypeId type() const = 0;

        virtual TypeId objectType() const = 0;

        virtual Boolean instanceof(TypeId id) const = 0;

        virtual Boolean isNull() const = 0;

        virtual Boolean isPrimitive() const = 0;

        virtual Boolean isObject() const = 0;

        virtual Boolean isPtr() const = 0;

        virtual Boolean isCPtr() const = 0;

        virtual Size hashCode() const = 0;

        virtual Int compareTo(placeholder* other) const = 0;

        virtual placeholder* clone() const = 0;
    };

    template<
        typename T,
        Boolean IsObject = Classify<T>::isObject,
        Boolean IsCPtr   = Classify<T>::isCPtr>
    class holder : public placeholder {
     public:
        holder(const T& value) : held(value) {}

     public:
        virtual TypeId type() const {
            return held ? Type<T>::id() : 1;
        }

        virtual TypeId objectType() const {
            return held ? held->type() : 1;
        }

        virtual Boolean instanceof(TypeId id) const {
            return held ? held->instanceof(id) : false;
        }

        virtual Boolean isNull() const {
            return !held;
        }

        virtual Boolean isPrimitive() const {
            return false;
        }

        virtual Boolean isObject() const {
            return !!held;
        }

        virtual Boolean isPtr() const {
            return held ? !IsCPtr : true;
        }

        virtual Boolean isCPtr() const {
            return held ? IsCPtr : true;
        }

        virtual Size hashCode() const {
            return held ? held->hashCode() : 0;
        }

        virtual Int compareTo(placeholder* that) const {
            if (that->isPtr() || that->isCPtr()) {
                TypeId thisId = this->objectType();
                TypeId thatId = that->objectType();
                if (thisId == thatId) {
                    T thatHeld = static_cast<holder<T>*>(that)->held;
                    return this->held
                            ? this->held->compareTo(thatHeld)
                            : 0;
                } else if (this->instanceof(thatId)) {
                    return TYPE_CMP_DERIVED;
                } else if (that->instanceof(thisId)) {
                    return -TYPE_CMP_DERIVED;
                } else {
                    return thisId < thatId
                        ? -TYPE_CMP_NOT_DERIVED
                        : TYPE_CMP_NOT_DERIVED;
                }
            } else {
                TypeId thisId = this->type();
                TypeId thatId = that->type();
                return thisId < thatId
                        ? -TYPE_CMP_NOT_DERIVED
                        : TYPE_CMP_NOT_DERIVED;
            }
        }

        virtual placeholder* clone() const {
            return new holder(held);
        }

     public:
        T held;

     private:
        holder& operator=(const holder&);
    };

    template<typename T>
    class holder<T, false, false> : public placeholder {
     public:
        holder(const T& value) : held(value) {}

     public:
        virtual TypeId type() const {
            return Type<T>::id();
        }

        virtual TypeId objectType() const {
            return 0;
        }

        virtual Boolean instanceof(TypeId id) const {
            return false;
        }

        virtual Boolean isNull() const {
            return false;
        }

        virtual Boolean isPrimitive() const {
            return true;
        }

        virtual Boolean isObject() const {
            return false;
        }

        virtual Boolean isPtr() const {
            return false;
        }

        virtual Boolean isCPtr() const {
            return false;
        }

        virtual Size hashCode() const {
#ifdef LIBJ_USE_CXX11
            static std::hash<T> hashFunc;
#else
            static boost::hash<T> hashFunc;
#endif
            return hashFunc(held);
        }

        virtual Int compareTo(placeholder* that) const {
            TypeId thisId = this->type();
            TypeId thatId = that->type();
            if (thisId == thatId) {
                T thatHeld = static_cast<holder<T>*>(that)->held;
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

        virtual placeholder* clone() const {
            return new holder(held);
        }

     public:
        T held;

     private:
        holder& operator=(const holder&);
    };

 private:
    template<typename T>
    friend Boolean _to(Value* operand, T** out, Boolean instanceof);

    placeholder* content;
};

#ifdef LIBJ_USE_CXX11

template<typename T>
class remove_const {
 public:
    typedef typename std::remove_const<T>::type type;
};

template<typename T>
class remove_reference {
 public:
    typedef typename std::remove_reference<T>::type type;
};

template<typename T>
class remove_reference_and_const {
 private:
    typedef typename std::remove_reference<T>::type nonref;

 public:
    typedef typename std::remove_const<nonref>::type type;
};

#else  // LIBJ_USE_CXX11

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

#endif  // LIBJ_USE_CXX11

template<typename T>
inline Boolean _to(Value* operand, T** out, Boolean instanceof) {
    if (operand &&
        (operand->type() == Type<T>::id() ||
         (operand->isNull() && Classify<T>::isObject) ||
         instanceof)) {
        Value::holder<T>* content =
            static_cast<Value::holder<T>*>(operand->content);
        *out = &content->held;
        return true;
    } else {
        return false;
    }
}

template<typename T>
inline Boolean _to(
    const Value* operand,
    const T** out,
    Boolean instanceof = false) {
    typedef typename remove_const<T>::type NonConst;
    return _to<NonConst>(
        const_cast<Value*>(operand),
        const_cast<T**>(out),
        instanceof);
}

template<typename T>
inline T _to(const Value& operand, T dflt) {
    typedef typename remove_reference_and_const<T>::type NonRefConst;
    NonRefConst* result;
    if (_to<NonRefConst>(&const_cast<Value&>(operand), &result, false)) {
        return *result;
    } else {
        return dflt;
    }
}

template<typename T>
inline Boolean _to(
    const Value& operand,
    typename remove_reference_and_const<T>::type* out,
    Boolean instanceof = false) {
    if (!out) return false;
    typedef typename remove_reference_and_const<T>::type NonRefConst;
    NonRefConst* result;
    if (_to<NonRefConst>(&const_cast<Value&>(operand), &result, instanceof)) {
        *out = *result;
        return true;
    } else {
        return false;
    }
}

}  // namespace detail
}  // namespace libj

#ifdef LIBJ_USE_CXX11
namespace std {
#else
namespace boost {
#endif
    template <>
    struct hash<libj::detail::Value> {
        std::size_t operator()(const libj::detail::Value& key) const {
            return key.hashCode();
        }
    };
}

#endif  // LIBJ_DETAIL_VALUE_H_
