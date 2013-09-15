// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_MAP_H_
#define LIBJ_DETAIL_MAP_H_

#include <libj/typed_set.h>
#include <libj/string_builder.h>

#include <map>

namespace libj {
namespace detail {

template<typename I>
class Map : public I {
 private:
    typedef std::map<Value, Value> Container;
    typedef typename Container::const_iterator CItr;

    typedef typename I::Entry EntryT;
    typedef TypedSet<typename EntryT::CPtr> EntrySetT;
    typedef TypedIterator<typename EntryT::CPtr> EntryIteratorT;

 public:
    Map() : map_(NULL) {}

    virtual ~Map() { delete map_; }

    virtual Size size() const {
        return map_ ? map_->size() : 0;
    }

    virtual Boolean containsKey(const Value& key) const {
        return map_ && map_->find(key) != map_->end();
    }

    virtual Boolean containsValue(const Value& val) const {
        if (!map_) return false;

        CItr end = map_->end();
        for (CItr itr = map_->begin(); itr != end; ++itr) {
            if (!itr->second.compareTo(val))
                return true;
        }
        return false;
    }

    virtual Value get(const Value& key) const {
        return _get(key);
    }

    virtual Value put(const Value& key, const Value& val) {
        if (map_) {
            Value v = _get(key);
            (*map_)[key] = val;
            return v;
        } else {
            map_ = new Container();
            (*map_)[key] = val;
            return UNDEFINED;
        }
    }

    virtual Value remove(const Value& key) {
        if (map_) {
            Value v = _get(key);
            map_->erase(key);
            return v;
        } else {
            return UNDEFINED;
        }
    }

    virtual Set::CPtr keySet() const {
        return Set::CPtr(new KeySet(this));
    }

    virtual typename EntrySetT::CPtr entrySet() const {
        return typename EntrySetT::CPtr(new EntrySet(this));
    }

    virtual void clear() {
        if (map_) {
            map_->clear();
        }
    }

    virtual Boolean isEmpty() const {
        return map_ ? map_->size() == 0 : true;
    }

    virtual String::CPtr toString() const {
        libj::StringBuilder::Ptr sb = libj::StringBuilder::create();
        sb->appendChar('{');
        Boolean first = true;
        typename EntrySetT::CPtr es = this->entrySet();
        typename EntryIteratorT::Ptr itr = es->iteratorTyped();
        while (itr->hasNext()) {
            typename EntryT::CPtr e = itr->nextTyped();
            if (first) {
                first = false;
            } else {
                sb->appendStr(LIBJ_U(", "));
            }
            sb->append(e->getKey());
            sb->appendChar('=');
            sb->append(e->getValue());
        }
        sb->appendChar('}');
        return sb->toString();
    }

 private:
    class KeySet : public GenericCollection<Set, Value> {
     public:
        KeySet(const typename detail::Map<I>* self) : self_(self) {}

        virtual Size size() const {
            return self_->size();
        }

        virtual Iterator::Ptr iterator() const {
            return Iterator::Ptr(new KeyIterator(self_->map_));
        }

     public:
        class KeyIterator : public Iterator {
            friend class KeySet;

         public:
            virtual Boolean hasNext() const {
                return map_ && pos_ != end_;
            }

            virtual Value next() {
                if (!map_ || pos_ == end_) {
                    LIBJ_HANDLE_ERROR(Error::NO_SUCH_ELEMENT);
                } else {
                    Value key = pos_->first;
                    ++pos_;
                    return key;
                }
            }

            virtual String::CPtr toString() const {
                return String::create();
            }

         private:
            const typename Map<I>::Container* map_;
            typename Map<I>::CItr pos_;
            typename Map<I>::CItr end_;

            KeyIterator(const typename Map<I>::Container* map)
                : map_(map)
                , pos_(map ? map->begin() : typename Map<I>::CItr())
                , end_(map ? map->end() : typename Map<I>::CItr()) {}
        };

     public:
        virtual void clear() {
            LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
        }

        virtual Boolean add(const Value& v) {
            LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
            return false;
        }

        virtual Boolean remove(const Value& v) {
            LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
            return false;
        }

        virtual Boolean addTyped(const Value& v) {
            LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
            return false;
        }

        virtual Boolean removeTyped(const Value& v) {
            LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
            return false;
        }

        virtual TypedIterator<Value>::Ptr iteratorTyped() const {
            LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
            return TypedIterator<Value>::null();
        }

     private:
        const typename detail::Map<I>* self_;
    };

    class Entry : public EntryT {
        LIBJ_MUTABLE_TEMPLATE_DEFS(Entry, EntryT);

     public:
        void setKey(const Value& key) {
            key_ = key;
        }

        void setValue(const Value& val) {
            val_ = val;
        }

        virtual Value getKey() const {
            return key_;
        }

        virtual Value getValue() const {
            return val_;
        }

        virtual String::CPtr toString() const {
            return String::create();
        }

     private:
        Value key_;
        Value val_;
    };

    class EntrySet
        : public GenericCollection<EntrySetT, typename EntryT::CPtr> {
     public:
        EntrySet(const typename detail::Map<I>* self) : self_(self) {}

        virtual Size size() const {
            return self_->size();
        }

        virtual Iterator::Ptr iterator() const {
            return Iterator::Ptr(new TypedEntryIterator(self_->map_));
        }

        virtual typename EntryIteratorT::Ptr iteratorTyped() const {
            return typename EntryIteratorT::Ptr(
                new TypedEntryIterator(self_->map_));
        }

     public:
        class TypedEntryIterator : public EntryIteratorT {
            friend class EntrySet;

         public:
            virtual Boolean hasNext() const {
                return map_ && pos_ != end_;
            }

            virtual Value next() {
                if (!map_ || pos_ == end_) {
                    LIBJ_HANDLE_ERROR(Error::NO_SUCH_ELEMENT);
                } else {
                    entry_->setKey(pos_->first);
                    entry_->setValue(pos_->second);
                    ++pos_;
                    return typename Entry::CPtr(entry_);
                }
            }

            virtual typename EntryT::CPtr nextTyped() {
                if (!map_ || pos_ == end_) {
                    LIBJ_THROW(Error::NO_SUCH_ELEMENT);
                }

                entry_->setKey(pos_->first);
                entry_->setValue(pos_->second);
                ++pos_;
                return typename Entry::CPtr(entry_);
            }

            virtual String::CPtr toString() const {
                return String::create();
            }

         private:
            const typename Map<I>::Container* map_;
            typename Map<I>::CItr pos_;
            typename Map<I>::CItr end_;

            // reuse Entry for better performance
            typename Entry::Ptr entry_;

            TypedEntryIterator(const typename Map<I>::Container* map)
                : map_(map)
                , pos_(map ? map->begin() : typename Map<I>::CItr())
                , end_(map ? map->end() : typename Map<I>::CItr())
                , entry_(map ? new Entry() : NULL) {}
        };

     public:
        virtual void clear() {
            LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
        }

        virtual Boolean add(const Value& v) {
            LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
            return false;
        }

        virtual Boolean remove(const Value& v) {
            LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
            return false;
        }

        virtual Boolean addTyped(const typename EntryT::CPtr& v) {
            LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
            return false;
        }

        virtual Boolean removeTyped(const typename EntryT::CPtr& v) {
            LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
            return false;
        }

     private:
        const typename detail::Map<I>* self_;
    };

 private:
    Value _get(const Value& key) const {
        if (!map_) return UNDEFINED;

        CItr itr = map_->find(key);
        if (itr != map_->end()) {
            return itr->second;
        } else {
            return UNDEFINED;
        }
    }

 private:
    Container* map_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_MAP_H_
