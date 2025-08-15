// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LIST_BOX_ITEM_CONTAINER_GENERATOR_HPP
#define KZ_LIST_BOX_ITEM_CONTAINER_GENERATOR_HPP


#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/ui/node/list_box_item_container.hpp>


namespace kanzi
{

class ListBoxItemContainerGenerator2D : public Object
{
public:

    typedef Node2D ListBoxType;
    typedef Node2D::LayoutVectorType VectorType;
    typedef Node2D Item;
    typedef ListBoxItemContainer2D ItemContainer;
    typedef Node2DSharedPtr ItemSharedPtr;
    typedef ListBoxItemContainer2DSharedPtr ItemContainerSharedPtr;

    explicit ListBoxItemContainerGenerator2D(Domain* domain) : Object(domain) {}

    virtual ~ListBoxItemContainerGenerator2D() {}

    /** Attaches the Item Generator. */
    virtual void attach(ListBoxType& node) = 0;

    /** Detaches the Item Generator. */
    virtual void detach(ListBoxType& node) = 0;

    /** Outputs an empty item container for an object. */
    virtual ItemContainerSharedPtr acquireItemContainer(string_view name) = 0;

    /** Deletes an item container returned by createItem. */
    virtual void releaseItemContainer(ItemContainerSharedPtr itemContainer) = 0;

    /** Gets size of an item container that would be created for an object of the given size. */
    virtual VectorType getItemContainerSize(VectorType itemSize) = 0;

    /** Gets the object attached to the list box item. */
    virtual ItemSharedPtr getItem(ItemContainer& itemContainer) = 0;

    /** Attaches an object to the list box item. */
    virtual void attachItem(ItemContainer& itemContainer, ItemSharedPtr item) = 0;

    /** Detaches the object contained by the list box item. */
    virtual void detachItem(ItemContainer& itemContainer) = 0;
};

#ifdef KANZI_FEATURE_3D

class ListBoxItemContainerGenerator3D : public Object
{
public:

    typedef Node3D ListBoxType;
    typedef Node3D::LayoutVectorType VectorType;
    typedef Node3D Item;
    typedef ListBoxItemContainer3D ItemContainer;
    typedef Node3DSharedPtr ItemSharedPtr;
    typedef ListBoxItemContainer3DSharedPtr ItemContainerSharedPtr;

    KZ_ABSTRACT_METACLASS_BEGIN(ListBoxItemContainerGenerator3D, Object, "Kanzi.ListBoxItemContainerGenerator3D")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        return PropertyTypeEditorInfoSharedPtr();
    }

    /** Attaches the Item Generator. */
    virtual void attach(ListBoxType& node) = 0;

    /** Detaches the Item Generator. */
    virtual void detach(ListBoxType& node) = 0;

    /** Outputs an empty item container for an object. */
    virtual ItemContainerSharedPtr acquireItemContainer(string_view name) = 0;

    /** Deletes an item container returned by createItem. */
    virtual void releaseItemContainer(ItemContainerSharedPtr itemContainer) = 0;

    /** Gets size of an item container that would be created for an object of the given size. */
    virtual VectorType getItemContainerSize(VectorType itemSize) = 0;

    /** Gets the object attached to the list box item. */
    virtual ItemSharedPtr getItem(ItemContainer& itemContainer) = 0;

    /** Attaches an object to the list box item. */
    virtual void attachItem(ItemContainer& itemContainer, ItemSharedPtr item) = 0;

    /** Detaches the object contained by the list box item. */
    virtual void detachItem(ItemContainer& itemContainer) = 0;

protected:

    // Constructor.
    explicit ListBoxItemContainerGenerator3D(Domain* domain) : Object(domain) {}

    // Destructor.
    virtual ~ListBoxItemContainerGenerator3D() {}
};

#endif

}

#endif
