// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_FLOW_LAYOUT_CONCEPT_IMPL_HPP
#define KZ_FLOW_LAYOUT_CONCEPT_IMPL_HPP

#include "flow_layout.hpp"

namespace kanzi
{

template <typename TBaseClass, typename TDerivedClass>
TDerivedClass* FlowLayoutConceptImpl<TBaseClass, TDerivedClass>::getThisObject()
{
    return static_cast<TDerivedClass*>(this);
}

template <typename TBaseClass, typename TDerivedClass>
const TDerivedClass* FlowLayoutConceptImpl<TBaseClass, TDerivedClass>::getThisObject() const
{
    return static_cast<const TDerivedClass*>(this);
}

template <typename TBaseClass, typename TDerivedClass>
FlowLayoutConcept::LayoutDirection FlowLayoutConceptImpl<TBaseClass, TDerivedClass>::getPrimaryDirection() const
{
    return getThisObject()->getProperty(PrimaryDirectionProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void FlowLayoutConceptImpl<TBaseClass, TDerivedClass>::setPrimaryDirection(LayoutDirection value)
{
    getThisObject()->setProperty(PrimaryDirectionProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
FlowLayoutConcept::LayoutDirection FlowLayoutConceptImpl<TBaseClass, TDerivedClass>::getSecondaryDirection() const
{
    return getThisObject()->getProperty(SecondaryDirectionProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void FlowLayoutConceptImpl<TBaseClass, TDerivedClass>::setSecondaryDirection(LayoutDirection value)
{
    getThisObject()->setProperty(SecondaryDirectionProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
FlowLayoutConceptImpl<TBaseClass, TDerivedClass>::FlowLayoutConceptImpl(Domain* domain, string_view name):
TBaseClass(domain, name)
{
}

template <typename TBaseClass, typename TDerivedClass>
PropertyTypeEditorInfoSharedPtr FlowLayoutConceptImpl<TBaseClass, TDerivedClass>::makeEditorInfo()
{
    return PropertyTypeEditorInfoSharedPtr(
        KZ_PROPERTY_TYPE_EDITOR_INFO(
            []() -> PropertyTypeEditorInfo::AttributeDictionary
            {
                PropertyTypeEditorInfo::AttributeDictionary dict;

                dict.displayName = "Flow Layout";

                return dict;
            }()
        ));
}

}

#endif
