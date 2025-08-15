// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DOCK_LAYOUT_CONCEPT_IMPL_HPP
#define KZ_DOCK_LAYOUT_CONCEPT_IMPL_HPP

#include "dock_layout.hpp"

#include <kanzi/core.ui/node/node.hpp>

namespace kanzi
{

template <typename TBaseClass, typename TDerivedClass>
TDerivedClass* DockLayoutConceptImpl<TBaseClass, TDerivedClass>::getThisObject()
{
    return static_cast<TDerivedClass*>(this);
}

template <typename TBaseClass, typename TDerivedClass>
const TDerivedClass* DockLayoutConceptImpl<TBaseClass, TDerivedClass>::getThisObject() const
{
    return static_cast<const TDerivedClass*>(this);
}

template <typename TBaseClass, typename TDerivedClass>
bool DockLayoutConceptImpl<TBaseClass, TDerivedClass>::isLastItemFill() const
{
    return getThisObject()->getProperty(LastItemFillProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void DockLayoutConceptImpl<TBaseClass, TDerivedClass>::setLastItemFill(bool value)
{
    getThisObject()->setProperty(LastItemFillProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
DockLayoutConcept::DockingSide DockLayoutConceptImpl<TBaseClass, TDerivedClass>::getSide(const Node& item)
{
    return item.getProperty(SideProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void DockLayoutConceptImpl<TBaseClass, TDerivedClass>::setSide(Node& item, DockLayoutConcept::DockingSide value)
{
    item.setProperty(SideProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
DockLayoutConceptImpl<TBaseClass, TDerivedClass>::DockLayoutConceptImpl(Domain* domain, string_view name):
TBaseClass(domain, name)
{
}

template <typename TBaseClass, typename TDerivedClass>
PropertyTypeEditorInfoSharedPtr DockLayoutConceptImpl<TBaseClass, TDerivedClass>::makeEditorInfo()
{
    return PropertyTypeEditorInfoSharedPtr(
        KZ_PROPERTY_TYPE_EDITOR_INFO(
            []() -> PropertyTypeEditorInfo::AttributeDictionary
            {
                PropertyTypeEditorInfo::AttributeDictionary dict;

                dict.displayName = "Dock Layout";

                return dict;
            }()
        ));
}

}

#endif
