// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DATA_SOURCE_LIST_ITEM_GENERATOR_IMPL_HPP
#define KZ_DATA_SOURCE_LIST_ITEM_GENERATOR_IMPL_HPP

#include "data_source_list_item_generator.hpp"

#include <kanzi/core.ui/node/node_property_notification_handler.hpp>


namespace kanzi
{

typedef function<void()> PropertyChangedFunction;

class PropertyListener : public NodePropertyNotificationHandler
{
public:
    PropertyListener(Node* node, kanzi::AbstractPropertyType type, PropertyChangedFunction function) :
        NodePropertyNotificationHandler(type, node), m_function(function) {}

        virtual void onPropertyChanged(PropertyNotificationReason /*reason*/)
        {
            m_function();
        }

private:
    PropertyChangedFunction m_function;
};

template <typename TBaseGenerator>
PropertyTypeEditorInfoSharedPtr DataSourceListItemGenerator<TBaseGenerator>::makeEditorInfo()
{
    return PropertyTypeEditorInfoSharedPtr(
        KZ_PROPERTY_TYPE_EDITOR_INFO(
            []() -> PropertyTypeEditorInfo::AttributeDictionary
            {
                PropertyTypeEditorInfo::AttributeDictionary dict;

                dict.displayName = "Data Source List Item Generator";

                return dict;
            }()
        ));
}

template <typename TBaseGenerator>
typename DataSourceListItemGenerator<TBaseGenerator>::DataSourceListItemGeneratorSharedPtr DataSourceListItemGenerator<TBaseGenerator>::create(Domain* domain, string_view /*name*/)
{
    return DataSourceListItemGeneratorSharedPtr(new DataSourceListItemGenerator(domain));
}

template <typename TBaseGenerator>
DataSourceListItemGenerator<TBaseGenerator>::DataSourceListItemGenerator(Domain* domain) :
    TBaseGenerator(domain),
    m_listBoxConcept(),
    m_listBox(),
    m_isAttached(false),
    m_previousCount(0)
{
}

template <typename TBaseGenerator>
DataSourceListItemGenerator<TBaseGenerator>::~DataSourceListItemGenerator()
{
}

template <typename TBaseGenerator>
void DataSourceListItemGenerator<TBaseGenerator>::onDataSourceUpdatedCallback(PropertyObject& object, const ResourceSharedPtr& dataSource, PropertyNotificationReason reason, void* userData)
{
    DataSourceListItemGenerator<TBaseGenerator>* self = static_cast<DataSourceListItemGenerator<TBaseGenerator>*>(userData);

    kzAssert(&object == self->m_listBox);
    KZ_MAYBE_UNUSED(object);

    self->onDataSourceUpdated(dataSource, reason);
}

template <typename TBaseGenerator>
void DataSourceListItemGenerator<TBaseGenerator>::onDataSourceUpdated(const ResourceSharedPtr& /*dataSource*/, PropertyNotificationReason /*reason*/)
{
    kzAssert(m_isAttached);

    DataObjectListSharedPtr itemsSource = updateItemsSource(m_listBox);

    if(itemsSource != m_itemsSource)
    {
        if (m_itemsSource)
        {
            m_itemsSource->removeModifiedNotificationHandler(m_token);
        }

        m_itemsSource = itemsSource;

        if (itemsSource)
        {
            m_token = itemsSource->addModifiedNotificationHandler(bind(&DataSourceListItemGenerator::updateItems, this));
        }
    }

    updateItems();
}

template <typename TBaseGenerator>
void DataSourceListItemGenerator<TBaseGenerator>::attach(typename TBaseGenerator::ListBoxType& node)
{
    kzAssert(!m_isAttached);

    // Store pointer to list box.
    ListBoxConcept* listBoxConcept = dynamic_cast<ListBoxConcept*>(&node);
    kzAssert(listBoxConcept);

    typename TBaseGenerator::ListBoxType* listBox = &node;

    DataObjectListSharedPtr itemsSource = updateItemsSource(listBox);
    PrefabTemplateSharedPtr itemPrefabTemplate = updateItemPrototype(listBox);

    listBox->addPropertyNotificationHandler(DataContext::DataContextProperty, &DataSourceListItemGenerator<TBaseGenerator>::onDataSourceUpdatedCallback, this);
    listBox->addPropertyNotificationHandler(DataContext::ItemsSourceProperty, &DataSourceListItemGenerator<TBaseGenerator>::onDataSourceUpdatedCallback, this);

    // Add listener for data context change.
    DataContext::ModifiedSubscriptionToken token;
    if (itemsSource)
    {
        token = itemsSource->addModifiedNotificationHandler(bind(&DataSourceListItemGenerator::updateItems, this));
    }
    bool isAttached = true;

    using std::swap;
    swap(m_listBoxConcept, listBoxConcept);
    swap(m_listBox, listBox);
    swap(m_itemsSource, itemsSource);
    swap(m_itemPrefabTemplate, itemPrefabTemplate);
    swap(m_token, token);
    swap(m_isAttached, isAttached);

    // Recreate list after everything is in place.
    updateItems();
}

template <typename TBaseGenerator>
DataObjectListSharedPtr DataSourceListItemGenerator<TBaseGenerator>::updateItemsSource(typename TBaseGenerator::ListBoxType* listBox)
{
    DataObjectListSharedPtr result;

    ResourceSharedPtr propertyValue = listBox->getProperty(DataContext::ItemsSourceProperty);

    DataObjectSharedPtr itemsSource = dynamic_pointer_cast<DataObject>(propertyValue);
    if (itemsSource)
    {
        result = dynamic_pointer_cast<DataObjectList>(itemsSource);
        if (!result)
        {
            kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Items source is not a list data object."));
        }
    }

    return result;
}

template <typename TBaseGenerator>
PrefabTemplateSharedPtr DataSourceListItemGenerator<TBaseGenerator>::updateItemPrototype(typename TBaseGenerator::ListBoxType* listBox)
{
    PrefabTemplateSharedPtr itemPrefabTemplate = dynamic_pointer_cast<PrefabTemplate>(listBox->getProperty(ListBoxConcept::ItemTemplateProperty));

    return itemPrefabTemplate;
}

template <typename TBaseGenerator>
typename TBaseGenerator::ItemSharedPtr DataSourceListItemGenerator<TBaseGenerator>::acquireItem(ResourceSharedPtr dataObjectResource)
{
    typename TBaseGenerator::ItemSharedPtr itemObjectNode;

    // Re-use previously recycled item if any.
    if (!m_recycledItems.empty())
    {
        itemObjectNode = m_recycledItems.top();
        m_recycledItems.pop();
    }

    // Create new item from item template if no recycled items left.
    if(!itemObjectNode && m_itemPrefabTemplate)
    {
        PrefabTemplateNodeSharedPtr rootNode = kzuPrefabTemplateGetRoot(&(*m_itemPrefabTemplate));
        itemObjectNode = m_itemPrefabTemplate->instantiate<typename TBaseGenerator::Item>(rootNode->name);
    }

    // Set data object to new item.
    if (itemObjectNode)
    {
        itemObjectNode->setProperty(DataContext::DataContextProperty, dataObjectResource);
        itemObjectNode->setPropertyFlag(DataContext::DataContextProperty, KZU_PROPERTY_MANAGER_FLAG_KEEP_DURING_PATCHING);
    }

    return itemObjectNode;
}

template <typename TBaseGenerator>
ResourceSharedPtr DataSourceListItemGenerator<TBaseGenerator>::getDataContext(Node& node)
{
    // See if there is data object assigned as a data context resource.
    return node.getProperty(DataContext::DataContextProperty);
}

template <typename TBaseGenerator>
void DataSourceListItemGenerator<TBaseGenerator>::freeRecycledItems()
{
    while (!m_recycledItems.empty())
    {
        m_recycledItems.pop();
    }
}

template <typename TBaseGenerator>
void DataSourceListItemGenerator<TBaseGenerator>::updateItems()
{
    if (!m_itemsSource)
    {
        return;
    }

    size_t newCount = getCount();
    if (m_previousCount != newCount)
    {
        m_previousCount = newCount;
        m_listBoxConcept->notifyItemCountChanged();
    }

    for(typename ItemMap::const_iterator it = cbegin(m_items), endIt = cend(m_items); it != endIt; ++it)
    {
        // Return value is used only comparison, so null is a accepted value.
        DataObjectSharedPtr listDataObject = dynamic_pointer_cast<DataObject>(getDataContext(*(it->second.get())));
        // Acquire new data source
        DataObjectSharedPtr sourceDataObject = m_itemsSource->acquireItem(it->first);
        // Release the previous reference. We just want the current data source object pointer without affecting the reference count.
        m_itemsSource->releaseItem(it->first);

        if (listDataObject != sourceDataObject)
        {
            it->second->setProperty(DataContext::DataContextProperty, ResourceSharedPtr(sourceDataObject));
            it->second->setPropertyFlag(DataContext::DataContextProperty, KZU_PROPERTY_MANAGER_FLAG_KEEP_DURING_PATCHING);
            m_listBoxConcept->notifyItemReplaced(it->first);
        }
    }
}

template <typename TBaseGenerator>
void DataSourceListItemGenerator<TBaseGenerator>::detach(typename TBaseGenerator::ListBoxType& listBox)
{
    kzAssert(m_isAttached);
    kzAssert(m_listBox == &listBox);
    KZ_MAYBE_UNUSED(listBox);

    m_listBox->removePropertyNotificationHandler(DataContext::DataContextProperty, &DataSourceListItemGenerator<TBaseGenerator>::onDataSourceUpdatedCallback, this);
    m_listBox->removePropertyNotificationHandler(DataContext::ItemsSourceProperty, &DataSourceListItemGenerator<TBaseGenerator>::onDataSourceUpdatedCallback, this);

    // Tell listbox to release all items. Iterate in reverse order, as removing one index modifies greater indices.
    for(typename ItemMap::const_reverse_iterator it = crbegin(m_items), endIt = crend(m_items); it != endIt; ++it)
    {
        m_listBoxConcept->notifyItemRemoved(it->first);
    }

    m_items.clear();
    if (m_itemsSource)
    {
        m_itemsSource->removeModifiedNotificationHandler(m_token);
    }
    m_itemsSource.reset();
    m_token.reset();
    m_itemPrefabTemplate.reset();
    freeRecycledItems();
    m_isAttached = false;
    m_previousCount = 0;
}

template <typename TBaseGenerator>
typename TBaseGenerator::ItemSharedPtr DataSourceListItemGenerator<TBaseGenerator>::acquireItem(size_t index)
{
    // TODO: this check should not be needed, but for some reason same item is acquired infinite times.
    typename ItemMap::iterator it = m_items.find(index);
    if (it != end(m_items))
    {
        return it->second;
    }

    if(!m_itemsSource || !m_itemPrefabTemplate)
    {
        return typename TBaseGenerator::ItemSharedPtr();
    }

    DataObjectSharedPtr dataObject = m_itemsSource->acquireItem(index);
    if (!dataObject)
    {
        return typename TBaseGenerator::ItemSharedPtr();
    }

    typename TBaseGenerator::ItemSharedPtr item = acquireItem(ResourceSharedPtr(dataObject));

    if (item)
    {
        m_items.insert(pair<const size_t, typename TBaseGenerator::ItemSharedPtr>(index, item));
    }

    return item;
}

template <typename TBaseGenerator>
void DataSourceListItemGenerator<TBaseGenerator>::releaseItem(typename TBaseGenerator::ItemSharedPtr object)
{
    optional<size_t> index = getItemIndex(object);
    if (!index)
    {
        return;
    }
    if (m_itemsSource)
    {
        m_itemsSource->releaseItem(*index);
    }
    m_items.erase(*index);
    if (m_recycledItems.size() < m_recycledItemStackMaximumSize)
    {
        m_recycledItems.push(object);
    }
}

template <typename TBaseGenerator>
optional<size_t> DataSourceListItemGenerator<TBaseGenerator>::getItemIndex(typename TBaseGenerator::ItemSharedPtr object)
{
    for(typename ItemMap::const_iterator it = cbegin(m_items), endIt = cend(m_items); it != endIt; ++it)
    {
        if (it->second == object)
        {
            return it->first;
        }
    }
    return nullopt;
}

template <typename TBaseGenerator>
typename TBaseGenerator::VectorType DataSourceListItemGenerator<TBaseGenerator>::getItemSize(size_t /*index*/)
{
    // Instead of trying to measure the size of the object here, set the size to 0 and prevent objects from overlapping by specifying the spacing property for the list box.
    // This works fine as long as the objects have roughly the same size.
    return typename TBaseGenerator::VectorType();
}

template <typename TBaseGenerator>
size_t DataSourceListItemGenerator<TBaseGenerator>::getCount()
{
    // Return 0, if prefab is missing, because otherwise acquireItem would return null and list box can't handle that.
    if (m_itemsSource && m_itemPrefabTemplate)
    {
        return m_itemsSource->itemCount();
    }
    return 0;
}

}
#endif
