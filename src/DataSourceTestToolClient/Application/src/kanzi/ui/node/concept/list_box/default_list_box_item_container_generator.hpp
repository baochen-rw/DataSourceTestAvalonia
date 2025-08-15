// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DEFAULT_LIST_BOX_ITEM_CONTAINER_GENERATOR_HPP
#define KZ_DEFAULT_LIST_BOX_ITEM_CONTAINER_GENERATOR_HPP


#include "list_box_item_container_generator.hpp"

#include <kanzi/ui/node/concept/list_box.hpp>

#include <kanzi/core.ui/resource/resource_manager.hpp>
#include <kanzi/core.ui/template/prefab.hpp>


namespace kanzi
{

template <typename TBaseGenerator>
class DefaultListBoxItemContainerGenerator : public TBaseGenerator
{
public:

    typedef shared_ptr<DefaultListBoxItemContainerGenerator<TBaseGenerator> > DefaultListBoxItemContainerGeneratorSharedPtr;

public:

    KZ_TEMPLATE_METACLASS_BEGIN(DefaultListBoxItemContainerGenerator, TBaseGenerator)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        return PropertyTypeEditorInfoSharedPtr();
    }

    static DefaultListBoxItemContainerGeneratorSharedPtr create(Domain* domain, string_view /*name*/)
    {
        return DefaultListBoxItemContainerGeneratorSharedPtr(new DefaultListBoxItemContainerGenerator(domain));
    }

    virtual void attach(typename TBaseGenerator::ListBoxType& node) KZ_OVERRIDE
    {
        using std::swap;

        // Acquire prefab template for item containers.
        PrefabTemplateSharedPtr itemContainerTemplate = dynamic_pointer_cast<PrefabTemplate>(node.getProperty(ListBoxConcept::ItemContainerTemplateProperty));

        swap(m_itemContainerTemplate, itemContainerTemplate);
    }

    virtual void detach(typename TBaseGenerator::ListBoxType& /*node*/) KZ_OVERRIDE
    {
    }

    virtual typename TBaseGenerator::ItemContainerSharedPtr acquireItemContainer(string_view name) KZ_OVERRIDE
    {
        typename TBaseGenerator::ItemContainerSharedPtr itemContainer;

        if(m_itemContainerTemplate)
        {
            // If item container prefab template is present, instantiate container from it.
            NodeSharedPtr itemContainerBase = m_itemContainerTemplate->template instantiate<Node>(name);
            itemContainer = dynamic_pointer_cast<typename TBaseGenerator::ItemContainer>(itemContainerBase);
        }
        else
        {
            // If no item container prefab template, just create the node as container.
            itemContainer = TBaseGenerator::ItemContainer::create(this->getDomain(), name);
        }

        return itemContainer;
    }

    /** Deletes an item container returned by createItem. */
    virtual void releaseItemContainer(typename TBaseGenerator::ItemContainerSharedPtr /*itemContainer*/) KZ_OVERRIDE
    {
        // Nothing to do
    }

    /** Gets size of an item container that would be created for an object of the given size. */
    virtual typename TBaseGenerator::VectorType getItemContainerSize(typename TBaseGenerator::VectorType itemSize) KZ_OVERRIDE
    {
        // TODO: return correct size or get rid of this function
        return itemSize;
    }

    /** Gets the object attached to the list box item. */
    virtual typename TBaseGenerator::ItemSharedPtr getItem(typename TBaseGenerator::ItemContainer& itemContainer) KZ_OVERRIDE
    {
        // Assume that node structure of container is not changing over time.
        return itemContainer.getChild(itemContainer.getChildCount() - 1);
    }

    /** Attaches an object to the list box item. */
    virtual void attachItem(typename TBaseGenerator::ItemContainer& itemContainer, typename TBaseGenerator::ItemSharedPtr item) KZ_OVERRIDE
    {
        // Add item as a last child of root node of container.
        // TODO: make location of item in container more definitive and reliable (i.e. property in container's root node with ref to the node where item should be added?)
        itemContainer.addChild(item);
    }

    /** Detaches the object contained by the list box item. */
    virtual void detachItem(typename TBaseGenerator::ItemContainer& itemContainer) KZ_OVERRIDE
    {
        // Assume that node structure of container is not changing over time.
        if (itemContainer.getChildCount() > 0) itemContainer.removeChild(itemContainer.getChildCount() - 1);
    }

protected:

    explicit DefaultListBoxItemContainerGenerator(Domain* domain) : TBaseGenerator(domain) {}

private:

    PrefabTemplateSharedPtr m_itemContainerTemplate;
};

}

#endif
