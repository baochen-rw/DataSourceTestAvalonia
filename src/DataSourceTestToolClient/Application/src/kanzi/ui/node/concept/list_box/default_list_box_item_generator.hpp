// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DEFAULT_LIST_BOX_ITEM_GENERATOR_HPP
#define KZ_DEFAULT_LIST_BOX_ITEM_GENERATOR_HPP

#include <kanzi/core/cpp/vector.hpp>

#include "list_box_item_generator.hpp"


namespace kanzi
{

template <typename TBaseItemGenerator>
class DefaultListBoxItemGenerator : public TBaseItemGenerator
{
public:

    typedef shared_ptr<DefaultListBoxItemGenerator<TBaseItemGenerator> > DefaultListBoxItemGeneratorSharedPtr;

public:

    KZ_TEMPLATE_METACLASS_BEGIN(DefaultListBoxItemGenerator, TBaseItemGenerator)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        return PropertyTypeEditorInfoSharedPtr();
    }

    static DefaultListBoxItemGeneratorSharedPtr create(Domain* domain, string_view /*name*/)
    {
        return DefaultListBoxItemGeneratorSharedPtr(new DefaultListBoxItemGenerator(domain));
    }

    /** Returns the number of objects controlled by the list interface. */
    size_t getListCount()
    {
        return m_items.size();
    }

    /** Gets the object at the given index of the list. */
    typename TBaseItemGenerator::ItemSharedPtr getListObject(size_t index)
    {
        return m_items.at(index);
    }

    /** Finds index of the given object in the list. */
    optional<size_t> findListIndex(typename TBaseItemGenerator::ItemSharedPtr const& object)
    {
        typename ItemContainer::const_iterator it = find(cbegin(m_items), cend(m_items), object);
        if (it == cend(m_items))
        {
            return nullopt;
        }

        return distance(cbegin(m_items), it);
    }

    /** Inserts an object at the given index. */
    void insertListObject(size_t index, typename TBaseItemGenerator::ItemSharedPtr object)
    {
        if (index > m_items.size())
        {
            kzThrowException(out_of_range("Index out of range"));
        }

        m_items.insert(begin(m_items) + index, object);
    }

    /** Removes an object at the given index from the object generator's list. */
    void removeListObject(size_t index)
    {
        if (index >= m_items.size())
        {
            kzThrowException(out_of_range("Index out of range"));
        }

        m_items.erase(begin(m_items) + index);
    }

    /** Replaces the object at the given index in the object generator's list. */
    void replaceListObject(size_t index, typename TBaseItemGenerator::ItemSharedPtr object)
    {
        m_items.at(index) = object;
    }

    //////////////////////////////////////////////////////////////////////////

    /** Attaches the Object Generator. */
    virtual void attach(typename TBaseItemGenerator::ListBoxType& /*node*/) KZ_OVERRIDE
    {
    }

    /** Detaches the Object Generator. */
    virtual void detach(typename TBaseItemGenerator::ListBoxType& /*node*/) KZ_OVERRIDE
    {
    }

    /**
    * Gets an object that should be displayed at the given index.
    * If the object has already been created and not freed afterwards, returns the object from cache.
    */
    virtual typename TBaseItemGenerator::ItemSharedPtr acquireItem(size_t index) KZ_OVERRIDE
    {
        return getListObject(index);
    }

    /** Frees an object that has been returned from getObject. */
    virtual void releaseItem(typename TBaseItemGenerator::ItemSharedPtr /*object*/) KZ_OVERRIDE
    {
        // Nothing to do
    }

    /**
    * Gets index of an object that has been returned from getObject, or KZU_UI_LIST_BOX_NO_ITEM if
    * the object does not exist.
    */
    virtual optional<size_t> getItemIndex(typename TBaseItemGenerator::ItemSharedPtr object) KZ_OVERRIDE
    {
        return findListIndex(object);
    }

#ifdef KANZI_FEATURE_3D
    // TODO: move outside, or unify measure method names
    static void doRemeasure(Node3D& node)
    {
        node.measureRecursive();
    }
#endif

    static void doRemeasure(Node2D& node)
    {
        // TODO: pass correct available size
        node.measure(KZ_NULL, false);
    }

#ifdef KANZI_FEATURE_3D
    // TODO: move outside, or unify arrange method names
    static void doArrange(Node3D& node)
    {
        node.arrange();
    }
#endif

    static void doArrange(Node2D& node)
    {
        node.arrange();
    }

    /**
    * Gets exact size of the object that should be displayed at the given index.
    * This size will be used unless the list box is provided an object prototype.
    * If it is not possible to determine item size, unbounded layout value is returned.
    * Caching the sizes may be a good idea.
    */
    virtual typename TBaseItemGenerator::VectorType getItemSize(size_t index) KZ_OVERRIDE
    {
        // Index of item whose size is requested should always be within valid range.
        kzAssert(index < m_items.size());

        // Return unbounded layout value if item is not attached
        // (which means that it is not acquired by list box).
        if (!m_items.at(index)->isAttached())
        {
            return TBaseItemGenerator::Item::unboundedLayoutSize();
        }

        // Calculate item size.
        doRemeasure(*m_items.at(index));
        typename TBaseItemGenerator::VectorType desiredSize = m_items.at(index)->getDesiredSize();
        m_items.at(index)->setAllocatedSize(desiredSize);
        doArrange(*m_items.at(index));

        return desiredSize;
    }

    /**
    * Gets the number of objects known by the object generator.
    * Last index can be calculated as 'count' - 1.
    */
    virtual size_t getCount() KZ_OVERRIDE
    {
        return getListCount();
    }

protected:

    explicit DefaultListBoxItemGenerator(Domain* domain) : TBaseItemGenerator(domain) {}

private:

    typedef vector<typename TBaseItemGenerator::ItemSharedPtr> ItemContainer;
    ItemContainer m_items;
};

}

#endif
