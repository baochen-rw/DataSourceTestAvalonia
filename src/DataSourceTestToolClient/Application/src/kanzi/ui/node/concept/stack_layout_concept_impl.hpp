// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_STACK_LAYOUT_CONCEPT_IMPL_HPP
#define KZ_STACK_LAYOUT_CONCEPT_IMPL_HPP

#include "stack_layout.hpp"


namespace kanzi
{

template<typename TBaseClass, typename TDerivedClass>
TDerivedClass* StackLayoutConceptImpl<TBaseClass, TDerivedClass>::getThisObject()
{
    return static_cast<TDerivedClass*>(this);
}

template<typename TBaseClass, typename TDerivedClass>
const TDerivedClass* StackLayoutConceptImpl<TBaseClass, TDerivedClass>::getThisObject() const
{
    return static_cast<const TDerivedClass*>(this);
}

template<typename TBaseClass, typename TDerivedClass>
StackLayoutConcept::LayoutDirection StackLayoutConceptImpl<TBaseClass, TDerivedClass>::getDirection() const
{
    return getThisObject()->getProperty(DirectionProperty);
}

template<typename TBaseClass, typename TDerivedClass>
void StackLayoutConceptImpl<TBaseClass, TDerivedClass>::setDirection(StackLayoutConcept::LayoutDirection value)
{
    getThisObject()->setProperty(DirectionProperty, value);
}

template<typename TBaseClass, typename TDerivedClass>
bool StackLayoutConceptImpl<TBaseClass, TDerivedClass>::isReversed() const
{
    return getThisObject()->getProperty(ReversedProperty);
}

template<typename TBaseClass, typename TDerivedClass>
void StackLayoutConceptImpl<TBaseClass, TDerivedClass>::setReversed(bool value)
{
    getThisObject()->setProperty(ReversedProperty, value);
}

template<typename TBaseClass, typename TDerivedClass>
StackLayoutConceptImpl<TBaseClass, TDerivedClass>::StackLayoutConceptImpl(Domain* domain, string_view name):
TBaseClass(domain, name)
{
}

template<typename TBaseClass, typename TDerivedClass>
PropertyTypeEditorInfoSharedPtr StackLayoutConceptImpl<TBaseClass, TDerivedClass>::makeEditorInfo()
{
    return PropertyTypeEditorInfoSharedPtr(
        KZ_PROPERTY_TYPE_EDITOR_INFO(
            []() -> PropertyTypeEditorInfo::AttributeDictionary
            {
                PropertyTypeEditorInfo::AttributeDictionary dict;

                dict.displayName = "Stack Layout";

                return dict;
            }()
        ));
}

}

#endif
