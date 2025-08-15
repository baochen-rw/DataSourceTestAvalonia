// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TOGGLE_BUTTON_GROUP_CONCEPT_HPP
#define KZ_TOGGLE_BUTTON_GROUP_CONCEPT_HPP

#include <kanzi/ui/ui_api.hpp>

#include <kanzi/core.ui/message/message_arguments.hpp>
#include <kanzi/core.ui/node/node.hpp>


namespace kanzi
{

/// ToggleButtonGroup contains properties that are common to both ToggleButtonGroup2D and ToggleButtonGroup3D.
class KANZI_UI_API ToggleButtonGroupConcept
{
public:
    unsigned int m_nextFreeId;

#include "toggle_button_group_properties.h"

    class KANZI_UI_API ToggleButtonGroupConceptMessageArguments : public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ToggleButtonGroupConceptMessageArguments, MessageArguments, "Kanzi.ToggleButtonGroupConcept.ToggleButtonGroupConceptMessageArguments")
        KZ_METACLASS_END()
    };

    class KANZI_UI_API ToggledMessageArguments : public ToggleButtonGroupConceptMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ToggledMessageArguments, ToggleButtonGroupConceptMessageArguments, "Kanzi.ToggleButtonGroupConcept.ToggledMessageArguments")
        KZ_METACLASS_END()
    };

    static MessageType<ToggledMessageArguments> ToggledMessage;

    template <typename TDerivedClass>
    ToggleButtonGroupConcept(TDerivedClass* derivedClass) :
        m_nextFreeId(0),
        m_derivedClass(derivedClass)
    {
    }

    Node* getDerivedObject() const
    {
        return m_derivedClass;
    }

    void unregisterButton(const Node* button);
    void onButtonGroupToggled(ToggledMessageArguments& message);

    /// Gets the value of #ToggledButtonIndexProperty.
    /// \see setToggledButtonIndex()
    int getCurrentButtonIndex() const
    {
        return m_derivedClass->getProperty(CurrentButtonIndexProperty);
    }

    KZ_MIXIN_METACLASS_BEGIN(ToggleButtonGroupConcept, "Kanzi.ToggleButtonConcept")
        KZ_METACLASS_PROPERTY_TYPE(CurrentButtonIndexProperty)
        KZ_METACLASS_MESSAGE_TYPE(ToggledMessage)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

private:
    Node* m_derivedClass;
    // Needed because the index property is not available anymore when the button is unregistered.
    NodeWeakPtr m_toggledButton;
};

template <class TBaseClass, class TDerivedClass>
class KANZI_UI_TEMPLATE_API ToggleButtonGroupConceptImpl : public TBaseClass, public ToggleButtonGroupConcept
{
public:
    KZ_TEMPLATE_METACLASS_BEGIN(ToggleButtonGroupConceptImpl, TBaseClass)
        KZ_METACLASS_MIXIN(ToggleButtonGroupConcept)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    ToggleButtonGroupConceptImpl(Domain* domain, string_view name);

    void initialize();

    virtual void onAttached() KZ_OVERRIDE
    {
        TBaseClass::onAttached();
        m_nextFreeId = 0;
    }

    virtual typename TBaseClass::LayoutVectorType measureOverride(typename TBaseClass::LayoutVectorType /*availableSize*/) KZ_OVERRIDE
    {
        typename TBaseClass::LayoutVectorType measuredSize;

        for (typename TBaseClass::ChildConstIterator it = TBaseClass::beginChildren(), end = TBaseClass::endChildren(); it != end; ++it)
        {
            typename TBaseClass::LayoutVectorType childSize = (*it)->getDesiredSize();
            measuredSize = componentWiseMax(measuredSize, childSize);
        }
        return measuredSize;
    }

protected:
    /// Internal accessor for the Curiously Recurring Template Pattern.
    inline TDerivedClass* getThisObject()
    {
        return static_cast<TDerivedClass*>(this);
    }

    /// Internal accessor for the Curiously Recurring Template Pattern.
    inline const TDerivedClass* getThisObject() const
    {
        return static_cast<const TDerivedClass*>(this);
    }
};
}

#endif
