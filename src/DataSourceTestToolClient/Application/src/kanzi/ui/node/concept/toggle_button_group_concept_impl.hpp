// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TOGGLE_BUTTON_GROUP_CONCEPT_IMPL_HPP
#define KZ_TOGGLE_BUTTON_GROUP_CONCEPT_IMPL_HPP

#include "toggle_button_group.hpp"


namespace kanzi
{

template <class TBaseClass, class TDerivedClass>
ToggleButtonGroupConceptImpl<TBaseClass, TDerivedClass>::ToggleButtonGroupConceptImpl(Domain* domain, string_view name) :
    TBaseClass(domain, name),
    ToggleButtonGroupConcept(getThisObject())
{
}

template <class TBaseClass, class TDerivedClass>
void ToggleButtonGroupConceptImpl<TBaseClass, TDerivedClass>::initialize()
{
    TBaseClass::initialize();

    getThisObject()->addMessageFilter(ToggledMessage,
                                      getThisObject(), &ToggleButtonGroupConcept::onButtonGroupToggled);
}

template <class TBaseClass, class TDerivedClass>
PropertyTypeEditorInfoSharedPtr ToggleButtonGroupConceptImpl<TBaseClass, TDerivedClass>::makeEditorInfo()
{
    return PropertyTypeEditorInfoSharedPtr(
        KZ_PROPERTY_TYPE_EDITOR_INFO(
            []() -> PropertyTypeEditorInfo::AttributeDictionary {
                PropertyTypeEditorInfo::AttributeDictionary dict;

                dict.displayName = "Toggle Button Group";

                return dict;
            }()));
}
}

#endif
