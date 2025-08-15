// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LIST_BOX_CONCEPT_IMPL_HPP
#define KZ_LIST_BOX_CONCEPT_IMPL_HPP

#include "list_box.hpp"

#include "list_box/default_list_box_item_container_generator.hpp"
#include "list_box/list_box_item_generator.hpp"

#include <kanzi/core.ui/data/data_context.hpp>
#include <kanzi/core/metadata/meta_object_factory.hpp>
#include <kanzi/core/metadata/metaclass.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/util/flag_scope_guard.hpp>
#include <kanzi/core.ui/command/command.hpp>



// Suppress false positives from use of optional.
#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic push
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 6)
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
#endif

namespace kanzi
{

namespace
{
    // Utility function, creates instance by type name.
    template <typename TClass>
    shared_ptr<TClass> createInstanceByType(Domain* domain, const string& typeName, const string& instanceName)
    {
        ObjectFactory* objectFactory = domain->getObjectFactory();
        const Metaclass* typeMetaClass = objectFactory->getMetaclass(typeName);
        shared_ptr<TClass> instance;

        if (typeMetaClass)
        {
            instance = typeMetaClass->create<TClass>(domain, instanceName);
        }

        return instance;
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
TDerivedClass* ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getThisObject()
{
    return static_cast<TDerivedClass*>(this);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
const TDerivedClass* ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getThisObject() const
{
    return static_cast<const TDerivedClass*>(this);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
bool ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::addContentItem(NodeSharedPtr abstractItem)
{
    ItemSharedPtr item = dynamic_pointer_cast<ItemClass>(abstractItem);
    if (!item)
    {
        return false;
    }

    addItem(item);
    return true;
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
bool ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::removeContentItem(NodeSharedPtr abstractItem)
{
    ItemSharedPtr item = dynamic_pointer_cast<ItemClass>(abstractItem);
    if (!item)
    {
        return false;
    }

    optional<size_t> index = getItemIndex(item);
    if (!index)
    {
        return false;
    }

    removeItem(*index);
    return true;
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::removeAllContentItems()
{
    removeAllItems();
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
size_t ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getContentItemCount()
{
    return getItemCount();
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
NodeSharedPtr ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getContentItem(size_t index)
{
    return getItem(index);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
size_t ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getItemCount()
{
    return m_itemGenerator->getCount();
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
optional<pair<size_t, size_t> > ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getAliveRange() 
{
    if (!getItemCount())
    {
        return nullopt;
    }
    else
    {
        return make_pair(m_beginIndex, m_itemCount);
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
bool ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::isEmpty()
{
    return getItemCount() == 0;
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
typename ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::LayoutVectorType ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getItemSize(size_t index)
{
    // Get item size of item container.
    const LayoutVectorType itemSize = m_itemGenerator->getItemSize(index);

    // If item container could not determine item size, return it as is.
    if (ItemClass::isUnboundedLayoutSize(itemSize))
    {
        return itemSize;
    }

    return m_itemContainerGenerator->getItemContainerSize(itemSize);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
optional<size_t> ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getItemIndex(ItemSharedPtr item)
{
    return m_itemGenerator->getItemIndex(item);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
typename ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::ItemSharedPtr ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getItem(size_t index)
{
    return m_itemGenerator->acquireItem(index);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::insertItem(size_t index, ItemSharedPtr item)
{
    m_defaultItemGenerator->insertListObject(index, item);

    // Notify item addition if default item generator is current item generator.
    if (m_defaultItemGenerator == m_itemGenerator)
    {
        notifyItemAdded(index);
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::removeItem(size_t index)
{
    // Notify item removal if default item generator is current item generator.
    if (m_defaultItemGenerator == m_itemGenerator)
    {
        notifyItemRemoved(index);
    }

    m_defaultItemGenerator->removeListObject(index);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::replaceItem(size_t index, ItemSharedPtr item)
{
    m_defaultItemGenerator->replaceListObject(index, item);

    // Notify item replacement if default item generator is current item generator.
    if (m_defaultItemGenerator == m_itemGenerator)
    {
        notifyItemReplaced(index);
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::addItem(ItemSharedPtr item)
{
    insertItem(m_defaultItemGenerator->getListCount(), item);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::removeLastItem()
{
    size_t index = m_defaultItemGenerator->getListCount() - 1;
    removeItem(index);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::removeAllItems()
{
    // TODO: implement direct clearing
    while (m_defaultItemGenerator->getCount() > 0)
    {
        removeLastItem();
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::applySelectionBehavior(size_t itemIndex, bool smooth)
{
    switch (getSelectionBehavior())
    {
        case SelectionBehaviorBringToCenter:
        {
            bringItemCenter(itemIndex, smooth);
            break;
        }
        // If no behavior do nothing.
        case SelectionBehaviorNone:
        default:
        {
            break;
        }
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::synchronizeSelectedItemIndexProperty()
{
    FlagScopeGuard<true> itemSelectionRecursionGuard(m_itemSelectionRecursionGuard);
    int selectedItemIndex = m_selectedItemIndex.value_or(-1);

    if (getSelectedItemIndex() != selectedItemIndex)
    {
        setSelectedItemIndex(selectedItemIndex);
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::selectItem(optional<size_t> itemIndex)
{
    optional<size_t> prevSelectedItemIndex = m_selectedItemIndex;
    optional<size_t> newSelectedItemIndex;

    // Calculate new selected item index.
    if (getItemCount() && itemIndex)
    {
        // If list box has items and item index is specified, clamp index to valid range. Otherwise leave it unspecified (no selection).
        newSelectedItemIndex = kzsClampui(*itemIndex, 0, getItemCount() - 1);
    }

    // Select new element (or un-select element) if new selected item index is different from current one.
    if (prevSelectedItemIndex != newSelectedItemIndex)
    {
        // Store index on selected item.
        m_selectedItemIndex = newSelectedItemIndex;

        // Unset selection on container of previously selected items if present.
        if (prevSelectedItemIndex)
        {
            // Find item info by index and unset selection on its container.
            // If item does not exist (not in visible range), just skip unsetting selection.
            typename IndexMap::const_iterator found = m_itemIndexMap.find(*prevSelectedItemIndex);

            if (found != cend(m_itemIndexMap))
            {
                ItemInfoSharedPtr itemInfo = found->second;
                itemInfo->itemContainer->setSelected(false);
            }
        }

        string command;

        // Set selection on container of newly selected items if present.
        if (newSelectedItemIndex)
        {
            // Find item info by index and set selection on its container.
            // If item does not exist (not in visible range), list box will set selection on it when it will be created in updateVisibleRange.
            typename IndexMap::const_iterator found = m_itemIndexMap.find(*newSelectedItemIndex);

            if (found != cend(m_itemIndexMap))
            {
                ItemInfoSharedPtr itemInfo = found->second;
                itemInfo->itemContainer->setSelected(true);

                // Get the command associated with the item.
                command = itemInfo->itemContainer->getProperty(Command::CommandProperty);
            }
        }

        // Synchronize SelectedItemIndex property before sending message about selected item.
        synchronizeSelectedItemIndexProperty();

        // Create message about item being selected.
        ItemSelectedMessageArguments itemSelectedMessageArguments;

        itemSelectedMessageArguments.setPreviouslySelectedItemIndex(prevSelectedItemIndex);
        itemSelectedMessageArguments.setSelectedItemIndex(newSelectedItemIndex);

        // Send message about item being selected.
        getThisObject()->dispatchMessage(ItemSelectedMessage, itemSelectedMessageArguments);

        // Dispatch command message.
        if (command.empty())
        {
            // Try to get the command from the listbox itself if the item does not specify it.
            command = getThisObject()->getProperty(Command::CommandProperty);
        }
        if (!command.empty())
        {
            Command::CommandMessageArguments commandArguments;
            commandArguments.setCommand(kanzi::move(command));
            getThisObject()->dispatchMessage(Command::CommandMessage, commandArguments);
        }
    }
    else
    {
        // If selection index did not change, synchronize SelectedItemIndex property anyway to set clamped (or invalid) value.
        synchronizeSelectedItemIndexProperty();
    }

    // Apply selection behavior in any case (even if not changing selection).
    // This should bring the item to center even if already selected.
    if (newSelectedItemIndex)
    {
        applySelectionBehavior(*newSelectedItemIndex, true);
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::notifyItemAdded(size_t index)
{
    m_presenter->notifyItemAdded(index);

    // We need to rearrange to create the list box item(s).
    // Arrange is not happening when the layout's size is fixed (as in GridListBox2D) due to the propagateMeasure optimization in Node2D.
    getThisObject()->invalidateArrange();

    /* For all item infos after or at the added index, shift index up by one. */
    {
        m_itemIndexMap.clear();

        for (typename ItemMap::const_iterator i = cbegin(m_itemMap), end = cend(m_itemMap); i != end; ++i)
        {
            ItemInfoSharedPtr shiftedItemInfo = i->second;
            if(shiftedItemInfo->index >= index)
            {
                ++shiftedItemInfo->index;
                    
                shiftedItemInfo->itemContainer->setPresenterIndex(shiftedItemInfo->index);
            }
            m_itemIndexMap[shiftedItemInfo->index] = shiftedItemInfo;
        }
    }

    // If item was added before selected item (so that index of selected item has changed), shift selection index as well.
    if (m_selectedItemIndex && *m_selectedItemIndex >= index)
    {
        (*m_selectedItemIndex)++;

        // Synchronize SelectedItemIndex property after selected index has changed.
        synchronizeSelectedItemIndexProperty();
    }

    m_forceUpdate = true;
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::notifyItemRemoved(size_t index)
{
    m_presenter->notifyItemRemoved(index);

    // We need to rearrange to create the list box item(s).
    // Arrange is not happening when the layout's size is fixed (as in GridListBox2D) due to the propagateMeasure optimization in Node2D.
    getThisObject()->invalidateArrange();

    typename IndexMap::const_iterator found = m_itemIndexMap.find(index);
    if (found != cend(m_itemIndexMap))
    {
        ItemInfoSharedPtr removedItemInfo = found->second;
        /* Delete old item from data structures. */
        removedItemInfo->itemContainer->setPresenterIndex(nullopt);
        m_presenter->removeFromLayout(removedItemInfo->itemContainer);

        m_itemMap.erase(removedItemInfo->item);
        m_itemContainerMap.erase(removedItemInfo->itemContainer);
        m_itemIndexMap.erase(found);

        m_itemContainerGenerator->detachItem(*removedItemInfo->itemContainer);
        m_itemContainerGenerator->releaseItemContainer(removedItemInfo->itemContainer);

        // Don't release the index from the item generator. The generator is the one calling us.
    }

    /* For all item infos after the removed index, shift index down by one. */
    {
        m_itemIndexMap.clear();

        for (typename ItemMap::const_iterator i = cbegin(m_itemMap), end = cend(m_itemMap); i != end; ++i)
        {
            ItemInfoSharedPtr shiftedItemInfo = i->second;
            if(shiftedItemInfo->index > index)
            {
                --shiftedItemInfo->index;
                shiftedItemInfo->itemContainer->setPresenterIndex(shiftedItemInfo->index);
            }

            m_itemIndexMap[shiftedItemInfo->index] = shiftedItemInfo;
        }
    }

    // Update selection after item has been removed.
    if (m_selectedItemIndex)
    {
        if(*m_selectedItemIndex == index)
        {
            // Selected item was removed: reset selection
            m_selectedItemIndex = nullopt;

            // synchronize SelectedItemIndex property
            synchronizeSelectedItemIndexProperty();

            // and send message about it.
            ItemSelectedMessageArguments itemSelectedMessageArguments;

            itemSelectedMessageArguments.setPreviouslySelectedItemIndex(nullopt);
            itemSelectedMessageArguments.setSelectedItemIndex(nullopt);

            getThisObject()->dispatchMessage(ItemSelectedMessage, itemSelectedMessageArguments);
        }
        else if(*m_selectedItemIndex > index)
        {
            // An item before selected item index was removed, update selection index.
            (*m_selectedItemIndex)--;

            // Synchronize SelectedItemIndex property after selected index has changed.
            synchronizeSelectedItemIndexProperty();
        }
    }

    m_forceUpdate = true;
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::notifyItemReplaced(size_t index)
{
    // We need to rearrange to create the list box item(s).
    // Arrange is not happening when the layout's size is fixed (as in GridListBox2D) due to the propagateMeasure optimization in Node2D.
    getThisObject()->invalidateArrange();

    typename IndexMap::const_iterator found = m_itemIndexMap.find(index);
    if (found != cend(m_itemIndexMap))
    {
        ItemInfoSharedPtr itemInfo = found->second;

        /* Delete old item from data structures. */
        m_itemMap.erase(itemInfo->item);

        m_itemContainerGenerator->detachItem(*itemInfo->itemContainer);

        /* Don't call kzuObjectGeneratorFreeObject here. */

        /* Add new item to data structures. */
        itemInfo->item = m_itemGenerator->acquireItem(index);

        m_itemContainerGenerator->attachItem(*itemInfo->itemContainer, itemInfo->item);

        m_itemMap[itemInfo->item] = itemInfo;

        // Item container remains the same after replacing item, no need to update selection in container.
    }

    m_forceUpdate = true;
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::notifyItemContainerChanged()
{
    if (m_presenter)
    {
        m_presenter->notifyItemContainerChanged();
    }

    // Detach all items in item map.
    for (typename ItemMap::iterator it = m_itemMap.begin(), endIt = m_itemMap.end(); (it != endIt); ++it)
    {
        ItemInfoSharedPtr removedItemInfo = it->second;
        
        m_presenter->removeFromLayout(removedItemInfo->itemContainer);
        m_itemContainerGenerator->detachItem(*removedItemInfo->itemContainer);
        m_itemContainerGenerator->releaseItemContainer(removedItemInfo->itemContainer);
    }
    m_itemMap.clear();
    m_itemContainerMap.clear();

    m_forceUpdate = true;
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::notifyItemCountChanged()
{
    // Give presenter a chance to update its state before arrange.
    m_presenter->update();

    doListBoxArrange(*this);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
Vector2 ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::doMeasure(Node2D& /*node*/)
{
    return Vector2(TBaseClass::unboundedLayoutValue(), TBaseClass::unboundedLayoutValue());
}

#ifdef KANZI_FEATURE_3D

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
Vector3 ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::doMeasure(Node3D& /*node*/)
{
    return Vector3(0.0f, 0.0f, 0.0f);
}

#endif

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
typename ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::LayoutVectorType ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::measureOverride(LayoutVectorType /*availableSize*/)
{
    return doMeasure(*this);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::arrangeOverride(LayoutVectorType /*actualSize*/)
{
    // Give presenter a chance to update its state before arrange.
    m_presenter->update();

    doListBoxArrange(*this);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::updateVisibleRangeQuiet(size_t beginIndex, size_t itemCount)
{
    if(m_forceUpdate || m_beginIndex != beginIndex || m_itemCount != itemCount)
    {
        updateVisibleRange(beginIndex, itemCount, false);
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::updateVisibleRange(size_t beginIndex, size_t itemCount)
{
    if(m_forceUpdate || m_beginIndex != beginIndex || m_itemCount != itemCount)
    {
        updateVisibleRange(beginIndex, itemCount, true);
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::updateVisibleRange(size_t beginIndex, size_t itemCount, bool sendMessages)
{
    using std::swap;
    unsigned int totalItemCount = getItemCount();

    kzAssert(itemCount <= totalItemCount);

    /* Swap object buffers. */
    swap(m_itemMap, m_itemMapBuffer);

    /* Prepare tables. */
    m_itemIndexMap.clear();
    m_itemMap.clear();

    /* Add visible items to data structures. */
    for(unsigned int i = 0; i < itemCount; ++i)
    {
        ItemInfoSharedPtr itemInfo;
        unsigned int index = (beginIndex + i) % totalItemCount;

        /* Get object at the current index. */
        ItemSharedPtr object = m_itemGenerator->acquireItem(index);

        /* Check that duplicate items aren't being inserted. */
        if(m_itemMap.find(object) != end(m_itemMap))
        {
            kzThrowException(logic_error("Logic"));
        }

        /* See if object existed already or if it was new. */
        typename ItemMap::iterator found = m_itemMapBuffer.find(object);
        if(found != end(m_itemMapBuffer))
        {
            itemInfo = found->second;
            /* Existed. Remove from list of candidates to be hidden. */
            m_itemMapBuffer.erase(found);

            /* Add to database. */
            m_itemIndexMap[itemInfo->index] =  itemInfo;

            m_itemMap[object] = itemInfo;

            // TODO: why is listbox updating presenter index?
            /* Update old item position in the layout. */
            itemInfo->itemContainer->setPresenterIndex(index);
        }
        else
        {
            /* Object did not exist. Create new item. */
            ItemContainerSharedPtr container;

            /* Create item. */
            {
                string itemName = object->getName() + " (List Box Item)";

                container = m_itemContainerGenerator->acquireItemContainer(itemName);

                m_itemContainerGenerator->attachItem(*container, object);
            }

            /* Add item to data structures. */
            {
                // TODO: add pool
                itemInfo = ItemInfoSharedPtr(new ItemInfo(container, object, index));

                m_itemIndexMap[itemInfo->index] = itemInfo;

                m_itemContainerMap[container] = itemInfo;

                m_itemMap[object] = itemInfo;
            }

            /* Add new item to layout. */
            itemInfo->itemContainer->setPresenterIndex(index);
            m_presenter->addToLayout(itemInfo->itemContainer);

            /* If new item is selected, set selection on its container, otherwise make it not selected. */
            bool itemSelected = (m_selectedItemIndex && *m_selectedItemIndex == index);
            itemInfo->itemContainer->setSelected(itemSelected);

            /* Send 'visible item' message. */
            if(sendMessages)
            {
                ItemVisibleMessageArguments itemVisibleMessageArguments;

                itemVisibleMessageArguments.setItem(object);
                itemVisibleMessageArguments.setItemIndex(index);

                getThisObject()->dispatchMessage(ItemVisibleMessage, itemVisibleMessageArguments);
            }
        }
    }

    /* Handle objects that were hidden. */
    {
        for (typename ItemMap::iterator it = begin(m_itemMapBuffer), itEnd = end(m_itemMapBuffer); it != itEnd; ++it)
        {
            ItemSharedPtr object = it->first;
            ItemInfoSharedPtr itemInfo = it->second;

            kzAssert(itemInfo->item == object);

            // TODO: use index to remove, its constant time operation
            itemInfo->itemContainer->setPresenterIndex(nullopt);
            m_presenter->removeFromLayout(itemInfo->itemContainer);

            /* Send 'hidden' message. */
            if(sendMessages)
            {
                ItemHiddenMessageArguments itemHiddenMessageArguments;

                itemHiddenMessageArguments.setItem(object);
                itemHiddenMessageArguments.setItemIndex(itemInfo->index);

                getThisObject()->dispatchMessage(ItemHiddenMessage, itemHiddenMessageArguments);
            }

            /* Delete item from data structures. */
            m_itemContainerMap.erase(itemInfo->itemContainer);

            /* Free container and object. */
            {
                m_itemContainerGenerator->detachItem(*itemInfo->itemContainer);

                m_itemContainerGenerator->releaseItemContainer(itemInfo->itemContainer);

                m_itemGenerator->releaseItem(object);
            }
        }

        /* Clear item map buffer so that list box does not share ownership of released objects. */
        m_itemMapBuffer.clear();
    }

    m_beginIndex = beginIndex;
    m_itemCount = itemCount;
    m_forceUpdate = false;

    kzAssert(m_itemCount == m_itemIndexMap.size());
    kzAssert(m_itemCount == m_itemContainerMap.size());
    kzAssert(m_itemCount == m_itemMap.size());
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
typename ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::ScrollViewSharedPtr ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getScrollView() const
{
    return m_scrollView;
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::bringItemCenter(size_t itemIndex, bool smooth)
{
    // TODO: throw exception or clamp at item count
    // size_t totalItemCount = getItemCount();
    // kzsErrorTest(itemIndex < totalItemCount, KZS_ERROR_ILLEGAL_ARGUMENT, ("Selection index out of range"));

    /* Get target offset. */
    Vector2 scrollTarget = m_presenter->bringItemCenter(itemIndex);

    /* Set scroll. */
    if (!smooth)
    {
        /* Immediate: Set both target and position. */
        sendSetScrollViewScrollMessage(scrollTarget);
    }

    sendScrollViewScrollTargetMessage(scrollTarget);

    sendListBoxTargetChangedMessage(itemIndex);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
int ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getKeepAliveItemCount() const
{
    return getThisObject()->getProperty(KeepAliveItemCountProperty);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::setKeepAliveItemCount(int value)
{
    getThisObject()->setProperty(KeepAliveItemCountProperty, value);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
int ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getSelectedItemIndex() const
{
    return getThisObject()->getProperty(SelectedItemIndexProperty);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::setSelectedItemIndex(int value)
{
    getThisObject()->setProperty(SelectedItemIndexProperty, value);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
ListBoxConcept::SelectionBehavior ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getSelectionBehavior() const
{
    return getThisObject()->getProperty(SelectionBehaviorProperty);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::setSelectionBehavior(SelectionBehavior value)
{
    getThisObject()->setProperty(SelectionBehaviorProperty, value);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
string ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getItemGeneratorTypeName() const
{
    return getThisObject()->getProperty(ItemGeneratorTypeNameProperty);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::setItemGeneratorTypeName(string_view value)
{
    getThisObject()->setProperty(ItemGeneratorTypeNameProperty, string(value));
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
string ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getItemContainerGeneratorTypeName() const
{
    return getThisObject()->getProperty(ItemContainerGeneratorTypeNameProperty);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::setItemContainerGeneratorTypeName(string_view value)
{
    getThisObject()->setProperty(ItemContainerGeneratorTypeNameProperty, string(value));
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
PrefabTemplateSharedPtr ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getItemTemplate() const
{
    return dynamic_pointer_cast<PrefabTemplate>(getThisObject()->getProperty(ItemTemplateProperty));
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::setItemTemplate(PrefabTemplateSharedPtr value)
{
    getThisObject()->setProperty(ItemTemplateProperty, value);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
PrefabTemplateSharedPtr ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::getItemContainerTemplate() const
{
    return dynamic_pointer_cast<PrefabTemplate>(getThisObject()->getProperty(ItemContainerTemplateProperty));
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::setItemContainerTemplate(PrefabTemplateSharedPtr value)
{
    getThisObject()->setProperty(ItemContainerTemplateProperty, value);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::assignItemGenerator(ItemGeneratorSharedPtr itemGenerator)
{
    if (!itemGenerator)
    {
        itemGenerator = m_defaultItemGenerator;
    }

    updateGenerators(itemGenerator, m_itemContainerGenerator);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::setItemGeneratorByProperty()
{
    // Create item generator if its valid type name specified in ItemGeneratorTypeName property.
    string itemGeneratorTypeName = getItemGeneratorTypeName();

    if (!m_itemGenerator || m_itemGenerator->getStaticMetaclass()->getName() != itemGeneratorTypeName)
    {
        Domain* domain = getThisObject()->getDomain();
        ItemGeneratorSharedPtr itemGenerator = createInstanceByType<ItemGeneratorClass>(domain, itemGeneratorTypeName, "ListBoxItemGenerator");

        if (!itemGenerator && !itemGeneratorTypeName.empty())
        {
            kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Failed to create item generator of type '{}' for '{}' list box: item generator class should be registered in object factory and should be compatible with base item generator class specified in list box.", itemGeneratorTypeName, getThisObject()->getName()));
        }

        assignItemGenerator(itemGenerator);
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::setItemGenerator(ItemGeneratorSharedPtr itemGenerator)
{
    assignItemGenerator(itemGenerator);

    // Set the type name of item generator to the property, so that the generator is not overridden unless the property actually changes.
    setItemGeneratorTypeName(m_itemGenerator->getStaticMetaclass()->getName().c_str());
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::assignItemContainerGenerator(ItemContainerGeneratorSharedPtr itemContainerGenerator)
{
    // If failed to create container generator, fall back to default one.
    if (!itemContainerGenerator)
    {
        Domain* domain = getThisObject()->getDomain();
        itemContainerGenerator = DefaultListBoxItemContainerGenerator<ItemContainerGeneratorClass>::create(domain, "DefaultListBoxItemContainerGenerator");
    }

    updateGenerators(m_itemGenerator, itemContainerGenerator);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::updateGenerators(ItemGeneratorSharedPtr itemGenerator, ItemContainerGeneratorSharedPtr itemContainerGenerator)
{
    if (itemGenerator == m_itemGenerator && itemContainerGenerator == m_itemContainerGenerator)
    {
        return;
    }

    // Detach & reset old data structures.
    if (getThisObject()->isAttached() || getThisObject()->isAttaching())
    {
        kzAssert(m_itemGenerator);
        kzAssert(m_itemContainerGenerator);

        m_itemGenerator->detach(*getThisObject());
        m_itemContainerGenerator->detach(*getThisObject());
    }

    // TODO: notify presenter that generator changed and all old items must be released.
    // Do cleanup on local copies of everything.
    using std::swap;
    swap(m_itemGenerator, itemGenerator);
    swap(m_itemContainerGenerator, itemContainerGenerator);

    if (getThisObject()->isAttached() || getThisObject()->isAttaching())
    {
        kzAssert(m_itemGenerator);
        kzAssert(m_itemContainerGenerator);

        m_itemGenerator->attach(*getThisObject());
        m_itemContainerGenerator->attach(*getThisObject());

        // Reset selected item index if any.
        if (m_selectedItemIndex)
        {
            selectItem(nullopt);
        }

        // Force the list box to rearrange items.
        getThisObject()->invalidateArrange();
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::setItemContainerGeneratorByProperty()
{
    // Create item container generator if its valid type name specified in ItemContainerGeneratorTypeName property.
    string itemContainerGeneratorTypeName = getItemContainerGeneratorTypeName();

    if (!m_itemContainerGenerator || m_itemContainerGenerator->getStaticMetaclass()->getName() != itemContainerGeneratorTypeName)
    {
        Domain* domain = getThisObject()->getDomain();
        ItemContainerGeneratorSharedPtr itemContainerGenerator = createInstanceByType<ItemContainerGeneratorClass>(domain, itemContainerGeneratorTypeName, "ListBoxItemContainerGenerator");

        if (!itemContainerGenerator && !itemContainerGeneratorTypeName.empty())
        {
            kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Failed to create item container generator of type '{}' for '{}' list box: item container generator class should be registered in object factory and should be compatible with base item container generator class specified in list box.", itemContainerGeneratorTypeName, getThisObject()->getName()));
        }

        assignItemContainerGenerator(itemContainerGenerator);
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::setItemContainerGenerator(ItemContainerGeneratorSharedPtr itemContainerGenerator)
{
    // Assign item container generator.
    assignItemContainerGenerator(itemContainerGenerator);

    // Set the type name of item container generator to the property, so that the generator is not overriden unless the property actually changes.
    setItemContainerGeneratorTypeName(m_itemContainerGenerator->getStaticMetaclass()->getName().c_str());
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::ListBoxConceptImpl(Domain* domain, string_view name) :
    TBaseClass(domain, name),
    m_itemSelectionRecursionGuard(false),
    m_beginIndex(0),
    m_itemCount(0),
    m_forceUpdate(true)
{
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::~ListBoxConceptImpl()
{
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::initialize(ScrollViewSharedPtr scroll, PresenterSharedPtr presenter)
{
    TBaseClass::initialize();

    m_scrollView = scroll;

    // Create default item generator. Item generator and item container generator will be assigned in OnAttached based on appropriate property values.
    Domain* domain = getThisObject()->getDomain();
    m_defaultItemGenerator = DefaultListBoxItemGenerator<ItemGeneratorClass>::create(domain, "DefaultListBoxItemGenerator");

    // Subscribe to messages.
    getThisObject()->addMessageFilter(ClickManipulator::ClickMessage, bind(&TDerivedClass::onClicked, this, placeholders::_1));

    getThisObject()->addMessageHandler(ScrollViewClass::ScrolledMessage, bind(&TDerivedClass::onScrolled, this, placeholders::_1), m_scrollView.get());
    getThisObject()->addMessageHandler(ScrollViewClass::ScrollStartedMessage, bind(&TDerivedClass::onScrollStarted, this, placeholders::_1), m_scrollView.get());
    getThisObject()->addMessageHandler(ScrollViewClass::ScrollFinishedMessage, bind(&TDerivedClass::onScrollFinished, this, placeholders::_1), m_scrollView.get());
    getThisObject()->addMessageHandler(ScrollViewClass::SnapRequestMessage, bind(&TDerivedClass::onSnapRequested, this, placeholders::_1), m_scrollView.get());

    m_presenter = presenter;

    // Create item generator from ItemGeneratorTypeNameProperty or fallback to default generator.
    setItemGeneratorByProperty();

    // Create item container generator from ItemContainerGeneratorTypeNameProperty property or fallback to default generator.
    setItemContainerGeneratorByProperty();
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::onAttached()
{
    TBaseClass::onAttached();

    // Attach item container generator first because attaching item generator might trigger updating items,
    // and at that point item container generator should be already attached in order to provide correct item containers.
    m_itemContainerGenerator->attach(*getThisObject());
    m_itemGenerator->attach(*getThisObject());

    // Set item selection based on the value of SelectedItemIndex property.
    {
        int selectedItemIndex = getSelectedItemIndex();
        optional<size_t> itemIndexToSelect;

        if (selectedItemIndex >= 0 && selectedItemIndex < static_cast<int>(getItemCount()))
        {
            itemIndexToSelect = optional<size_t>(static_cast<size_t>(selectedItemIndex));
        }

        // During attach select (or un-select) an item based on property value only if it is different from current selection.
        if(itemIndexToSelect != m_selectedItemIndex)
        {
            selectItem(itemIndexToSelect);
        }
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::onDetached()
{
    m_itemContainerGenerator->detach(*getThisObject());
    m_itemGenerator->detach(*getThisObject());

    TBaseClass::onDetached();
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::onClicked(ClickManipulator::ClickMessageArguments& messageArguments)
{
    ItemContainerSharedPtr clickedItemContainer = dynamic_pointer_cast<ItemContainerClass>(messageArguments.getSource());

    if (clickedItemContainer)
    {
        ItemSharedPtr clickedItem = m_itemContainerGenerator->getItem(*clickedItemContainer);
        optional<size_t> itemIndex = getItemIndex(clickedItem);

        if (itemIndex)
        {
            selectItem(*itemIndex);
        }
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::onScrolled(ScrollViewConcept::ScrolledMessageArguments& messageArguments)
{
    Vector2 scrollPosition = messageArguments.getScrollPosition();

    getThisObject()->invalidateMeasure();

    m_presenter->setScroll(scrollPosition);

    messageArguments.setHandled(true);

    // Send another #ScrolledMessage from the list box, since the one from #ScrollView was handled. This allows
    // the user to listen to the scroll messages from the list box.
    {
        ScrolledMessageArguments scrolledMessageArgs;
        scrolledMessageArgs.setScrollPosition(scrollPosition);
        scrolledMessageArgs.setScrollSpeed(messageArguments.getScrollSpeed());
        getThisObject()->dispatchMessage(ScrolledMessage, scrolledMessageArgs);
    }
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::onScrollStarted(ScrollViewConcept::ScrollStartedMessageArguments& messageArguments)
{
    messageArguments.setHandled(true);

    // Send another #ScrollStartedMessage from the list box, to be consistent with sending list box scroll
    // messages as opposed to passing through scroll view messages.
    ScrollStartedMessageArguments scrollStartedMessageArgs;
    scrollStartedMessageArgs.setScrollPosition(messageArguments.getScrollPosition());
    scrollStartedMessageArgs.setScrollSpeed(messageArguments.getScrollSpeed());
    getThisObject()->dispatchMessage(ScrollStartedMessage, scrollStartedMessageArgs);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::onScrollFinished(ScrollViewConcept::ScrollFinishedMessageArguments& messageArguments)
{
    messageArguments.setHandled(true);

    // Send another #ScrollFinishedMessage from the list box, to be consistent with sending list box scroll
    // messages as opposed to passing through scroll view messages.
    ScrollFinishedMessageArguments scrollFinishedMessageArgs;
    scrollFinishedMessageArgs.setScrollPosition(messageArguments.getScrollPosition());
    scrollFinishedMessageArgs.setScrollSpeed(messageArguments.getScrollSpeed());
    getThisObject()->dispatchMessage(ScrollFinishedMessage, scrollFinishedMessageArgs);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::onSnapRequested(ScrollViewConcept::SnapRequestMessageArguments& messageArguments)
{
    Vector2 targetPosition = messageArguments.getSnapPosition();
    Vector2 snapDirection = messageArguments.getSnapDirection();

    Vector2 snapPosition;
    int snappedItem;

    // Get snapping offset.
    m_presenter->snap(targetPosition, snapDirection, true, &snapPosition, &snappedItem);

    // Set new scroll target.
    sendScrollViewScrollTargetMessage(snapPosition);

    if (snappedItem != KZU_UI_LIST_BOX_NO_ITEM)
    {
        sendListBoxTargetChangedMessage(static_cast<size_t>(snappedItem));
    }

    messageArguments.setHandled(true);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::sendScrollViewScrollTargetMessage(const Vector2& scrollTarget)
{
    ScrollViewConcept::SetScrollTargetMessageArguments messageArguments;
    messageArguments.setScrollTarget(scrollTarget);
    m_scrollView->dispatchMessage(ScrollViewConcept::SetScrollTargetMessage, messageArguments);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::sendSetScrollViewScrollMessage(const Vector2& scrollPosition)
{
    ScrollViewConcept::SetScrollMessageArguments messageArguments;
    messageArguments.setScrollPosition(scrollPosition);
    m_scrollView->dispatchMessage(ScrollViewConcept::SetScrollMessage, messageArguments);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::sendListBoxTargetChangedMessage(size_t targetItem)
{
    TargetChangedMessageArguments targetChangedMessageArguments;

    targetChangedMessageArguments.setItem(getItem(targetItem));
    targetChangedMessageArguments.setItemIndex(targetItem);

    getThisObject()->dispatchMessage(TargetChangedMessage, targetChangedMessageArguments);
}

template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
void ListBoxConceptImpl<TBaseClass, TDerivedClass, ListBoxTraits>::onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason)
{
    TBaseClass::onNodePropertyChanged(propertyType, reason);

    if (getThisObject()->isAttached() && !getThisObject()->isDetaching())
    {
        // Set item selection based on the value of SelectedItemIndex property.
        if (propertyType == SelectedItemIndexProperty && !m_itemSelectionRecursionGuard)
        {
            optional<size_t> itemIndexToSelect;

            // If new value assigned to property, set selection only if new index is not out of bounds, otherwise clear selection.
            // If property has been removed, clear selection as well.
            if (reason == PropertyNotificationReasonChanged)
            {
                int selectedItemIndex = getSelectedItemIndex();
                itemIndexToSelect = (selectedItemIndex >= 0 && selectedItemIndex < static_cast<int>(getItemCount()) ? optional<size_t>(static_cast<size_t>(selectedItemIndex)) : nullopt);
            }

            // Apply selection.
            selectItem(itemIndexToSelect);
        }

        if (propertyType == SelectionBehaviorProperty)
        {
            if (m_selectedItemIndex)
            {
                applySelectionBehavior(*m_selectedItemIndex, true);
            }
        }
        // If item container is changed and we already have a item container generator, it needs to be reattached.
        else if (propertyType == ItemContainerTemplateProperty)
        {
            if (m_itemContainerGenerator)
            {
                m_itemContainerGenerator->detach(*getThisObject());
                m_itemContainerGenerator->attach(*getThisObject());
            }

            notifyItemContainerChanged();
        }
        else if ((propertyType == ItemTemplateProperty))
        {
            // Force recreation of all items when the item template changes.
            if (m_itemGenerator)
            {
                m_itemGenerator->detach(*getThisObject());
                m_itemGenerator->attach(*getThisObject());
            }
        }
    }

    if (propertyType == ItemGeneratorTypeNameProperty)
    {
        setItemGeneratorByProperty();
    }
    else if (propertyType == ItemContainerGeneratorTypeNameProperty)
    {
        setItemContainerGeneratorByProperty();
    }
}

}

#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic pop
#endif


#endif
