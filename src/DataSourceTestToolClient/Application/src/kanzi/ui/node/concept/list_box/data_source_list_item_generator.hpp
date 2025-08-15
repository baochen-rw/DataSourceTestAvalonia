// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DATA_SOURCE_LIST_ITEM_GENERATOR_HPP
#define KZ_DATA_SOURCE_LIST_ITEM_GENERATOR_HPP

#include <kanzi/ui/ui_api.hpp>
#include <kanzi/ui/node/concept/list_box/list_box_item_generator.hpp>
#include <kanzi/ui/node/concept/list_box.hpp>

#include <kanzi/core.ui/template/prefab.hpp>
#include <kanzi/core.ui/data/data_object_list.hpp>
#include <kanzi/core.ui/data/data_context.hpp>

#include <kanzi/core/cpp/map.hpp>

#include <stack>


namespace kanzi
{

class PropertyListener;

// Represents data source list box item generator.
template <typename TBaseGenerator>
class KANZI_UI_TEMPLATE_API DataSourceListItemGenerator : public TBaseGenerator
{
public:

    typedef shared_ptr<DataSourceListItemGenerator<TBaseGenerator> > DataSourceListItemGeneratorSharedPtr;

    KZ_TEMPLATE_METACLASS_BEGIN(DataSourceListItemGenerator, TBaseGenerator)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    static DataSourceListItemGeneratorSharedPtr create(Domain* domain, string_view name);

    // Attaches the Object Generator.
    virtual void attach(typename TBaseGenerator::ListBoxType& node) KZ_OVERRIDE;

    // Detaches the Object Generator.
    virtual void detach(typename TBaseGenerator::ListBoxType& node) KZ_OVERRIDE;

    // Gets an object that should be displayed at the given index.
    // If the object has already been created and not freed afterwards, returns the object from cache.
    virtual typename TBaseGenerator::ItemSharedPtr acquireItem(size_t index) KZ_OVERRIDE;

    // Frees an object that has been returned from getObject.
    virtual void releaseItem(typename TBaseGenerator::ItemSharedPtr object) KZ_OVERRIDE;

    // Gets index of an object that has been returned from getObject, or KZU_UI_LIST_BOX_NO_ITEM if
    // the object does not exist.
    virtual optional<size_t> getItemIndex(typename TBaseGenerator::ItemSharedPtr object) KZ_OVERRIDE;

    // Gets exact size of the object that should be displayed at the given index.
    // This size will be used unless the list box is provided an object prototype.
    // Caching the sizes may be a good idea.
    virtual typename TBaseGenerator::VectorType getItemSize(size_t index) KZ_OVERRIDE;

    // Gets the number of objects known by the object generator.
    // Last index can be calculated as 'count' - 1.
    virtual size_t getCount() KZ_OVERRIDE;

    virtual ~DataSourceListItemGenerator();

protected:
    // Constructor.
    explicit DataSourceListItemGenerator(Domain* domain);

    DataObjectListSharedPtr updateItemsSource(typename TBaseGenerator::ListBoxType* listBox);
    PrefabTemplateSharedPtr updateItemPrototype(typename TBaseGenerator::ListBoxType* listBox);

    // Creates item for data object or reuses previously recycled item.
    typename TBaseGenerator::ItemSharedPtr acquireItem(ResourceSharedPtr dataObjectResource);

    static ResourceSharedPtr getDataContext(Node& node);

    // Frees all recycled items. Next item acquisition will create an item from scratch.
    void freeRecycledItems();

    static void onDataSourceUpdatedCallback(PropertyObject& object, const ResourceSharedPtr& dataSource, PropertyNotificationReason reason, void* userData);

    void onDataSourceUpdated(const ResourceSharedPtr& dataSource, PropertyNotificationReason reason);

private:

    typedef map<size_t, typename TBaseGenerator::ItemSharedPtr> ItemMap;
    ItemMap m_items;

    static const size_t m_recycledItemStackMaximumSize = 50;
    typedef std::stack<typename TBaseGenerator::ItemSharedPtr> ItemStack;
    ItemStack m_recycledItems;

    // List box where item generator attached to.
    ListBoxConcept* m_listBoxConcept;
    typename TBaseGenerator::ListBoxType* m_listBox;

    // Prefab template for instantiating list box item's scene objects.
    PrefabTemplateSharedPtr m_itemPrefabTemplate;

    DataObjectListSharedPtr m_itemsSource;

    DataContext::ModifiedSubscriptionToken m_token;
    bool m_isAttached;
    size_t m_previousCount;

    void updateItems();
};

}
#endif
