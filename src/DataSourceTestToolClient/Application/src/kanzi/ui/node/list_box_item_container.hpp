// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LIST_BOX_ITEM_CONTAINER_HPP
#define KZ_LIST_BOX_ITEM_CONTAINER_HPP

#include <kanzi/ui/ui_api.hpp>

#include <kanzi/core.ui/node/node3d.hpp>
#include <kanzi/core.ui/input/click_manipulator.hpp>
#include <kanzi/core.ui/input/multi_click_manipulator.hpp>
#include <kanzi/core.ui/node/node2d.hpp>


namespace kanzi
{

class ListBoxItemContainer3D;

typedef shared_ptr<ListBoxItemContainer3D> ListBoxItemContainer3DSharedPtr;

class ListBoxItemContainer2D;

typedef shared_ptr<ListBoxItemContainer2D> ListBoxItemContainer2DSharedPtr;


/// Base class for List Box Item Containers for List Box.
class KANZI_UI_API ListBoxItemContainer
{
public:

    /// \name Properties
    /// \{
#include "list_box_item_container_properties.h"
    /// \}

    KZ_MIXIN_METACLASS_BEGIN(ListBoxItemContainer, "Kanzi.ListBoxItemContainer")
        KZ_METACLASS_PROPERTY_TYPE(SelectedProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
};

/// Implementation of base List Box Item Container class for List Box.
template <typename TBaseClass, typename TDerivedClass>
class KANZI_UI_TEMPLATE_API ListBoxItemContainerImpl : public TBaseClass, public ListBoxItemContainer
{
    TDerivedClass* getThisObject() { return static_cast<TDerivedClass*>(this); };

    const TDerivedClass* getThisObject() const { return static_cast<const TDerivedClass*>(this); };

public:

    KZ_TEMPLATE_METACLASS_BEGIN(ListBoxItemContainerImpl, TBaseClass)
        KZ_METACLASS_MIXIN(ListBoxItemContainer)
    KZ_METACLASS_END()

    /// Gets the value of #Selected.
    /// \see setSelected()
    bool isSelected() const { return getThisObject()->getProperty(SelectedProperty); };
    /// Sets the value of #Selected.
    /// \see isSelected()
    void setSelected(bool value) { getThisObject()->setProperty(SelectedProperty, value); };

protected:
    explicit ListBoxItemContainerImpl(Domain* domain, string_view name):
        TBaseClass(domain, name)
    {
    }

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        // TODO provide info
        return PropertyTypeEditorInfoSharedPtr();
    }
};

#ifdef KANZI_FEATURE_3D

/// List Box Item Container for List Box 3D. Wrapper component for storing item object nodes.
class KANZI_UI_API ListBoxItemContainer3D : public ListBoxItemContainerImpl<Node3D, ListBoxItemContainer3D>
{
    typedef ListBoxItemContainerImpl<Node3D, ListBoxItemContainer3D> BaseClass;

public:

    optional<size_t> getPresenterIndex() const { return m_presenterIndex; }
    void setPresenterIndex(optional<size_t> presenterIndex) { m_presenterIndex = presenterIndex; }

    /// Creates a list box item container node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name Name of the node.
    static ListBoxItemContainer3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(ListBoxItemContainer3D, BaseClass, "Kanzi.ListBoxItemContainer3D")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit ListBoxItemContainer3D(Domain* domain, string_view name);

    virtual void onAttached() KZ_OVERRIDE;
    virtual void onDetached() KZ_OVERRIDE;

private:

    ClassPropertyDefaultValue<bool> m_hitTestableClassDefaultValue;
    ClassPropertyDefaultValue<bool> m_hitTestableContainerClassDefaultValue;
    optional<size_t> m_presenterIndex;
    ClickManipulatorSharedPtr m_clickManipulator;
    MultiClickManipulatorSharedPtr m_multiClickManipulator;
};

#endif

/// List Box Item Container for List Box 2D. Wrapper component for storing item object nodes.
class KANZI_UI_API ListBoxItemContainer2D : public ListBoxItemContainerImpl<Node2D, ListBoxItemContainer2D>
{
    typedef ListBoxItemContainerImpl<Node2D, ListBoxItemContainer2D> BaseClass;

public:

    optional<size_t> getPresenterIndex() const { return m_presenterIndex; }
    void setPresenterIndex(optional<size_t> presenterIndex) { m_presenterIndex = presenterIndex; }

    /// Creates a list box item container node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name Name of the node.
    static ListBoxItemContainer2DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(ListBoxItemContainer2D, BaseClass, "Kanzi.ListBoxItemContainer2D")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit ListBoxItemContainer2D(Domain* domain, string_view name);

    virtual void onAttached() KZ_OVERRIDE;
    virtual void onDetached() KZ_OVERRIDE;

    /*virtual Vector2 measureOverride(Vector2 availableSize) KZ_OVERRIDE;
    virtual void arrangeOverride(Vector2 actualSize) KZ_OVERRIDE;*/

private:

    ClassPropertyDefaultValue<bool> m_hitTestableClassDefaultValue;
    optional<size_t> m_presenterIndex;
    ClickManipulatorSharedPtr m_clickManipulator;
    MultiClickManipulatorSharedPtr m_multiClickManipulator;
};

}

#endif
