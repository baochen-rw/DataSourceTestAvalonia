// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LIST_BOX_TRAJECTORY_PRESENTER_HPP
#define KZ_LIST_BOX_TRAJECTORY_PRESENTER_HPP

#include <kanzi/core/legacy/legacy_conversions.hpp>
#include <kanzi/ui/node/scroll_view3d.hpp>
#include <kanzi/ui/node/concept/list_box.hpp>
#include <kanzi/ui/node/concept/list_box/kzu_virtual_item_list.h>
#include <kanzi/core.ui/domain/domain.hpp>


namespace kanzi
{

template <typename TFinalClass, typename TLayout, typename TItemClass, typename TScrollView>
class ListBoxTrajectoryPresenter
{
public:
    typedef ListBoxTrajectoryPresenter<TFinalClass, TLayout, TItemClass, TScrollView> ListBoxTrajectoryPresenterType;

    typedef shared_ptr<TLayout> LayoutSharedPtr;
    typedef shared_ptr<TItemClass> ItemSharedPtr;
    typedef shared_ptr<TScrollView> ScrollViewSharedPtr;

    LayoutSharedPtr getLayout() const
    {
        return m_layout;
    }

    /// Implements notifyItemAdded for a trajectory list box. Called by the ListBoxConceptImpl after the item has been added.
    /// \param index Index of the item that was added.
    void notifyItemAdded(unsigned int index)
    {
        m_layout->invalidateMeasure();

        const unsigned int newTotalItemCount = m_listBox->getItemCount();
        kzAssert(newTotalItemCount > 0);
        const unsigned int oldTotalItemCount = newTotalItemCount - 1;

        // Normalize fixed point index to a positive number in the range of indices.
        if (oldTotalItemCount > 0)
        {
            m_fixedPointIndex = kzsRemainder(m_fixedPointIndex, oldTotalItemCount);

            // If the added item is before the fixed point in the list, shift the fixed point up one slot.
            if (index <= static_cast<unsigned int>(m_fixedPointIndex))
            {
                ++m_fixedPointIndex;
            }
        }

        // Make sure the fixed point is always within the non-virtualized range.
        m_firstIndex = m_fixedPointIndex;
        m_rangeSize = 1u;
        kzAssert(m_rangeSize == 0 || kzsRemainder(m_fixedPointIndex - m_firstIndex, newTotalItemCount) < m_rangeSize);
    }

    /// Implements notifyItemRemoved for a trajectory list box. Called by the ListBoxConceptImpl before the item is removed.
    /// \param index Index of the item that will be removed.
    void notifyItemRemoved(unsigned int index)
    {
        m_layout->invalidateMeasure();

        const unsigned int oldTotalItemCount = m_listBox->getItemCount();
        kzAssert(oldTotalItemCount > 0);
        const unsigned int newTotalItemCount = oldTotalItemCount - 1;

        // Normalize fixed point index to a positive number in the range of indices.
        m_fixedPointIndex = kzsRemainder(m_fixedPointIndex, oldTotalItemCount);

        // If the removed item is before the fixed point in the list, shift the fixed point down one slot.
        if (index <= static_cast<unsigned int>(m_fixedPointIndex) && m_fixedPointIndex > 0)
        {
            --m_fixedPointIndex;
        }

        // Make sure the fixed point is always be within the non-virtualized range.
        m_firstIndex = m_fixedPointIndex;
        m_rangeSize = newTotalItemCount > 0u ? 1u : 0u;
        kzAssert(m_rangeSize == 0 || oldTotalItemCount == 1 || kzsRemainder(m_fixedPointIndex - m_firstIndex, oldTotalItemCount - 1) < m_rangeSize);
    }

    /** Implements kzuPresenterItemReplaced for trajectory list box. */
    void notifyItemReplaced(unsigned int /*index*/)
    {
        m_layout->invalidateMeasure();
    }

    /// Invalidates layout if the item container is changed.
    void notifyItemContainerChanged()
    {
        m_layout->invalidateMeasure();
    }

    void initialize(TFinalClass* listBox, LayoutSharedPtr layout)
    {
        m_listBox = listBox;
        m_layout = layout;

        kzsError result;
        result = kzuVirtualItemListCreate(m_listBox->getDomain()->getMemoryManager(),
                                          kzuTrajectoryLayoutPresenterItemWidthFunction_internal,
                                          kzuTrajectoryLayoutPresenterItemListSizeFunction_internal, this,
                                          kzuTrajectoryLayoutPresenterItemCountFunction_internal, this,
                                          &m_itemList);
        kzThrowIfError(result);

        /* Invalidate view interval. */
        kzuVirtualItemIteratorInvalidate(&m_viewIntervalLeft);
        kzuVirtualItemIteratorInvalidate(&m_viewIntervalRight);

        /* Read spacing property. */
        kzuVirtualItemListSetSpacing(m_itemList, m_listBox->getSpacing());

        ScrollViewSharedPtr scrollView = m_listBox->getScrollView();

        scrollView->setScrollBoundsX(KZ_FLOAT_MINIMUM, KZ_FLOAT_MAXIMUM);
        scrollView->setScrollBoundsY(KZ_FLOAT_MINIMUM, KZ_FLOAT_MAXIMUM);
    }

    /** Updates presenter's state and visible items. */
    void update()
    {
        kzsError result;
        unsigned int totalItemCount = m_listBox->getItemCount();
        float trajectoryLength = m_layout->getCurveLength();
        float scrollOffset = -m_scrollOffset / trajectoryLength;
        float selectorOffset = m_listBox->getCursorOffset();

        /* Center initial position to first item. */
        scrollOffset -= selectorOffset;

        /* Set looping value. */
        {
            kzBool wasLooping = kzuVirtualItemListIsLooping(m_itemList);
            bool isLooping = m_listBox->isLooping();
            kzuVirtualItemListSetLooping(m_itemList, isLooping);

            /* If looping is disabled runtime, update current indexes to valid range. */
            if(wasLooping && !isLooping && totalItemCount > 0)
            {
                m_fixedPointIndex = (int)kzsRemainder(m_fixedPointIndex, totalItemCount);
                m_firstIndex = m_fixedPointIndex;
                m_rangeSize = 1;
            }
        }

        /* Update view area. */
        m_viewLeft = scrollOffset * trajectoryLength;
        m_viewRight = (scrollOffset + 1.0f) * trajectoryLength;

        if(totalItemCount == 0 || trajectoryLength <= 0.0f)
        {
            /* Hide all items. */
            m_listBox->updateVisibleRange(0, 0);

            m_firstIndex = 0;
            m_rangeSize = 0;
            m_fixedPointIndex = 0;
            m_fixedPointOffset = 0.0f;
            kzuVirtualItemIteratorInvalidate(&m_viewIntervalLeft);
        }
        else
        {
            unsigned int keepAlive = m_listBox->getKeepAliveItemCount();
            keepAlive = kzsMinU(keepAlive, totalItemCount);

            /* Put items that fit in the visible range to the trajectory layout and return other items to the object generator. Request new items if there is empty space in the visible range. */
            bool forceAllVisible = calculateVisibleRange();

            kzAssert(kzuVirtualItemIteratorIsValid(&m_viewIntervalLeft));
            kzAssert(kzuVirtualItemIteratorIsValid(&m_viewIntervalRight));
            kzAssert(m_rangeSize > 0);

            // TODO: With no virtualization this block loops over all items several times. Modify to update only items that become visible/invisible
            /* Update item visibility and offsets in the trajectory layout. */
            {
                ItemSharedPtr objectNode;
                unsigned int itemCount = kzuVirtualItemListGetIntervalElementCount(&m_viewIntervalLeft, &m_viewIntervalRight);
                kzAssert(itemCount <= totalItemCount);
                KzuVirtualItemIterator it = m_viewIntervalLeft;

                /* TODO: try to find a way to not re-set the visible property for all keep alive items every frame, set only when items disappear. */
                /* Make keep alive objects invisible. */
                {
                    int firstItemIndex = it.index;
                    int lastItemIndex = firstItemIndex + (int)itemCount - 1;
                    unsigned int firstItemLoopedIndex = kzsRemainder(firstItemIndex, totalItemCount);
                    unsigned int lastItemLoopedIndex = kzsRemainder(lastItemIndex, totalItemCount);

                    // For some reason since fixed point item should be always inside of non-virtualized item range, this range is
                    // stretched so fixed point item is inside of this range (by calculating m_firstIndex and m_rangeSize member vars in calculateVisibleRange()).
                    // Because of this there are alive items outside of visible range even if virtualization is not enabled, and these alive items are not
                    // set to invisible by existing logic of presenter.
                    // The block below fixes the issue for now, but it should be removed and presenter should be refactored.
                    {
                        if(m_firstIndex < m_viewIntervalLeft.index)
                        {
                            for(int i = 0, count = (m_viewIntervalLeft.index - m_firstIndex); i < count; ++i)
                            {
                                objectNode = getItem(m_firstIndex + i);
                                if (objectNode)
                                {
                                    objectNode->setVisible(false);
                                }
                            }
                        }

                        if(static_cast<int>(m_firstIndex + m_rangeSize) > m_viewIntervalRight.index)
                        {
                            for(int i = 0, count = (static_cast<int>(m_firstIndex + m_rangeSize) - (m_viewIntervalRight.index + 1)); i < count; ++i)
                            {
                                objectNode = getItem(m_viewIntervalRight.index + 1 + i);
                                if (objectNode)
                                {
                                    objectNode->setVisible(false);
                                }
                            }
                        }
                    }

                    for(unsigned int i = 0; i < keepAlive; ++i)
                    {
                        unsigned int index = kzsRemainder(firstItemIndex - (int)i - 1, totalItemCount);
                        if(index == lastItemLoopedIndex)
                        {
                            /* Don't make objects on visible range invisible. */
                            break;
                        }
                        objectNode = getItem(index);
                        if (objectNode)
                        {
                            objectNode->setVisible(false);
                        }
                        else
                        {
                            break;
                        }
                    }
                    for(unsigned int i = 0; i < keepAlive; ++i)
                    {
                        unsigned int index = kzsRemainder(lastItemIndex + (int)i + 1, totalItemCount);
                        if(index == firstItemLoopedIndex)
                        {
                            /* Don't make objects on visible range invisible. */
                            break;
                        }
                        objectNode = getItem(index);
                        if (objectNode)
                        {
                            objectNode->setVisible(false);
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                /* Update visible object offsets and set their visible property to true. */
                for(unsigned int i = 0; i < itemCount; ++i)
                {
                    bool visible;
                    unsigned int index = kzuVirtualItemIteratorGetIndex(&it);
                    float offset = (kzuVirtualItemIteratorGetCenter(&it) - m_viewLeft) / trajectoryLength;

                    if(forceAllVisible)
                    {
                        offset = kzsRemainderf(offset, 1.0f);
                    }

                    visible = offset >= 0.0f && offset <= 1.0f; /* Hide items that are outside the trajectory because trajectory offsets outside [0,1] are not valid. */

                    objectNode = getItem(index);

                    if(visible)
                    {
                        TLayout::setOverrideOffset(*objectNode, offset);
                    }

                    objectNode->setVisible(visible);

                    if(i < itemCount - 1) /* Don't iterate past the last valid item. */
                    {
                        result = kzuVirtualItemIteratorNext(&it);
                        kzThrowIfError(result);
                    }
                }
            }

            /* Re-measure layout object because objects have moved, and children may have been removed or added, and we are already in the arrange phase. */
            {
                // TODO: should affectparent fix this?
                /* Invalidate measure, because changing KZU_PROPERTY_TYPE_STATIC_TRAJECTORY_OFFSET of children doesn't do it. */
                m_layout->invalidateMeasure();
                m_layout->measureRecursive();
            }
        }
    }

    void setScroll(Vector2 scroll)
    {
        const bool horizontalScroll = m_listBox->getScrollView()->getAllowedScrollAxis() & ScrollViewConcept::XAxis;
        m_scrollOffset = horizontalScroll ? scroll.getX() : scroll.getY();
    }

    void addToLayout(ItemSharedPtr listBoxItem)
    {
        /* Add list box item to layout. */
        m_layout->addChild(listBoxItem);
    }

    void removeFromLayout(ItemSharedPtr listBoxItem)
    {
        // The item might have been removed from the parent already during project patching.
        // Remove it here if it is still a child of the list box.
        if (listBoxItem->getParent())
        {
            m_layout->removeChild(*listBoxItem);
        }
    }

    explicit ListBoxTrajectoryPresenter() :
        m_listBox(0),
        m_itemList(0),
        m_viewLeft(0.0f),
        m_viewRight(0.0f),
        m_scrollOffset(0.0f),
        m_firstIndex(0),
        m_rangeSize(0),
        m_fixedPointIndex(0),
        m_fixedPointOffset(0.0f)
    {
    }

    ~ListBoxTrajectoryPresenter()
    {
        kzsError result;
        
        result = kzuVirtualItemListDelete(m_itemList);
        kzThrowIfError(result);
    }

    KzuVirtualItemIterator findMiddleIterator()
    {
        // Recalculate m_viewIntervalLeft and m_viewIntervalRight because they might not be up-to-date if items have been added or removed since last update.
        update();

        float leftOffset = kzuVirtualItemIteratorGetCenter(&m_viewIntervalLeft);
        float rightOffset = kzuVirtualItemIteratorGetCenter(&m_viewIntervalRight);
        /* TODO: this is incorrect offset: m_viewInterval is not symmetrical because it starts and ends from items.
          Should probably use m_viewLeft and m_viewRight. */
        float middleOffset = leftOffset + m_listBox->getCursorOffset() * (rightOffset - leftOffset);

        KzuVirtualItemIterator iterator = m_viewIntervalLeft;
        /* Move iterator to the left until its left edge is left from the target. */
        while(kzuVirtualItemIteratorHasPrevious(&iterator) && kzuVirtualItemIteratorGetLeftEdge(&iterator) > middleOffset)
        {
            iterateLeft(&iterator);
        }

        /* Move side iterator to the right until its right edge is right from the target. */
        while(kzuVirtualItemIteratorHasNext(&iterator) && kzuVirtualItemIteratorGetRightEdge(&iterator) < middleOffset)
        {
            iterateRight(&iterator);
        }

        return iterator;
    }

    /** Brings given item to the selector position. */
    Vector2 bringItemCenter(unsigned int selection)
    {
        // Get an iterator to the item closest to the cursor.
        KzuVirtualItemIterator it = findMiddleIterator();

        // Iterate from cursor to the selected item through the shorter route.
        iterateToIndex(&it, selection);

        float selectionOffset = kzuVirtualItemIteratorGetCenter(&it);

        m_fixedPointIndex = it.index;
        m_fixedPointOffset = it.offset;

        return Vector2(-selectionOffset, 0.0f);
    }

    /**
    * Snaps towards given direction from given position.
    * Returns snapping target and index of the object that scrolling snapped to, unless they're given as KZ_NULL.
    * The changeTarget should be KZ_TRUE if the list box target is changed to the snapped item.
    *
    * If snapping happened towards no object, index will be -1.
    */
    void snap(Vector2 position, Vector2 direction, bool changeTarget, Vector2* out_position, int* out_itemIndex)
    {
        static float directionTolerance = 0.0001f;

        Vector2 snapPosition = position;
        int snapIndex = KZU_UI_LIST_BOX_NO_ITEM;

        float trajectoryLength = m_layout->getCurveLength();
        unsigned int totalItemCount = m_listBox->getItemCount();

        float trajectoryOffset = -snapPosition.getX();

        if (totalItemCount > 0 && trajectoryLength > 0.0f && m_rangeSize > 0)
        {
            KzuTrajectoryLayoutSnapInfo closest;

            // Which directions are allowed for snapping in the basic case.
            kzBool snapLeft = direction.getX() <= directionTolerance;   //< Is snapping to negative X allowed.
            kzBool snapRight = direction.getX() >= -directionTolerance; //< Is snapping to positive X allowed.

            // Find the snap candidates.
            KzuVirtualItemIterator it = m_viewIntervalLeft;
            float signedDistance = kzuVirtualItemIteratorGetCenter(&it) - trajectoryOffset;

            // Reveal items from left until the selector is covered.
            while (kzuVirtualItemIteratorHasPrevious(&it) && signedDistance > 0.0f)
            {
                iterateLeft(&it);

                signedDistance = kzuVirtualItemIteratorGetCenter(&it) - trajectoryOffset;
            }

            // Reveal items from right until the selector is covered.
            while (kzuVirtualItemIteratorHasNext(&it) && signedDistance < 0.0f)
            {
                iterateRight(&it);

                signedDistance = kzuVirtualItemIteratorGetCenter(&it) - trajectoryOffset;
            }

            // Snap to candidates.
            {
                KzuVirtualItemIterator previous = it;
                KzuVirtualItemIterator next = it;

                if (kzuVirtualItemIteratorHasNext(&next))
                {
                    iterateRight(&next);
                }

                if (kzuVirtualItemIteratorHasPrevious(&previous))
                {
                    iterateLeft(&previous);
                }

                snapImprove(&closest, kzuVirtualItemIteratorGetIndex(&previous),
                    kzuVirtualItemIteratorGetCenter(&previous), trajectoryOffset,
                    snapLeft, snapRight);

                snapImprove(&closest, kzuVirtualItemIteratorGetIndex(&next),
                    kzuVirtualItemIteratorGetCenter(&next), trajectoryOffset,
                    snapLeft, snapRight);

                {
                    kzBool snapLeftEdge = !kzuVirtualItemIteratorHasPrevious(&it) && kzuVirtualItemIteratorGetCenter(&it) > trajectoryOffset;
                    kzBool snapRightEdge = !kzuVirtualItemIteratorHasNext(&it) && kzuVirtualItemIteratorGetCenter(&it) < trajectoryOffset;
                    kzBool snapAtEdge = snapLeftEdge || snapRightEdge;

                    snapImprove(&closest, kzuVirtualItemIteratorGetIndex(&it),
                                kzuVirtualItemIteratorGetCenter(&it), trajectoryOffset,
                                snapAtEdge | snapLeft, snapAtEdge | snapRight);
                }
            }

            // Let the next update trim the virtualized range instead of doing it here.

            // Apply snap.
            if (closest.found)
            {
                float targetOffsetDelta = trajectoryOffset - closest.offset;
                float targetTrajectoryOffset = trajectoryOffset - targetOffsetDelta;
                float targetScrollOffset = -targetTrajectoryOffset;

                snapPosition.setX(targetScrollOffset);

                snapIndex = (int)closest.index;

                if (changeTarget)
                {
                    // Make the new targeted object the fixed point of position calculations, so that if the targeted object is resized while it is
                    // still being centered, it is still always correctly centered, even without any corrections to the scroll view state.
                    m_fixedPointIndex = snapIndex;
                    m_fixedPointOffset = closest.offset;
                }
            }
        }

        if (out_position)
        {
            *out_position = snapPosition;
        }

        if (out_itemIndex)
        {
            *out_itemIndex = snapIndex;
        }
    }

protected:

    /** Sets indices and offsets of first and last visible items and the number of visible elements. Sets the values of viewInternal member. */
    bool calculateVisibleRange()
    {
        kzsError result;
        KzuVirtualItemIterator firstIterator = m_viewIntervalLeft;
        KzuVirtualItemIterator lastIterator;
        unsigned int totalItemCount = m_listBox->getItemCount();
        unsigned int rangeSize;
        bool forceAllVisible = false;
        unsigned int iterationCount; /* Iteration count is used to detect when all items in the list have zero size, which requires a special handling. */
        kzBool hasNonZeroSizeChild = KZ_TRUE;
        float spacing = m_listBox->getSpacing();
        kzuVirtualItemListSetSpacing(m_itemList, spacing); /* First use the spacing property to fit as many objects as possible. If empty space remains, expand the virtual item list
                                                                  spacing until all space is filled. */

        kzAssert(totalItemCount > 0);

        if(m_rangeSize == 0)
        {
            m_firstIndex = 0;
            m_rangeSize = 1;
            m_fixedPointIndex = 0;
            m_fixedPointOffset = 0.0f;
        }

        /* Update visible range with old values in case the list box and all its items has been detached. */
        updateVisibleRange();

        /* Start from the one fixed point from the previous frame. */
        firstIterator.index = m_fixedPointIndex;
        firstIterator.offset = m_fixedPointOffset;
        firstIterator.valid = KZ_TRUE;
        firstIterator.itemList = m_itemList;

        result = kzuVirtualItemIteratorUpdateWidth(&firstIterator);
        kzThrowIfError(result);

        /* Reveal items until the left edge of the visible area is covered. */
        iterationCount = 0;
        while (hasNonZeroSizeChild && kzuVirtualItemIteratorHasPrevious(&firstIterator) &&
            ((kzuVirtualItemIteratorGetLeftEdge(&firstIterator) - spacing) > m_viewLeft) &&
            // For negative spacing:
            ((spacing >= 0.0f) || (kzuVirtualItemIteratorGetLeftEdge(&firstIterator) - spacing < m_viewRight)))
        {
            iterateLeft(&firstIterator);

            ++iterationCount;
            if((iterationCount > totalItemCount) && (abs(firstIterator.offset - m_fixedPointOffset) < 0.0001f))
            {
                /* Break to prevent infinite loop. */
                hasNonZeroSizeChild = KZ_FALSE;
            }
        }

        /* Hide items on the left side of the left edge of the visible area. */
        iterationCount = 0;
        while(hasNonZeroSizeChild && kzuVirtualItemIteratorHasNext(&firstIterator) &&
            (kzuVirtualItemIteratorGetRightEdge(&firstIterator) < m_viewLeft) &&
            // For negative spacing:
            ((spacing >= 0.0f) || (kzuVirtualItemIteratorGetRightEdge(&firstIterator) > m_viewLeft)))
        {
            iterateRight(&firstIterator);

            ++iterationCount;
            if((iterationCount > totalItemCount) && (abs(firstIterator.offset - m_fixedPointOffset) < 0.0001f))
            {
                /* Break to prevent infinite loop. */
                hasNonZeroSizeChild = KZ_FALSE;
            }
        }

        kzAssert(hasNonZeroSizeChild || abs(firstIterator.offset - m_fixedPointOffset) < 0.0001f);

        /* Show items until the right edge of the visible area is covered. */
        lastIterator = firstIterator;
        rangeSize = 1;
        while(kzuVirtualItemIteratorHasNext(&lastIterator) && kzuVirtualItemIteratorGetRightEdge(&lastIterator) + spacing < m_viewRight && rangeSize < totalItemCount)
        {
            ++rangeSize;

            iterateRight(&lastIterator);
        }

        kzAssert(hasNonZeroSizeChild || (rangeSize == totalItemCount || rangeSize == 1));

        /* Special case for a list where all items are visible: don't let the leftmost item disappear when it should actually be the rightmost item or vice versa. */
        if((!hasNonZeroSizeChild || rangeSize == totalItemCount) && kzuVirtualItemListIsLooping(m_itemList))
        {
            float filledArea = (hasNonZeroSizeChild ? kzuVirtualItemIteratorGetRightEdge(&lastIterator) - kzuVirtualItemIteratorGetLeftEdge(&firstIterator) : 0.0f);
            float availableArea = m_viewRight - m_viewLeft;
            float freeArea = availableArea - filledArea - spacing;

            kzAssert(hasNonZeroSizeChild || abs(filledArea) < 0.0001f);

            if(freeArea > -0.01f) /* Allow some leeway for numerical errors. */
            {
                float spacingChange = freeArea / (float)totalItemCount;
                forceAllVisible = true;

                spacing += spacingChange;
                kzuVirtualItemListSetSpacing(m_itemList, spacing);

                /* Spacing changed => the previously calculated iterators are not valid => recalculate iterators. */
                firstIterator.index = m_fixedPointIndex;
                firstIterator.offset = m_fixedPointOffset;
                result = kzuVirtualItemIteratorUpdateWidth(&firstIterator);
                kzThrowIfError(result);
                /* Reveal items until the left edge of the visible area is covered. */
                while(kzuVirtualItemIteratorGetLeftEdge(&firstIterator) - spacing > m_viewLeft)
                {
                    result = kzuVirtualItemIteratorPrevious(&firstIterator);
                    kzThrowIfError(result);
                }
                /* Hide items on the left side of the left edge of the visible area. */
                while(kzuVirtualItemIteratorGetRightEdge(&firstIterator) < m_viewLeft)
                {
                    result = kzuVirtualItemIteratorNext(&firstIterator);
                    kzThrowIfError(result);
                }
                /* TODO: right iterator is probably not needed anywhere, remove it completely. */
                lastIterator = firstIterator;
                for(unsigned int i = 1; i < totalItemCount; ++i)
                {
                    result = kzuVirtualItemIteratorNext(&lastIterator);
                    kzThrowIfError(result);
                }
            }
        }

        m_viewIntervalLeft = firstIterator;
        m_viewIntervalRight = lastIterator;

        /* Virtualize all items outside the visible area that is extended to contain the fixedPoint. */
        {
            int startIndex = firstIterator.index;
            int endIndex = lastIterator.index;
            kzAssert(endIndex >= startIndex);

            if(m_fixedPointIndex < startIndex)
            {
                startIndex = m_fixedPointIndex;
            }
            else if(m_fixedPointIndex > endIndex)
            {
                endIndex = m_fixedPointIndex;
            }

            kzAssert(endIndex >= startIndex);
            m_firstIndex = startIndex;
            m_rangeSize = kzsMinU((unsigned int)(endIndex - startIndex + 1), totalItemCount);

            updateVisibleRange();
        }

        kzAssert(m_rangeSize > 0); /* One item is always kept in memory as a reference point. */

#ifdef KANZI_DEBUG
        /* The left and right iterators, and everything in between should always be within the non-virtualized range. */
        {
            KzuVirtualItemIterator debugIterator = m_viewIntervalLeft;
            kzAssert(kzsRemainder(debugIterator.index - m_firstIndex, totalItemCount) < m_rangeSize);
            while(debugIterator.index < m_viewIntervalRight.index)
            {
                kzAssert(kzsRemainder(debugIterator.index + 1 - m_firstIndex, totalItemCount) < m_rangeSize);

                kzAssert(kzuVirtualItemIteratorHasNext(&debugIterator));
                result = kzuVirtualItemIteratorNext(&debugIterator);
                kzThrowIfError(result);
            }
        }
#endif
        /* Fixed point should be within non-virtualized range. */
        kzAssert(kzsRemainder(m_fixedPointIndex - m_firstIndex, totalItemCount) < m_rangeSize);

        return forceAllVisible;
    }

    /** Asks the list box to update the items in the layout according to the currently set firstIndex and rangeSize, taking also the keep alive into account. */
    void updateVisibleRange()
    {
        unsigned int totalItemCount = m_listBox->getItemCount();
        unsigned int firstIndex = kzsRemainder(m_firstIndex, totalItemCount);
        unsigned int rangeSize = m_rangeSize;

        unsigned int keepAlive = m_listBox->getKeepAliveItemCount();
        keepAlive = kzsMinU(keepAlive, totalItemCount);

        firstIndex = (firstIndex + totalItemCount - keepAlive) % totalItemCount;
        rangeSize = kzsMinU(rangeSize + keepAlive * 2, totalItemCount);

        m_listBox->updateVisibleRange(firstIndex, rangeSize);
    }

    // TODO: highly inefficient function, the presenter knows the items and indices
    ItemSharedPtr getItem(size_t presenterIndex)
    {
        for (typename TLayout::ChildConstIterator i = m_layout->beginChildren(), end = m_layout->endChildren(); i != end; ++i)
        {
            ItemSharedPtr item = dynamic_pointer_cast<TItemClass>(*i);
            if (item->getPresenterIndex() == presenterIndex)
            {
                return item;
            }
        }

        return ItemSharedPtr();
    }

    /// Iterates left in virtual item list.
    /// This operation might extend presenters range of visible items if
    /// the size of an item where iterator will be pointing to could not
    /// be determined otherwise.
    /// \param it Iterator to iterate.
    void iterateLeft(KzuVirtualItemIterator* it)
    {
        kzsError result;

        result = kzuVirtualItemIteratorPrevious(it);
        kzThrowIfError(result);
    }

    /// Iterates right in virtual item list.
    /// This operation might extend presenters range of visible items if
    /// the size of an item where iterator will be pointing to could not
    /// be determined otherwise.
    /// \param it Iterator to iterate.
    void iterateRight(KzuVirtualItemIterator* it)
    {
        kzsError result;

        result = kzuVirtualItemIteratorNext(it);
        kzThrowIfError(result);
    }

    struct KzuTrajectoryLayoutSnapInfo
    {
    public:
        KzuTrajectoryLayoutSnapInfo():
            found(false),
            index(0),
            offset(KZ_FLOAT_MAXIMUM),
            distance(KZ_FLOAT_MAXIMUM)
        {
        }

    public:
        kzBool found; /**< True if there is a snap candidate. */
        unsigned int index; /**< Index of snapped object. */
        float offset; /**< Offset of snapped object. */
        float distance; /**< Distance of snapped object from target. */
    };

    void snapImprove(KzuTrajectoryLayoutSnapInfo* snap, unsigned int objectIndex, float offset, float selectorOffset, kzBool snapLeft, kzBool snapRight)
    {
        float signedDistance = offset - selectorOffset;

        if((snapLeft && signedDistance >= 0.0f) || (snapRight && signedDistance <= 0.0f))
        {
            float distance = abs(signedDistance);

            if(distance < snap->distance)
            {
                snap->found = KZ_TRUE;
                snap->index = objectIndex;
                snap->offset = offset;
                snap->distance = distance;
            }
        }
    }

    /** Gets object's width from its size for virtual item list. */
    static float kzuTrajectoryLayoutPresenterItemWidthFunction_internal(const KzcVector3* size)
    {
        return kzcVector3GetX(size);
    }

    /// Extends visible range of presenter to it includes specified item.
    /// If item is already inside the visible range, then the range
    /// will remain unchanged.
    /// \param index Index of the item which should be included into the range.
    void extendVisibleItemRangeToItem(unsigned int index)
    {
        unsigned int itemCount = getItemCount();
        int firstItemIndex = kzsRemainder(m_firstIndex, itemCount);
        int lastItemIndex = kzsRemainder(firstItemIndex + m_rangeSize - 1, itemCount);
        int itemIndex = static_cast<int>(index);

        // Adjust indices of first and last items in visible range
        // so it includes requested item.
        if (kzuVirtualItemListIsLooping(m_itemList))
        {
            bool isItemOutside = false;

            // Determine if index is outside of visible range.
            if (firstItemIndex <= lastItemIndex)
            {
                isItemOutside = ((itemIndex < firstItemIndex) || (itemIndex > lastItemIndex));
            }
            else
            {
                isItemOutside = ((itemIndex > lastItemIndex) && (itemIndex < firstItemIndex));
            }

            // Adjust indices if item is outside of visible range.
            if (isItemOutside)
            {
                if (kzsAbs(firstItemIndex - itemIndex) < kzsAbs(lastItemIndex - itemIndex))
                {
                    firstItemIndex = itemIndex;
                }
                else
                {
                    lastItemIndex = itemIndex;
                }
            }
        }
        else
        {
            // Adjust indices if item is outside of visible range.
            if (itemIndex < firstItemIndex)
            {
                firstItemIndex = itemIndex;
            }
            else if (itemIndex > lastItemIndex)
            {
                lastItemIndex = itemIndex;
            }
        }

        // Indices of first and last items should be different.
        kzAssert(firstItemIndex != lastItemIndex);

        // Adjust last item to calculate the visible range size correctly.
        if (firstItemIndex > lastItemIndex)
        {
            lastItemIndex += itemCount;
        }

        // Calculate new range size.
        unsigned int rangeSize = lastItemIndex - firstItemIndex + 1;

        // Update visible range if it has changed.
        if ((firstItemIndex != m_firstIndex) || (rangeSize != m_rangeSize))
        {
            m_firstIndex = firstItemIndex;
            m_rangeSize = rangeSize;

            updateVisibleRange();
        }
    }

    /// Returns size of an item specified by its index.
    /// If the item is outside of presenters range of visible items
    /// and its size could not be determined by list box, the visible range
    /// will be extended so list box can acquire the item and determine its size.
    /// \param itemIndex Index of an item whose size should be returned.
    /// \return size of an item.
    Vector3 getItemSize(unsigned int itemIndex)
    {
        // Try to get item size from list box.
        Vector3 itemSize = m_listBox->getItemSize(itemIndex);

        // List box returns unbounded layout value as item size if it could not determine
        // the size of the item. It can happen because item is not acquired by list box.
        // Ask list box to acquire the item and try to get its size once more.
        if (TItemClass::isUnboundedLayoutSize(itemSize))
        {
            extendVisibleItemRangeToItem(itemIndex);
            itemSize = m_listBox->getItemSize(itemIndex);
        }

        // At this point list box should return valid item size.
        kzAssert(!TItemClass::isUnboundedLayoutSize(itemSize));

        return itemSize;
    }

    /// Gets number of items in presenters list box.
    /// \return item count.
    unsigned int getItemCount()
    {
        return m_listBox->getItemCount();
    }

    /** Gets object's size by index. */
    static kzsError kzuTrajectoryLayoutPresenterItemListSizeFunction_internal(unsigned int index, void* userData, KzcVector3* out_size)
    {
        ListBoxTrajectoryPresenterType* presenter = static_cast<ListBoxTrajectoryPresenterType*>(userData);

        *out_size = legacy::convert(presenter->getItemSize(index));
        kzsSuccess();
    }

    /** Gets list box's total item count. */
    static unsigned int kzuTrajectoryLayoutPresenterItemCountFunction_internal(void* userData)
    {
        ListBoxTrajectoryPresenterType* presenter = static_cast<ListBoxTrajectoryPresenterType*>(userData);

        return presenter->getItemCount();
    }

    /** Iterates the iterator to the given index. */
    void iterateToIndex(KzuVirtualItemIterator* iterator, unsigned int index)
    {
        unsigned int itemCount = m_listBox->getItemCount();

        kzAssert(kzuVirtualItemIteratorIsValid(iterator));

        if(itemCount > 0)
        {
            if(kzuVirtualItemListIsLooping(iterator->itemList))
            {
                /* Iterate to the given index (modulo itemCount) through the shorter direction (shorter in number of indices). */
                unsigned int modularStartIndex = kzuVirtualItemIteratorGetIndex(iterator);

                unsigned int leftDistance = (modularStartIndex + itemCount - index) % itemCount;
                unsigned int rightDistance = (index + itemCount - modularStartIndex) % itemCount;

                if (rightDistance == leftDistance && leftDistance != 0)
                {
                    // Decide which direction to go to if index distances are same.

                    // If we were already in motion, e.g. from previous selection request, it's possible the index distances are same
                    // even if the item is clearly already closer from one side. It also happens frequently if item width is 0.

                    // Take distance from fixed point offset and prefer going left if it's more than half spacing
                    float diff = iterator->offset - m_fixedPointOffset;
                    if (diff > m_listBox->getSpacing() * 0.5f)
                    {
                        // Prefer left side by making right side appear worse.
                        rightDistance++;
                    }
                }

                if(rightDistance <= leftDistance)
                {
                    for(unsigned int i = 0; i < rightDistance; ++i)
                    {
                        iterateRight(iterator);
                    }
                }
                else
                {
                    for(unsigned int i = 0; i < leftDistance; ++i)
                    {
                        iterateLeft(iterator);
                    }
                }
            }
            else
            {
                // Iterate to the given index straight as no looping is possible.
                while(iterator->index < (int)index)
                {
                    iterateRight(iterator);
                }

                while(iterator->index > (int)index)
                {
                    iterateLeft(iterator);
                }
            }
        }
    }

private:

    LayoutSharedPtr m_layout;
    TFinalClass* m_listBox;

    KzuVirtualItemList* m_itemList; /**< Virtual collection of virtual items. */
    KzuVirtualItemIterator m_viewIntervalLeft; /**< Iterator to the leftmost item in the visible area. */
    KzuVirtualItemIterator m_viewIntervalRight; /**< Iterator to the rightmost item in the visible area. */

    float m_viewLeft; /**< Offset of the beginning of the visible area. In scene units. */
    float m_viewRight; /**< Offset of the end of the visible area. In scene units. */

    float m_scrollOffset; /**< Offset of scrolling. In proportional space. */

    int m_firstIndex; /**< Index of the first item in the visible area. */
    unsigned int m_rangeSize; /**< Number of items in the visible area. */

    int m_fixedPointIndex; /**< Index of an item that is currently acting as a fixed point in the list. */
    float m_fixedPointOffset; /**< The offset of the fixed point. This maps all items to the their places in the list:
                                   even when object sizes change between updates, the location of the item in fixedPointIndex stays constant. */
};

}

#endif
