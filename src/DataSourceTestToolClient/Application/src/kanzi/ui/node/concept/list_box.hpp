// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LIST_BOX_HPP
#define KZ_LIST_BOX_HPP

#include <kanzi/ui/ui_api.hpp>
#include <kanzi/ui/node/concept/list_box/default_list_box_item_generator.hpp>
#include <kanzi/ui/node/concept/list_box/list_box_item_generator.hpp>
#include <kanzi/ui/node/concept/scroll_view.hpp>
#include <kanzi/ui/node/list_box_item_container.hpp>

#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/content/content_item_collection.hpp>
#include <kanzi/core.ui/input/keyboard.hpp>

#include <kanzi/core/cpp/unordered_map.hpp>
#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/cpp/memory.hpp>


/** List box selection index represents no selection. */
#define KZU_UI_LIST_BOX_NO_ITEM (-1)

namespace kanzi
{

class Domain;
class PrefabTemplate;
typedef shared_ptr<PrefabTemplate> PrefabTemplateSharedPtr;


/// Properties and messages for list boxes.
///
/// \see For general documentation about list boxes, see ListBoxConceptImpl.
class KANZI_UI_API ListBoxConcept : public ContentItemCollectionModel
{
public:
    /// Behaviors for list box when an item in the list box is selected.
    enum SelectionBehavior
    {
        SelectionBehaviorNone, ///< Does not change scroll position when selection changes.
        // TODO: rename bring to cursor
        SelectionBehaviorBringToCenter ///< Centers the item when selected.
    };

    /// Virtual functions for notifying item changes to list
    virtual void notifyItemAdded(size_t index) = 0;
    virtual void notifyItemRemoved(size_t index) = 0;
    virtual void notifyItemReplaced(size_t index) = 0;
    virtual void notifyItemCountChanged() = 0;

    /// \name Properties
    /// \{
#include "list_box_properties.h"
    /// \}

    /// Represents message arguments of ItemSelected message.
    class KANZI_UI_API ItemSelectedMessageArguments : public MessageArguments
    {
    public:
        /// \name Properties
        /// \{

        /// SelectedItemIndex property.
        /// The default value is -1.
        /// \see setSelectedItemIndex(), getSelectedItemIndex()
        static PropertyType<int> SelectedItemIndexProperty;

        /// PreviousSelectedItemIndex property.
        /// The default value is -1.
        /// \see setPreviousSelectedItemIndex(), getPreviousSelectedItemIndex()
        static PropertyType<int> PreviousSelectedItemIndexProperty;

        /// \}

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ItemSelectedMessageArguments, MessageArguments, "Kanzi.ListBoxConcept.ItemSelectedMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(SelectedItemIndexProperty)
            KZ_METACLASS_PROPERTY_TYPE(PreviousSelectedItemIndexProperty)
        KZ_METACLASS_END()

        optional<size_t> getSelectedItemIndex() const
        {
            int value = getArgument(SelectedItemIndexProperty);
            return (value != KZU_UI_LIST_BOX_NO_ITEM) ? optional<size_t>(static_cast<size_t>(value)) : nullopt;
        }
        void setSelectedItemIndex(optional<size_t> value)
        {
            int propertyValue = value ? static_cast<int>(*value) : KZU_UI_LIST_BOX_NO_ITEM;
            setArgument(SelectedItemIndexProperty, propertyValue);
        }

        optional<size_t> getPreviouslySelectedItemIndex() const
        {
            int value = getArgument(PreviousSelectedItemIndexProperty);
            return (value != KZU_UI_LIST_BOX_NO_ITEM) ? optional<size_t>(static_cast<size_t>(value)) : nullopt;
        }
        void setPreviouslySelectedItemIndex(optional<size_t> value)
        {
            int propertyValue = KZU_UI_LIST_BOX_NO_ITEM;
            if (value)
            {
                propertyValue = static_cast<int>(*value);
            }
            setArgument(PreviousSelectedItemIndexProperty, propertyValue);
        }


        static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
    };

    /// Represents base class for item-related message arguments.
    class KANZI_UI_API ItemMessageArguments : public MessageArguments
    {
    public:
        /// \name Properties
        /// \{

        /// ItemIndex property.
        /// The default value is -1.
        /// \see setItemIndex(), getItemIndex()
        static PropertyType<int> ItemIndexProperty;

        /// Item property.
        /// The default value is KZ_NULL.
        /// \see setItem(), getItem()
        static PropertyType<void*> ItemProperty;
        
        /// \}

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ItemMessageArguments, MessageArguments, "Kanzi.ListBoxConcept.ItemMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(ItemIndexProperty)
            KZ_METACLASS_PROPERTY_TYPE(ItemProperty)
        KZ_METACLASS_END()

        optional<size_t> getItemIndex() const
        {
            int value = getArgument(ItemIndexProperty);
            return (value != KZU_UI_LIST_BOX_NO_ITEM) ? optional<size_t>(static_cast<size_t>(value)) : nullopt;
        }
        void setItemIndex(size_t value)
        {
            setArgument(ItemIndexProperty, static_cast<int>(value));
        }

        NodeSharedPtr getItem() const
        {
            // TODO: implement it properly.
            Node* node = static_cast<Node*>(getArgument(ItemProperty));
            return node->shared_from_this();
        }
        void setItem(NodeSharedPtr value)
        {
            // TODO: implement it properly.
            Node& node = *value;
            setArgument(ItemProperty, static_cast<void*>(&node));
        }

        static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
    };

    /// Base class for scroll-related message arguments.
    class KANZI_UI_API ScrollMessageArguments : public MessageArguments
    {
    public:

        /// \name Properties
        /// \{

        /// ScrollPosition property.
        static PropertyType<Vector2> ScrollPositionProperty;
        /// Gets #ScrollPositionProperty.
        /// \return Argument value.
        Vector2 getScrollPosition() const
        {
            return getArgument(ScrollPositionProperty);
        }
        /// Sets #ScrollPositionProperty.
        /// \param value New Argument value.
        void setScrollPosition(Vector2 value)
        {
            setArgument(ScrollPositionProperty, value);
        }

        /// ScrollSpeed property.
        static PropertyType<Vector2> ScrollSpeedProperty;
        /// Gets #ScrollSpeedProperty.
        /// \return Argument value.
        Vector2 getScrollSpeed() const
        {
            return getArgument(ScrollSpeedProperty);
        }
        /// Sets #ScrollSpeedProperty.
        /// \param value New Argument value.
        void setScrollSpeed(Vector2 value)
        {
            setArgument(ScrollSpeedProperty, value);
        }

        /// \}

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ScrollMessageArguments, MessageArguments, "Kanzi.ListBoxConcept.ScrollMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(ScrollPositionProperty)
            KZ_METACLASS_PROPERTY_TYPE(ScrollSpeedProperty)
        KZ_METACLASS_END()
    };

    /// Scrolled message, sent when list box is scrolling.
    class KANZI_UI_API ScrolledMessageArguments : public ScrollMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ScrolledMessageArguments, ScrollMessageArguments, "Kanzi.ListBoxConcept.ScrolledMessageArguments")
        KZ_METACLASS_END()

        static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
    };

    /// ScrollStarted message, sent when list box scroll starts.
    class KANZI_UI_API ScrollStartedMessageArguments : public ScrollMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ScrollStartedMessageArguments, ScrollMessageArguments, "Kanzi.ListBoxConcept.ScrollStartedMessageArguments")
        KZ_METACLASS_END()

        static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
    };

    /// ScrollFinished message, sent when list box scroll ends.
    class KANZI_UI_API ScrollFinishedMessageArguments : public ScrollMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ScrollFinishedMessageArguments, ScrollMessageArguments, "Kanzi.ListBoxConcept.ScrollFinishedMessageArguments")
        KZ_METACLASS_END()

        static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
    };

    /// Represents message arguments of ItemVisible message.
    class KANZI_UI_API ItemVisibleMessageArguments : public ItemMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ItemVisibleMessageArguments, ItemMessageArguments, "Kanzi.ListBoxConcept.ItemVisibleMessageArguments")
        KZ_METACLASS_END()
    };

    /// Represents message arguments of ItemHidden message.
    class KANZI_UI_API ItemHiddenMessageArguments : public ItemMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ItemHiddenMessageArguments, ItemMessageArguments, "Kanzi.ListBoxConcept.ItemHiddenMessageArguments")
        KZ_METACLASS_END()
    };

    /// Represents message arguments of TargetChanged message.
    class KANZI_UI_API TargetChangedMessageArguments : public ItemMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(TargetChangedMessageArguments, ItemMessageArguments, "Kanzi.ListBoxConcept.TargetChangedMessageArguments")
        KZ_METACLASS_END()
    };

    /// ItemSelected message type.
    static MessageType<ItemSelectedMessageArguments> ItemSelectedMessage;
    /// ItemVisible message type.
    static MessageType<ItemVisibleMessageArguments> ItemVisibleMessage;
    /// ItemHidden message type.
    static MessageType<ItemHiddenMessageArguments> ItemHiddenMessage;
    /// TargetChanged message type.
    static MessageType<TargetChangedMessageArguments> TargetChangedMessage;
    /// Scrolled message type.
    static MessageType<ScrolledMessageArguments> ScrolledMessage;
    /// Scroll Started message type.
    static MessageType<ScrollStartedMessageArguments> ScrollStartedMessage;
    /// Scroll Finished message type.
    static MessageType<ScrollFinishedMessageArguments> ScrollFinishedMessage;

    KZ_MIXIN_METACLASS_BEGIN(ListBoxConcept, "Kanzi.ListBoxConcept")
        KZ_METACLASS_PROPERTY_TYPE(KeepAliveItemCountProperty)
        KZ_METACLASS_PROPERTY_TYPE(SelectedItemIndexProperty)
        KZ_METACLASS_PROPERTY_TYPE(SelectionBehaviorProperty)
        KZ_METACLASS_PROPERTY_TYPE(ItemGeneratorTypeNameProperty)
        KZ_METACLASS_PROPERTY_TYPE(ItemContainerGeneratorTypeNameProperty)
        KZ_METACLASS_PROPERTY_TYPE(ItemTemplateProperty)
        KZ_METACLASS_PROPERTY_TYPE(ItemContainerTemplateProperty)

        KZ_METACLASS_MESSAGE_TYPE(ItemSelectedMessage)
        KZ_METACLASS_MESSAGE_TYPE(ItemVisibleMessage)
        KZ_METACLASS_MESSAGE_TYPE(ItemHiddenMessage)
        KZ_METACLASS_MESSAGE_TYPE(TargetChangedMessage)
        KZ_METACLASS_MESSAGE_TYPE(ScrolledMessage)
        KZ_METACLASS_MESSAGE_TYPE(ScrollStartedMessage)
        KZ_METACLASS_MESSAGE_TYPE(ScrollFinishedMessage)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
};

#ifdef KANZI_FEATURE_3D
inline void doListBoxArrange(Node3D& node)
{
    node.centeredArrange(node.getActualSize());
}
#endif

inline void doListBoxArrange(Node2D& node)
{
    node.Node2D::arrangeOverride(node.getActualSize());
}


/// ListBoxConceptImpl provides common base implementation for different list boxes.
///
/// List box is a layout node that contain other nodes as items. The list box provides
/// an invisible hit testable area that listens to input and reacts when the user
/// pans the area. The list box then scrolls the items so that new items become
/// visible and old items disappear. How this actually happens depends on the specific
/// list boxes.
///
/// The list box gets its items from an <em>item generator</em>. By default the list box
/// uses the DefaultListBoxItemGenerator that simply stores the items that have been
/// added to it. It is possible to create dynamic content for the list box by replacing
/// the item generator with a custom implementation.
///
/// The list box wraps its items in container nodes that are created by an <em>item container
/// generator</em>. The default item generator creates invisible nodes that don't do anything.
template <typename TBaseClass, typename TDerivedClass, typename ListBoxTraits>
class KANZI_UI_TEMPLATE_API ListBoxConceptImpl : public TBaseClass, public ListBoxConcept
{
    TDerivedClass* getThisObject();

    const TDerivedClass* getThisObject() const;

public:
    KZ_TEMPLATE_METACLASS_BEGIN(ListBoxConceptImpl, TBaseClass)
        KZ_METACLASS_MIXIN(ListBoxConcept)
    KZ_METACLASS_END()

    typedef typename ListBoxTraits::TScrollViewClass ScrollViewClass;
    typedef typename ListBoxTraits::TItemClass ItemClass;
    typedef typename ListBoxTraits::TItemContainerClass ItemContainerClass;
    typedef typename ListBoxTraits::TPresenterClass PresenterClass;
    typedef typename ListBoxTraits::TItemGeneratorClass ItemGeneratorClass;
    typedef typename ListBoxTraits::TItemContainerGeneratorClass ItemContainerGeneratorClass;

    typedef typename TBaseClass::LayoutVectorType LayoutVectorType;
    typedef shared_ptr<ScrollViewClass> ScrollViewSharedPtr;
    typedef shared_ptr<ItemClass> ItemSharedPtr;
    typedef shared_ptr<ItemContainerClass> ItemContainerSharedPtr;
    typedef shared_ptr<DefaultListBoxItemGenerator<ItemGeneratorClass> > DefaultItemGeneratorSharedPtr;
    typedef shared_ptr<ItemGeneratorClass> ItemGeneratorSharedPtr;
    typedef shared_ptr<ItemContainerGeneratorClass> ItemContainerGeneratorSharedPtr;
    typedef shared_ptr<PresenterClass> PresenterSharedPtr;

    virtual bool addContentItem(NodeSharedPtr abstractItem) KZ_OVERRIDE;
    virtual bool removeContentItem(NodeSharedPtr abstractItem) KZ_OVERRIDE;
    virtual void removeAllContentItems() KZ_OVERRIDE;
    virtual size_t getContentItemCount() KZ_OVERRIDE;
    virtual NodeSharedPtr getContentItem(size_t index) KZ_OVERRIDE;

    PresenterSharedPtr getPresenter() const
    {
        return m_presenter;
    }

    /// Returns the total item count of the list box. Includes all virtual items.
    size_t getItemCount();

    /// Returns the range of items being alive in the buffer (based on the KeepItemsAlive property).
    /// Returned pair contains the index of the first and the item count. If the virtual range does not exist, returns empty.
    optional<pair<size_t, size_t> > getAliveRange();

    /// Returns true if the list box has no items.
    bool isEmpty();

    /// Returns size of the item at the given index or unbounded layout value
    /// if size could not be determined without acquiring the item first.
    LayoutVectorType getItemSize(size_t index);

    /// Returns index of the given item. If the item does not exist currently, returns empty.
    optional<size_t> getItemIndex(ItemSharedPtr item);

    /// Gets the item at the given index in a list box.
    ItemSharedPtr getItem(size_t index);

    /// Inserts an item at the given index in a list box when using the default object generator.
    void insertItem(size_t index, ItemSharedPtr item);

    /// Removes the item at the given index from a list box when using the default object generator.
    void removeItem(size_t index);

    /// Replaces the item at the given index from a list box when using the default object generator.
    void replaceItem(size_t index, ItemSharedPtr item);

    /// Adds an item at the end of a list box when using the default object generator.
    void addItem(ItemSharedPtr item);

    /// Removes the last item from a list box when using the default object generator.
    void removeLastItem();

    /// Removes all items from a list box when using the default object generator.
    void removeAllItems();


    /// Requests the list box to select the item in the given index.
    /// \param itemIndex The index of the selected item. Set to empty to clear the selection.
    void selectItem(optional<size_t> itemIndex);

    virtual void notifyItemAdded(size_t index) KZ_OVERRIDE;
    virtual void notifyItemRemoved(size_t index) KZ_OVERRIDE;
    virtual void notifyItemReplaced(size_t index) KZ_OVERRIDE;
    virtual void notifyItemCountChanged() KZ_OVERRIDE;
    void notifyItemContainerChanged();

    static Vector2 doMeasure(Node2D& node);
#ifdef KANZI_FEATURE_3D
    static Vector3 doMeasure(Node3D& node);
#endif
    virtual LayoutVectorType measureOverride(LayoutVectorType availableSize) KZ_OVERRIDE;

    virtual void arrangeOverride(LayoutVectorType actualSize) KZ_OVERRIDE;

    /// Requests items from the item generator.
    /// Called by the presenter when new items are displayed or old items hidden.
    void updateVisibleRangeQuiet(size_t beginIndex, size_t itemCount);
    /// Requests items from the item generator.
    /// Called by the presenter when new items are displayed or old items hidden. Sends messages about hidden and revealed items.
    void updateVisibleRange(size_t beginIndex, size_t itemCount);
    void updateVisibleRange(size_t beginIndex, size_t itemCount, bool sendMessages);

    /// Returns scroll view used for scrolling list box.
    /// Use it to access properties of the scroll view or modify the scrolling behaviour.
    /// \return Returns scroll view.
    ScrollViewSharedPtr getScrollView() const;

    /// Requests the list box to focus on the item in the given index.
    /// \param itemIndex The index of the focused item.
    /// \param smooth If set to true, the list box scroll to the target item smoothly. If set to false, the list box jumps to the target item immediately.
    void bringItemCenter(size_t itemIndex, bool smooth);

    /// Gets the value of #KeepAliveItemCount.
    /// \see getKeepAliveItemCount()
    int getKeepAliveItemCount() const;
    /// Sets the value of #KeepAliveItemCount.
    /// \see setKeepAliveItemCount()
    void setKeepAliveItemCount(int value);

    /// Gets the value of #SelectedItemIndex.
    /// \see setSelectedItemIndex()
    int getSelectedItemIndex() const;
    /// Sets the value of #SelectedItemIndex.
    /// \see getSelectedItemIndex()
    void setSelectedItemIndex(int value);

    /// Gets the value of #SelectionBehavior.
    /// \see setSelectionBehavior()
    SelectionBehavior getSelectionBehavior() const;
    /// Sets the value of #SelectionBehavior.
    /// \see getSelectionBehavior()
    void setSelectionBehavior(SelectionBehavior value);

    /// Gets the value of #ObjectGeneratorTypeName.
    /// \see getObjectGeneratorTypeName()
    string getItemGeneratorTypeName() const;
    /// Sets the value of #ObjectGeneratorTypeName.
    /// \see setObjectGeneratorTypeName()
    void setItemGeneratorTypeName(string_view value);

    /// Gets the value of #ItemContainerGeneratorTypeName.
    /// \see getItemContainerGeneratorTypeName()
    string getItemContainerGeneratorTypeName() const;
    /// Sets the value of #ItemContainerGeneratorTypeName.
    /// \see setItemContainerGeneratorTypeName()
    void setItemContainerGeneratorTypeName(string_view value);

    // Gets the value of #ItemPrototypeTypeName.
    // \see getItemPrototypeTypeName()
    //    ResourceID getItemPrototypeTypeName() const { return getThisObject()->getProperty(ItemPrototypeTypeNameProperty); }
    // Sets the value of #ItemPrototypeTypeName.
    // \see setItemPrototypeTypeName()
    //    void setItemPrototypeTypeName(ResourceID value) { getThisObject()->setProperty(ItemPrototypeTypeNameProperty, value); }

    /// Gets the value of #ItemTemplate.
    /// \see getItemTemplate()
    PrefabTemplateSharedPtr getItemTemplate() const;
    /// Sets the value of #ItemTemplate.
    /// \see setItemTemplate()
    void setItemTemplate(PrefabTemplateSharedPtr value);

    /// Gets the value of #ItemContainerTemplate.
    /// \see getItemContainerTemplate()
    PrefabTemplateSharedPtr getItemContainerTemplate() const;
    /// Sets the value of #ItemContainerTemplate.
    /// \see setItemContainerTemplate()
    void setItemContainerTemplate(PrefabTemplateSharedPtr value);

    /// Sets the list box item generator.
    /// \param itemGenerator New item generator.
    void setItemGenerator(ItemGeneratorSharedPtr itemGenerator);

    /// Sets the list box item container generator.
    /// \param itemContainerGenerator New item container generator.
    void setItemContainerGenerator(ItemContainerGeneratorSharedPtr itemContainerGenerator);

protected:
    explicit ListBoxConceptImpl(Domain* domain, string_view name);
    ~ListBoxConceptImpl();

    void initialize(ScrollViewSharedPtr scroll, PresenterSharedPtr pres);

    void onClicked(ClickManipulator::ClickMessageArguments& messageArguments);
    void onScrolled(ScrollViewConcept::ScrolledMessageArguments& messageArguments);
    void onScrollStarted(ScrollViewConcept::ScrollStartedMessageArguments& messageArguments);
    void onScrollFinished(ScrollViewConcept::ScrollFinishedMessageArguments& messageArguments);
    void onSnapRequested(ScrollViewConcept::SnapRequestMessageArguments& messageArguments);

    /// Sends new scroll target to scroll view.
    void sendScrollViewScrollTargetMessage(const Vector2& scrollTarget);

    /// Sends new current scroll position to scroll view.
    void sendSetScrollViewScrollMessage(const Vector2& scrollPosition);

    /// Sends new current scroll position to scroll view.
    void sendListBoxTargetChangedMessage(size_t targetItem);

    /// Node::onAttached() implementation.
    virtual void onAttached() KZ_OVERRIDE;

    /// Node::onDetached() implementation.
    virtual void onDetached() KZ_OVERRIDE;

    /// Node::onNodePropertyChanged() implementation.
    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// Applies selection behavior to specified item.
    /// \param itemIndex index of the item to which selection behavior should be applied.
    /// \param smooth indicates if selection should be immediate or smooth.
    void applySelectionBehavior(size_t itemIndex, bool smooth);

    /// Assigns list box item generator to list box.
    void assignItemGenerator(ItemGeneratorSharedPtr itemGenerator);

    /// Creates and assigns item generator by ItemGeneratorTypeName property value.
    void setItemGeneratorByProperty();

    /// Assigns list box item container generator to list box.
    void assignItemContainerGenerator(ItemContainerGeneratorSharedPtr itemContainerGenerator);

    /// Creates and assigns item container generator by ItemGeneratorTypeName property value.
    void setItemContainerGeneratorByProperty();

    /// Replaces item and item container generators with new objects. Updates items and layout accordingly.
    void updateGenerators(ItemGeneratorSharedPtr itemGenerator, ItemContainerGeneratorSharedPtr itemContainerGenerator);

    /// Updates SelectedItemIndex property after selected item index changes internally by list box.
    void synchronizeSelectedItemIndexProperty();

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        // TODO provide info
        return PropertyTypeEditorInfoSharedPtr();
    }

private:
    /// Data for items controlled by list box.
    struct ItemInfo
    {
        ItemInfo() :
            index(0)
        {
        }

        ItemInfo(ItemContainerSharedPtr newItemContainer, ItemSharedPtr newItem, size_t newIndex) :
            itemContainer(newItemContainer),
            item(newItem),
            index(newIndex)
        {
        }

        ItemContainerSharedPtr itemContainer; ///< List box item that contains the item object.
        ItemSharedPtr item;                   ///< Reference to the object wrapped into the list box item.
        size_t index;                         ///< Index of object in the object generator.
    };

    typedef shared_ptr<ItemInfo> ItemInfoSharedPtr;

    typedef unordered_map<size_t, ItemInfoSharedPtr> IndexMap;
    typedef unordered_map<ItemContainerSharedPtr, ItemInfoSharedPtr> ItemContainerMap;
    typedef unordered_map<ItemSharedPtr, ItemInfoSharedPtr> ItemMap;

    ScrollViewSharedPtr m_scrollView; ///< Controls scrolling of list box.
    PresenterSharedPtr m_presenter;   ///< Controls presentation of objects.

    optional<size_t> m_selectedItemIndex; ///< Current selection.
    bool m_itemSelectionRecursionGuard;   ///< Flag preventing recursion when selecting list box item.

    IndexMap m_itemIndexMap;             ///< Item infos by item indices.
    ItemContainerMap m_itemContainerMap; ///< Item infos by item pointers.
    ItemMap m_itemMap;                   ///< Item infos by objects.
    ItemMap m_itemMapBuffer;             ///< Double buffer for itemInfosByObjects.
    size_t m_beginIndex;                 ///< Index of the first item.
    size_t m_itemCount;                  ///< Number of items.

    DefaultItemGeneratorSharedPtr m_defaultItemGenerator;     ///< Default item generator with special handling.
    ItemGeneratorSharedPtr m_itemGenerator;                   ///< Generates and manages items for list box.
    ItemContainerGeneratorSharedPtr m_itemContainerGenerator; ///< Generates and manages list box item containers for list box.

    bool m_forceUpdate; ///< Forces re-update even with previous range when items have been added, removed, or replaced.
};
}

#endif
