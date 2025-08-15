// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LIST_BOX_ITEM_GENERATOR_HPP
#define KZ_LIST_BOX_ITEM_GENERATOR_HPP

#include <kanzi/ui/ui_api.hpp>

#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/core.ui/node/node3d.hpp>


namespace kanzi
{

class KANZI_UI_API ListBoxItemGenerator2D : public Object
{
public:

    typedef Node2D ListBoxType;
    typedef Node2D Item;
    typedef Node2DSharedPtr ItemSharedPtr;
    typedef Item::LayoutVectorType VectorType;

    KZ_ABSTRACT_METACLASS_BEGIN(ListBoxItemGenerator2D, Object, "Kanzi.ListBoxItemGenerator2D")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        return PropertyTypeEditorInfoSharedPtr();
    }

    /** Attaches the Object Generator. */
    virtual void attach(ListBoxType& node) = 0;

    /** Detaches the Object Generator. */
    virtual void detach(ListBoxType& node) = 0;

    /**
    * Gets an object that should be displayed at the given index.
    * If the object has already been created and not freed afterwards, returns the object from cache.
    */
    virtual ItemSharedPtr acquireItem(size_t index) = 0;

    /** Frees an object that has been returned from getObject. */
    virtual void releaseItem(ItemSharedPtr object) = 0;

    /**
    * Gets index of an object that has been returned from getObject, or KZU_UI_LIST_BOX_NO_ITEM if
    * the object does not exist.
    */
    virtual optional<size_t> getItemIndex(ItemSharedPtr object) = 0;

    /**
    * Gets exact size of the object that should be displayed at the given index.
    * This size will be used unless the list box is provided an object prototype.
    * If it is not possible to determine item size without acquiring the item first,
    * unbounded layout value should be returned.
    * Caching the sizes may be a good idea.
    */
    virtual VectorType getItemSize(size_t index) = 0;

    /**
    * Gets the number of objects known by the object generator.
    * Last index can be calculated as 'count' - 1.
    */
    virtual size_t getCount() = 0;

protected:

    // Constructor.
    explicit ListBoxItemGenerator2D(Domain* domain) : Object(domain) {}

    /// Destructor.
    virtual ~ListBoxItemGenerator2D() { }
};

#ifdef KANZI_FEATURE_3D

class KANZI_UI_API ListBoxItemGenerator3D : public Object
{
public:

    typedef Node3D ListBoxType;
    typedef Node3D Item;
    typedef Node3DSharedPtr ItemSharedPtr;
    typedef Item::LayoutVectorType VectorType;

    KZ_ABSTRACT_METACLASS_BEGIN(ListBoxItemGenerator3D, Object, "Kanzi.ListBoxItemGenerator3D")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        return PropertyTypeEditorInfoSharedPtr();
    }

    /** Attaches the Object Generator. */
    virtual void attach(ListBoxType& node) = 0;

    /** Detaches the Object Generator. */
    virtual void detach(ListBoxType& node) = 0;

    /**
    * Gets an object that should be displayed at the given index.
    * If the object has already been created and not freed afterwards, returns the object from cache.
    */
    virtual ItemSharedPtr acquireItem(size_t index) = 0;

    /** Frees an object that has been returned from getObject. */
    virtual void releaseItem(ItemSharedPtr object) = 0;

    /**
    * Gets index of an object that has been returned from getObject, or KZU_UI_LIST_BOX_NO_ITEM if
    * the object does not exist.
    */
    virtual optional<size_t> getItemIndex(ItemSharedPtr object) = 0;

    /**
    * Gets exact size of the object that should be displayed at the given index.
    * This size will be used unless the list box is provided an object prototype.
    * If it is not possible to determine item size without acquiring the item first,
    * unbounded layout value should be returned.
    * Caching the sizes may be a good idea.
    */
    virtual VectorType getItemSize(size_t index) = 0;

    /**
    * Gets the number of objects known by the object generator.
    * Last index can be calculated as 'count' - 1.
    */
    virtual size_t getCount() = 0;

protected:

    // Constructor.
    explicit ListBoxItemGenerator3D(Domain* domain) : Object(domain) {}

    /// Destructor.
    virtual ~ListBoxItemGenerator3D() { }
};

#endif

}

#endif
