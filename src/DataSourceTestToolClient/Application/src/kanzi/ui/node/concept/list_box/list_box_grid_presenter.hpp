// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LIST_BOX_GRID_PRESENTER_HPP
#define KZ_LIST_BOX_GRID_PRESENTER_HPP

#include <kanzi/ui/node/scroll_view3d.hpp>
#include <kanzi/ui/node/concept/list_box.hpp>
#include <kanzi/ui/node/concept/grid_list_box.hpp>


namespace kanzi
{

template <typename TFinalClass, typename TLayout, typename TItemClass, typename TScrollView>
class ListBoxGridPresenter
{
public:

    typedef shared_ptr<TLayout> LayoutSharedPtr;
    typedef shared_ptr<TItemClass> ItemSharedPtr;
    typedef shared_ptr<TScrollView> ScrollViewSharedPtr;

    explicit ListBoxGridPresenter() :
        m_layout(),
        m_listBox(),
        m_stateChanged(true)
    {
    }

    void initialize(TFinalClass* listBox, LayoutSharedPtr layout)
    {
        m_listBox = listBox;
        m_layout = layout;
    }

    void scrollDirectionMessageHandler(ScrollViewConcept::ScrollDirectionMessageArguments& arguments)
    {
        ScrollViewConcept::ScrollDirection direction = arguments.getScroll();
        scroll(direction);
    }

    void scrollPageMessageHandler(ScrollViewConcept::ScrollPageMessageArguments& arguments)
    {
        ScrollViewConcept::ScrollPage direction = arguments.getScroll();
        scroll(direction);
    }

    void scrollEdgeMessageHandler(ScrollViewConcept::ScrollEdgeMessageArguments& arguments)
    {
        ScrollViewConcept::ScrollEdge direction = arguments.getScroll();
        scroll(direction);
    }

    /// Handles key down event.
    void onKeyDown(Keyboard::KeyDownMessageArguments& arguments)
    {
        arguments.setHandled(false);
        KzsInputKey key = arguments.getKey();
        switch (key)
        {
            case KZS_KEY_ARROW_UP:
            {
                if (m_currentState.layoutDirection == GridLayoutConcept::GridDirectionDown)
                {
                    return;
                }

                scroll(ScrollViewConcept::ScrollUp);
                break;
            }
            case KZS_KEY_ARROW_DOWN:
            {
                if (m_currentState.layoutDirection == GridLayoutConcept::GridDirectionDown)
                {
                    return;
                }

                scroll(ScrollViewConcept::ScrollDown);
                break;
            }
            case KZS_KEY_ARROW_LEFT:
            {
                if (m_currentState.layoutDirection == GridLayoutConcept::GridDirectionRight)
                {
                    return;
                }

                scroll(ScrollViewConcept::ScrollLeft);
                break;
            }
            case KZS_KEY_ARROW_RIGHT:
            {
                if (m_currentState.layoutDirection == GridLayoutConcept::GridDirectionRight)
                {
                    return;
                }

                scroll(ScrollViewConcept::ScrollRight);
                break;
            }
            case KZS_KEY_PAGE_UP:
            {
                scroll(ScrollViewConcept::ScrollPageUp);
                break;
            }
            case KZS_KEY_PAGE_DOWN:
            {
                scroll(ScrollViewConcept::ScrollPageDown);
                break;
            }
            case KZS_KEY_HOME:
            {
                scroll(ScrollViewConcept::ScrollHome);
                break;
            }
            case KZS_KEY_END:
            {
                scroll(ScrollViewConcept::ScrollEnd);
                break;
            }
            default:
            {
                return;
            }
        }

        arguments.setHandled(true);
    }

    /// Sets scroll delta to one item and starts scrolling to that direction.
    /// \param direction Scroll direction.
    void scroll(ScrollViewConcept::ScrollDirection direction)
    {
        ScrollViewSharedPtr scrollView = m_listBox->getScrollView();
        if (scrollView->isDragging())
        {
            return;
        }

        if (m_currentState.totalItemCount == 0)
        {
            return;
        }

        int newIndex = m_listBox->getSelectedItemIndex();
        if (newIndex == -1)
        {
            newIndex = 0;
        }

        switch (direction)
        {
            case ScrollViewConcept::ScrollUp:
            case ScrollViewConcept::ScrollLeft:
            {
                --newIndex;
                break;
            }
            case ScrollViewConcept::ScrollDown:
            case ScrollViewConcept::ScrollRight:
            {
                ++newIndex;
                break;
            }
        }

        newIndex = clamp(newIndex, 0, m_currentState.totalItemCount - 1);
        m_listBox->setSelectedItemIndex(newIndex);

        scrollView->scrollToPosition(bringItemCenter(newIndex));
    }

    /// Sets scroll delta to one page and starts scrolling to that direction.
    /// \param direction Scroll direction.
    void scroll(ScrollViewConcept::ScrollPage direction)
    {
        ScrollViewSharedPtr scrollView = m_listBox->getScrollView();
        if (scrollView->isDragging())
        {
            return;
        }

        if (m_currentState.totalItemCount == 0)
        {
            return;
        }

        int newIndex = m_listBox->getSelectedItemIndex();
        if (newIndex == -1)
        {
            newIndex = 0;
        }

        switch (direction)
        {
            case ScrollViewConcept::ScrollPageUp:
            {
                newIndex -= m_currentState.fittingColumns * m_currentState.fittingRows;
                break;
            }
            case ScrollViewConcept::ScrollPageDown:
            {
                newIndex += m_currentState.fittingColumns * m_currentState.fittingRows;
                break;
            }
        }

        newIndex = clamp(newIndex, 0, m_currentState.totalItemCount - 1);
        m_listBox->setSelectedItemIndex(newIndex);

        scrollView->scrollToPosition(bringItemCenter(newIndex));
    }

    /// Sets scroll target to content edge and starts scrolling to that direction.
    /// \param direction Scroll direction.
    void scroll(ScrollViewConcept::ScrollEdge direction)
    {
        ScrollViewSharedPtr scrollView = m_listBox->getScrollView();
        if (scrollView->isDragging())
        {
            return;
        }

        if (m_currentState.totalItemCount == 0)
        {
            return;
        }

        int newIndex = 0;

        if (direction == ScrollViewConcept::ScrollEnd)
        {
            newIndex = m_currentState.totalItemCount - 1;
        }

        m_listBox->setSelectedItemIndex(newIndex);
        scrollView->scrollToPosition(bringItemCenter(newIndex));
    }

    /** Invalidates layout if an item is added. */
    void notifyItemAdded(size_t /*index*/)
    {
        m_stateChanged = true;
        m_layout->invalidateMeasure();
    }

    /** Invalidates layout if an item is removed. */
    void notifyItemRemoved(size_t /*index*/)
    {
        m_stateChanged = true;
        m_layout->invalidateMeasure();
    }

    /** Invalidates layout if an item is replaced. */
    void notifyItemReplaced(size_t /*index*/)
    {
        m_stateChanged = true;
        m_layout->invalidateMeasure();
    }


    /// Invalidates layout if the item container is changed.
    void notifyItemContainerChanged()
    {
        m_stateChanged = true;
        m_layout->invalidateMeasure();
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
        // TODO: pass correct available size like calling (with correct size): node.measure(KZ_NULL, false);
        node.measureRecursive();

        // If the list box item contains a Viewport2D node, propagate information upwards that there is a transformed scene that needs to be extracted.
        // Normally this is done during the measure phase, but here the measure phase has already passed, and a new item has been added during the arrange phase.
        if (node.hasChildrenRequireExtract())
        {
            Node2D* parent = dynamic_cast<Node2D*>(node.getParent());
            while (parent)
            {
                parent->setChildrenRequireExtract(true);
                parent = dynamic_cast<Node2D*>(parent->getParent());
            }
        }
    }

    void update()
    {
        GridLayoutConcept::GridDirection layoutDirection = m_layout->getDirection();

        /* Update new state. */
        {
            // TODO: prevent inf on update after attach and before layout
            m_currentState.actualSize = TFinalClass::replaceUnboundedLayoutSizeWithZero(m_listBox->getActualSize());

            m_currentState.keepAlive = m_listBox->getKeepAliveItemCount();
            m_currentState.cellWidth = m_listBox->getCellWidth();
            m_currentState.cellHeight = m_listBox->getCellHeight();
            m_currentState.layoutDirection = layoutDirection;
            m_currentState.totalItemCount = m_listBox->getItemCount();

            m_currentState.keepAlive = kzsMinU(m_currentState.totalItemCount, m_currentState.keepAlive);

            /* Used areas and rows. */
            {
                Vector2 scroll = m_currentState.scrollOffset;
                unsigned int fittingColumns = kzsMaxU(1, (unsigned int)(m_currentState.actualSize.getX() / m_currentState.cellWidth + KZ_FLOAT_EPSILON));
                unsigned int fittingRows = kzsMaxU(1, (unsigned int)(m_currentState.actualSize.getY() / m_currentState.cellHeight + KZ_FLOAT_EPSILON));
                unsigned int usedColumns = 0;
                unsigned int usedRows = 0;
                unsigned int totalColumns = 0;
                unsigned int totalRows = 0;
                unsigned int beginIndex = 0;
                unsigned int endIndex = 0;

                switch(m_currentState.layoutDirection)
                {
                    case GridLayoutConcept::GridDirectionRight:
                    {
                        float layoutHeight = m_currentState.actualSize.getY();
                        float scrollOffset = scroll.getY();
                        int skipCount = (int)kzsFloorf(TFinalClass::layoutUp() * scrollOffset / m_currentState.cellHeight);
                        int rows = (int)(kzsCeilf((layoutHeight + TFinalClass::layoutUp() * scrollOffset) / m_currentState.cellHeight)) - skipCount;
                        kzAssert(rows >= 0);

                        usedRows = (unsigned int)rows;
                        usedColumns = fittingColumns;
                        totalColumns = usedColumns;
                        totalRows = (m_currentState.totalItemCount + usedColumns - 1) / usedColumns;

                        beginIndex = (unsigned int)kzsClampi(skipCount * (int)usedColumns, 0, (int)m_currentState.totalItemCount);
                        endIndex = (unsigned int)kzsClampi((skipCount + (int)usedRows) * (int)usedColumns, 0, (int)m_currentState.totalItemCount);

                        if(m_currentState.keepAlive % usedColumns != 0)
                        {
                            /* Increase keep alive so that top side is expanded with a full row. */
                            m_currentState.keepAlive += usedColumns - m_currentState.keepAlive % usedColumns;
                        }
                        usedRows += (m_currentState.keepAlive + usedColumns - 1) / usedColumns * 2;
                        usedRows = kzsMinU(usedRows, (m_currentState.totalItemCount + fittingColumns - 1) / fittingColumns);
                        break;
                    }
                    case GridLayoutConcept::GridDirectionDown:
                    {
                        float layoutWidth = m_currentState.actualSize.getX();
                        float scrollOffset = scroll.getX();
                        int skipCount = (int)kzsFloorf(-scrollOffset / m_currentState.cellWidth);
                        int columns = (int)(kzsCeilf((layoutWidth - scrollOffset) / m_currentState.cellWidth)) - skipCount;
                        kzAssert(columns >= 0);

                        usedColumns = (unsigned int)columns;
                        usedRows = fittingRows;
                        totalRows = usedRows;
                        totalColumns = (m_currentState.totalItemCount + usedRows - 1) / usedRows;

                        beginIndex = (unsigned int)kzsClampi(skipCount * (int)usedRows, 0, (int)m_currentState.totalItemCount);
                        endIndex = (unsigned int)kzsClampi((skipCount + (int)usedColumns) * (int)usedRows, 0, (int)m_currentState.totalItemCount);

                        if(m_currentState.keepAlive % usedRows != 0)
                        {
                            /* Increase keep alive so that left side is expanded with a full column. */
                            m_currentState.keepAlive += usedRows - m_currentState.keepAlive % usedRows;
                        }
                        usedColumns += (m_currentState.keepAlive + usedRows - 1) / usedRows * 2;
                        usedColumns = kzsMinU(usedColumns, (m_currentState.totalItemCount + fittingRows - 1) / fittingRows);
                        break;
                    }
                    default:
                    {
                        kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Invalid enum value passed to KzuUiGridLayoutDirection in KzuGridLayoutPresenterData: value {} is out of valid range", m_currentState.layoutDirection));
                    }
                }

                m_currentState.usedColumns = usedColumns;
                m_currentState.usedRows = usedRows;
                m_currentState.fittingColumns = fittingColumns;
                m_currentState.fittingRows = fittingRows;
                m_currentState.totalColumns = totalColumns;
                m_currentState.totalRows = totalRows;
                m_currentState.beginIndex = beginIndex;
                m_currentState.endIndex = endIndex;
            }
        }

        /* Refresh items if needed. */
        if(isStateChanged())
        {
            /* Update grid. */
            {
                unsigned int rows = m_layout->getRowCount();
                unsigned int columns = m_layout->getColumnCount();
                unsigned int usedRows = m_currentState.usedRows;
                unsigned int usedColumns = m_currentState.usedColumns;
                unsigned int i;

                /* Resize existing rows and columns. */
                for(i = 0; i < columns; ++i)
                {
                    m_layout->setColumnFixed(i, m_currentState.cellWidth);
                }

                for(i = 0; i < rows; ++i)
                {
                    m_layout->setRowFixed(i, m_currentState.cellHeight);
                }

                /* Add or remove columns. */
                while(columns > usedColumns)
                {
                    m_layout->removeColumn();
                    --columns;
                }
                while(columns < usedColumns)
                {
                    m_layout->addFixedColumn(m_currentState.cellWidth);
                    ++columns;
                }

                /* Add or remove rows. */
                while(rows > usedRows)
                {
                    m_layout->removeRow();
                    --rows;
                }
                while(rows < usedRows)
                {
                    m_layout->addFixedRow(m_currentState.cellHeight);
                    ++rows;
                }
            }

            /* Reorganize visible items to correct grid layout slots. */
            {
                unsigned int i;
                unsigned int firstIndex = (m_currentState.beginIndex > m_currentState.keepAlive ? m_currentState.beginIndex - m_currentState.keepAlive : 0);
                unsigned int lastIndex = kzsMinU(m_currentState.endIndex + m_currentState.keepAlive, m_currentState.totalItemCount);
                unsigned int rangeSize = lastIndex - firstIndex;

                kzAssert(m_currentState.beginIndex <= m_currentState.endIndex);
                kzAssert(m_currentState.usedRows * m_currentState.usedColumns >= rangeSize);

                /* Set visible items. */
                m_listBox->updateVisibleRange(firstIndex, rangeSize);

                for(i = 0; i < rangeSize; ++i)
                {
                    unsigned int index = firstIndex + i;
                    unsigned int row = 0;
                    unsigned int column = 0;
                    switch(m_currentState.layoutDirection)
                    {
                        case GridLayoutConcept::GridDirectionRight:
                        {
                            row = i / m_currentState.usedColumns;
                            column = i % m_currentState.usedColumns;
                            break;
                        }
                        case GridLayoutConcept::GridDirectionDown:
                        {
                            row = i % m_currentState.usedRows;
                            column = i / m_currentState.usedRows;
                            break;
                        }
                        default:
                        {
                            kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Invalid enum value passed to KzuUiGridLayoutDirection in KzuGridLayoutPresenterData: value {} is out of valid range", m_currentState.layoutDirection));
                        }
                    }

                    ItemSharedPtr objectNode = getItem(index);

                    TLayout::setColumn(*objectNode, column);
                    TLayout::setRow(*objectNode, row);

                    /* Update visibility. */
                    {
                        bool visible = (index >= m_currentState.beginIndex && index < m_currentState.endIndex);
                        objectNode->setVisible(visible);
                    }
                }
            }

            /* Re-measure layout object because children may have been removed or added and we are already in the arrange phase. */
            {
                m_layout->invalidateMeasure();
                doRemeasure(*m_layout);
            }
        }

        /* Update transforms. */
        {
            const Vector2 skippedOffset = deduceSkippedOffset();
            Vector2 scrollOffset = m_currentState.scrollOffset;

            switch(layoutDirection)
            {
                case GridLayoutConcept::GridDirectionDown:
                {
                    scrollOffset -= skippedOffset;
                    scrollOffset.setY(0.0f);
                    break;
                }
                case GridLayoutConcept::GridDirectionRight:
                {
                    scrollOffset += skippedOffset * -TLayout::layoutUp();
                    scrollOffset.setX(0.0f);
                    break;
                }
                default:
                {
                    kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Invalid enum value passed to KzuUiGridLayoutDirection in KzuGridLayoutPresenterData: value {} is out of valid range", layoutDirection));
                }
            }

            updateRenderTransform(scrollOffset);
        }

        /* Calculate VisibleAmountInParent property for objects. */
        updateOffsetProperties();

        /* Catch old state. */
        m_oldState = m_currentState;

        /* Reconfigure scroll view. */
        updateScrollViewBounds();
    }

    void updateScrollViewBounds()
    {
        ScrollViewSharedPtr scrollView = m_listBox->getScrollView();

        switch (m_currentState.layoutDirection)
        {
            case GridLayoutConcept::GridDirectionRight:
            {
                scrollView->setAllowedScrollAxis(ScrollViewConcept::YAxis);
                break;
            }
            case GridLayoutConcept::GridDirectionDown:
            {
                scrollView->setAllowedScrollAxis(ScrollViewConcept::XAxis);
                break;
            }
            default:
            {
                kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Invalid enum value passed to grid presenter layout direction: value {} is out of valid range", m_currentState.layoutDirection));
            }
        }

        float scrollMinimumX;
        float scrollMaximumX;
        float scrollMinimumY;
        float scrollMaximumY;

        getScrollBounds(&scrollMinimumX, &scrollMaximumX, &scrollMinimumY, &scrollMaximumY);

        scrollView->setScrollBoundsX(scrollMinimumX, scrollMaximumX);
        scrollView->setScrollBoundsY(scrollMinimumY, scrollMaximumY);
    }

    /** Calculates properties VisibleAmountInParent and GridListBoxOffset for objects in the grid list box. */
    void updateOffsetProperties()
    {
        // TODO: this method uses layout width and so on, should use actualSize?
        // TODO: get from currentState?
        GridLayoutConcept::GridDirection layoutDirection = m_layout->getDirection();

        float beginOffset = m_listBox->getItemAreaBegin();
        float endOffset = m_listBox->getItemAreaEnd();

        unsigned int remainingObjects = m_layout->getChildCount();

        // TODO: this is repeated several times
        unsigned int firstIndex = (m_currentState.beginIndex > m_currentState.keepAlive ? m_currentState.beginIndex - m_currentState.keepAlive : 0);

        // TODO: called from previous function?
        Vector2 skippedOffset = deduceSkippedOffset();

        switch(layoutDirection)
        {
            case GridLayoutConcept::GridDirectionDown:
            {
                float layoutWidth = m_listBox->getWidth();
                float layoutBegin = layoutWidth * beginOffset;
                float layoutEnd = layoutWidth * endOffset;

                unsigned int columnCount = m_layout->getColumnCount();
                float currentOffset = m_currentState.scrollOffset.getX() - skippedOffset.getX();

                for(unsigned i = 0; i < columnCount && remainingObjects > 0; ++i)
                {
                    unsigned int columnItemCount = kzsMinU(m_currentState.totalRows, remainingObjects);
                    // TODO: forget much? the listbox knows the size
                    float columnWidth = m_layout->getActualColumnSize(i);

                    float gridOffset = (currentOffset + columnWidth * 0.5f) / layoutWidth;

                    float visibleAmountInParent = 1.0f;
                    visibleAmountInParent = kzsMinf(visibleAmountInParent, (currentOffset + columnWidth - layoutBegin) / columnWidth);
                    visibleAmountInParent = kzsMinf(visibleAmountInParent, (layoutEnd - currentOffset) / columnWidth);
                    visibleAmountInParent = kzsMaxf(visibleAmountInParent, 0.0f);

                    for(unsigned j = 0; j < columnItemCount; ++j)
                    {
                        unsigned int index = firstIndex + i * m_currentState.totalRows + j;
                        ItemSharedPtr item = getItem(index);

                        item->setVisibleAmountInParent(visibleAmountInParent);
                        item->setProperty(GridListBoxConcept::CalculatedOffsetProperty, gridOffset);
                    }

                    remainingObjects -= columnItemCount;
                    currentOffset += columnWidth;
                }
                break;
            }
            case GridLayoutConcept::GridDirectionRight:
            {
                float layoutHeight = m_listBox->getHeight();
                float layoutBegin = layoutHeight * beginOffset;
                float layoutEnd = layoutHeight * endOffset;

                unsigned int rowCount = m_layout->getRowCount();
                float currentOffset = -TLayout::layoutUp() * m_currentState.scrollOffset.getY() + skippedOffset.getY();

                for(unsigned i = 0; i < rowCount && remainingObjects > 0; ++i)
                {
                    unsigned int rowItemCount = kzsMinU(m_currentState.totalColumns, remainingObjects);
                    float rowHeight = m_layout->getActualRowSize(i);

                    float gridOffset = (currentOffset + rowHeight * 0.5f) / layoutHeight;

                    float visibleAmountInParent = 1.0f;
                    visibleAmountInParent = kzsMinf(visibleAmountInParent, (currentOffset + rowHeight - layoutBegin) / rowHeight);
                    visibleAmountInParent = kzsMinf(visibleAmountInParent, (layoutEnd - currentOffset) / rowHeight);
                    visibleAmountInParent = kzsMaxf(visibleAmountInParent, 0.0f);

                    for(unsigned j = 0; j < rowItemCount; ++j)
                    {
                        unsigned int index = firstIndex + i * m_currentState.totalColumns + j;
                        ItemSharedPtr item = getItem(index);

                        item->setVisibleAmountInParent(visibleAmountInParent);
                        item->setProperty(GridListBoxConcept::CalculatedOffsetProperty, gridOffset);
                    }

                    remainingObjects -= rowItemCount;
                    currentOffset += rowHeight;
                }
                break;
            }
            default:
            {
                kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Invalid enum value passed to KzuUiGridLayoutDirection in KzuGridLayoutPresenterData: value {} is out of valid range", m_currentState.layoutDirection));
            }
        }
    }

    /** Returns KZ_TRUE if presenter's layout state has changed. */
    bool isStateChanged()
    {
        State* current = &m_currentState;
        State* old = &m_oldState;

        bool changed = false;

        /* Detect if the layout state has changed. */

        if(!kzsFloatIsEqual(current->cellWidth, old->cellWidth) ||
            !kzsFloatIsEqual(current->cellHeight, old->cellHeight) ||
            current->usedColumns != old->usedColumns || current->usedRows != old->usedRows ||
            current->totalColumns != old->totalColumns || current->totalRows != old->totalRows ||
            current->beginIndex != old->beginIndex || current->endIndex != old->endIndex ||
            current->totalItemCount != old->totalItemCount ||
            current->keepAlive != old->keepAlive ||
            m_stateChanged)
        {
            // TODO: fix side effect
            m_stateChanged = false;
            changed = true;
        }

        return changed;
    }

    void getScrollBounds(float* out_scrollMinimumX, float* out_scrollMaximumX,
                         float* out_scrollMinimumY, float* out_scrollMaximumY) const
    {
        float layoutWidth = m_currentState.actualSize.getX();
        float layoutHeight = m_currentState.actualSize.getY();
        float beginOffset = m_listBox->getItemAreaBegin();
        float endOffset = m_listBox->getItemAreaEnd();

        /* TODO: Assign to output variables at end of function. */

        /* Maximum scroll values. */
        switch(m_currentState.layoutDirection)
        {
            case GridLayoutConcept::GridDirectionRight:
            {
                float totalSize = kzsMaxf(0.0f, (float)m_currentState.totalRows * m_currentState.cellHeight);
                float minimumOffset;
                float maximumOffset;

                if(TFinalClass::layoutUp() < 0.0f)
                {
                    minimumOffset = -totalSize + layoutHeight * endOffset;
                    maximumOffset = layoutHeight * beginOffset;

                    minimumOffset = kzsMinf(minimumOffset, maximumOffset);
                }
                else
                {
                    minimumOffset = -layoutHeight * beginOffset;
                    maximumOffset = totalSize - layoutHeight * endOffset;

                    maximumOffset = kzsMaxf(minimumOffset, maximumOffset);
                }

                *out_scrollMinimumX = 0.0f;
                *out_scrollMaximumX = 0.0f;
                *out_scrollMinimumY = minimumOffset;
                *out_scrollMaximumY = maximumOffset;
                break;
            }
            case GridLayoutConcept::GridDirectionDown:
            {
                float totalSize = kzsMaxf(0.0f, (float)m_currentState.totalColumns * m_currentState.cellWidth);

                float minimumOffset = -totalSize + layoutWidth * endOffset;
                float maximumOffset = layoutWidth * beginOffset;

                minimumOffset = kzsMinf(minimumOffset, maximumOffset);

                *out_scrollMinimumX = minimumOffset;
                *out_scrollMaximumX = maximumOffset;
                *out_scrollMinimumY = 0.0f;
                *out_scrollMaximumY = 0.0f;
                break;
            }
            default:
            {
                kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Invalid enum value passed to KzuUiGridLayoutDirection in KzuGridLayoutPresenterData: value {} is out of valid range. Defaults to KZU_GRID_LAYOUT_DIRECTION_RIGHT", m_currentState.layoutDirection));
                *out_scrollMinimumX = 0.0f;
                *out_scrollMaximumX = 0.0f;
                *out_scrollMinimumY = 0.0f;
                *out_scrollMaximumY = 0.0f;
            }
        }
    }

    /** Calculates how much offset is being skipped by skipping non-visible items. */
    Vector2 deduceSkippedOffset() const
    {
        Vector2 skippedOffset;
        unsigned int firstIndex = (m_currentState.beginIndex > m_currentState.keepAlive ? m_currentState.beginIndex - m_currentState.keepAlive : 0);

        switch(m_currentState.layoutDirection)
        {
            case GridLayoutConcept::GridDirectionRight:
            {
                unsigned int skipCount = firstIndex / m_currentState.usedColumns;

                skippedOffset = Vector2(0.0f, (float)skipCount * m_currentState.cellHeight);
                break;
            }
            case GridLayoutConcept::GridDirectionDown:
            {
                unsigned int skipCount = firstIndex / m_currentState.usedRows;

                skippedOffset = Vector2(-(float)skipCount * m_currentState.cellWidth, 0.0f);
                break;
            }
            default:
            {
                unsigned int skipCount = firstIndex / m_currentState.usedColumns;

                skippedOffset = Vector2(0.0f, (float)skipCount * m_currentState.cellHeight);

                kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Invalid enum value passed to KzuUiGridLayoutDirection in KzuGridLayoutPresenterData: value {} is out of valid range. Defaults to KZU_GRID_LAYOUT_DIRECTION_RIGHT", m_currentState.layoutDirection));
            }
        }

        return skippedOffset;
    }

#ifdef KANZI_FEATURE_3D
    // TODO: move outside
    static void doUpdateRenderTransform(Node3D& node, Vector2 scroll)
    {
        node.setRenderTransformation(SRTValue3D::createTranslation(Vector3(scroll.getX(), scroll.getY(), 0.0f)));
    }
#endif

    static void doUpdateRenderTransform(Node2D& node, Vector2 scroll)
    {
        node.setRenderTransformation(SRTValue2D::createTranslation(Vector2(scroll.getX(), scroll.getY())));
    }

    /** Updates scroll transform of layout. */
    void updateRenderTransform(Vector2 scroll)
    {
        doUpdateRenderTransform(*m_layout, scroll);
    }

    // TODO: highly inefficient function, the presenter knows the items and indices
    ItemSharedPtr getItem(size_t presenterIndex) const
    {
        for (typename TLayout::ChildConstIterator i = m_layout->beginChildren(), end = m_layout->endChildren(); i != end; ++i)
        {
            ItemSharedPtr item = dynamic_pointer_cast<TItemClass>(*i);
            kzAssert(item);
            if (item->getPresenterIndex() == presenterIndex)
            {
                return item;
            }
        }

        kzThrowException(runtime_error("Logic"));
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

    void snap(Vector2 position, Vector2 /*direction*/, bool /*changeTarget*/, Vector2* out_position, int* out_itemIndex)
    {
        /* Bounds for snapping coordinates. */
        float snapMinimumX;
        float snapMaximumX;
        float snapMinimumY;
        float snapMaximumY;

        getScrollBounds(&snapMinimumX, &snapMaximumX, &snapMinimumY, &snapMaximumY);

        /* Get snap position. */
        float snapPositionX = position.getX();
        float snapPositionY = position.getY();
        snapPositionX = kzsClampf(snapPositionX, snapMinimumX, snapMaximumX);
        snapPositionY = kzsClampf(snapPositionY, snapMinimumY, snapMaximumY);

        int resultIndex = KZU_UI_LIST_BOX_NO_ITEM;

        if(out_position)
        {
            *out_position = Vector2(snapPositionX, snapPositionY);
        }

        if(out_itemIndex)
        {
            *out_itemIndex = resultIndex;
        }
    }

    void setScroll(Vector2 scroll)
    {
        m_currentState.scrollOffset = scroll;
        m_listBox->invalidateMeasure();
    }

    Vector2 bringItemCenter(size_t selection) const
    {
        float scrollX;
        float scrollY;

        float scrollMinimumX;
        float scrollMaximumX;
        float scrollMinimumY;
        float scrollMaximumY;

        /* Calculate scroll value. */
        switch(m_currentState.layoutDirection)
        {
            case GridLayoutConcept::GridDirectionRight:
            {
                unsigned int row = selection / kzsMaxU(1, m_currentState.usedColumns);
                scrollX = 0.0f;
                scrollY = TFinalClass::layoutUp() * (static_cast<float>(row + 0.5f) * m_currentState.cellHeight - m_currentState.actualSize.getY() * 0.5f);
                break;
            }
            case GridLayoutConcept::GridDirectionDown:
            {
                unsigned int column = selection / kzsMaxU(1, m_currentState.usedRows);
                scrollX = -(float)(column + 0.5f) * m_currentState.cellWidth + m_currentState.actualSize.getX() * 0.5f;
                scrollY = 0.0f;
                break;
            }
            default:
            {
                unsigned int row = selection / kzsMaxU(1, m_currentState.usedColumns);
                scrollX = 0.0f;
                scrollY = (float)(row + 0.5f) * m_currentState.cellHeight - m_currentState.actualSize.getY() * 0.5f;

                kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Invalid enum value passed to KzuUiGridLayoutDirection in KzuGridLayoutPresenterData: value {} is out of valid range. Defaults to KZU_GRID_LAYOUT_DIRECTION_RIGHT", m_currentState.layoutDirection));
            }
        }

        /* Limit to snapping bounds. */
        getScrollBounds(&scrollMinimumX, &scrollMaximumX, &scrollMinimumY, &scrollMaximumY);

        scrollX = kzsClampf(scrollX, scrollMinimumX, scrollMaximumX);
        scrollY = kzsClampf(scrollY, scrollMinimumY, scrollMaximumY);

        return Vector2(scrollX, scrollY);
    }

    /// Gets the number of columns that are currently displayed.
    /// \return Returns the number of columns.
    size_t getColumnCount() const
    {
        return m_currentState.usedColumns;
    }

    /// Gets the number of rows that are currently displayed.
    /// \return Returns the number of rows.
    size_t getRowCount() const
    {
        return m_currentState.usedRows;
    }

private:

    /** State for grid layout presenter's layout. */
    struct State
    {
        typename TLayout::LayoutVectorType actualSize; /**< Maximum size for the grid layout. */
        GridLayoutConcept::GridDirection layoutDirection; /**< Direction of layouting. */

        float cellWidth; /**< Width of grid cells. */
        float cellHeight; /**< Height of grid cells. */

        unsigned int usedColumns; /**< Number of columns that are currently displayed. */
        unsigned int usedRows; /**< Number of rows that are currently displayed. */

        unsigned int fittingColumns; /**< Number of columns that can be fitted in layout. */
        unsigned int fittingRows; /**< Number of rows that can be fitted in layout. */

        unsigned int totalColumns; /**< Total number of columns required. */
        unsigned int totalRows; /**< Total number of rows required. */

        unsigned int beginIndex; /**< Index of first currently displayed item. */
        unsigned int endIndex; /**< Index of first item not currently displayed. */
        unsigned int totalItemCount; /**< Total item count of list box. */

        unsigned int keepAlive; /**< Number of items that are made invisible before they are virtualized. */

        Vector2 scrollOffset; /**< Scroll offset applied to items. */

        State()
        {
            layoutDirection = GridLayoutConcept::GridDirectionRight;
            cellWidth = 0.0f;
            cellHeight = 0.0f;
            usedColumns = 0;
            usedRows = 0;
            fittingColumns = 0;
            fittingRows = 0;
            totalColumns = 0;
            totalRows = 0;
            beginIndex = 0;
            endIndex = 0;
            totalItemCount = 0;
            keepAlive = 0;
            scrollOffset = Vector2(0.0f, 0.0f);
        }
    };

    LayoutSharedPtr m_layout;
    TFinalClass* m_listBox;

    State m_currentState; /**< Current layouting parameters. */
    State m_oldState; /**< Old layouting parameters. */

    bool m_stateChanged; /**< Does grid layout need to be updated. */
};

}

#endif
