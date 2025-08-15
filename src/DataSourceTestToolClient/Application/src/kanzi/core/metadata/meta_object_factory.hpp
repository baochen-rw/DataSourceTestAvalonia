// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_OBJECT_FACTORY_HPP
#define KZ_OBJECT_FACTORY_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/metadata/metaclass.hpp>

#include <kanzi/core/cpp/unordered_map.hpp>
#include <kanzi/core/cpp/unordered_set.hpp>

namespace kanzi
{

// TODO: rename?
class KANZI_API ObjectFactory
{
    typedef unordered_map<string_view, const Metaclass*> MetaclassMap;
    typedef unordered_set<const Metaclass*> MetaclassContainer;    

public:

    void registerMetaclass(const Metaclass* metaclass);
    void overrideMetaclass(const Metaclass* metaclass);

    const Metaclass* getMetaclass(string_view className) const;

    typedef MetaclassMap::const_iterator RegisteredMetaclassIterator;
    RegisteredMetaclassIterator beginRegisteredMetaclasses() const { return cbegin(m_metaclasses); }
    RegisteredMetaclassIterator endRegisteredMetaclasses() const { return cend(m_metaclasses); }

    typedef MetaclassContainer::const_iterator MetaclassIterator;
    MetaclassIterator beginMetaclasses() const { return cbegin(m_allMetaclasses); }
    MetaclassIterator endMetaclasses() const { return cend(m_allMetaclasses); }

private:

    void registerMetaclassRecurse(const Metaclass* metaclass);

    MetaclassMap m_metaclasses;
    MetaclassContainer m_allMetaclasses;
};

template<typename T>
void registerMetaclass(ObjectFactory& objectFactory)
{
    const Metaclass* staticMetaclass = T::getStaticMetaclass();
    objectFactory.registerMetaclass(staticMetaclass);
}

template<typename T>
void overrideMetaclass(ObjectFactory& objectFactory)
{
    const Metaclass* staticMetaclass = T::getStaticMetaclass();
    objectFactory.overrideMetaclass(staticMetaclass);
}
}

#endif
