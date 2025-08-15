// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_GRID_LIST_BOX3D_HPP
#define KZ_GRID_LIST_BOX3D_HPP

#include <kanzi/ui/node/concept/grid_list_box.hpp>
#include <kanzi/ui/node/concept/list_box.hpp>
#include <kanzi/ui/node/concept/list_box/list_box_grid_presenter.hpp>
#include <kanzi/ui/node/grid_layout3d.hpp>
#include <kanzi/ui/node/scroll_view3d.hpp>
#include <kanzi/ui/node/concept/list_box/list_box_item_container_generator.hpp>


namespace kanzi
{

class GridListBox3D;

typedef shared_ptr<GridListBox3D> GridListBox3DSharedPtr;


class KANZI_UI_API GridListBox3DTraits
{
public:
    typedef ScrollView3D TScrollViewClass;
    typedef Node3D TItemClass;
    typedef ListBoxItemContainer3D TItemContainerClass;
    typedef ListBoxGridPresenter<GridListBox3D, GridLayout3D, ListBoxItemContainer3D, ScrollView3D> TPresenterClass;
    typedef ListBoxItemGenerator3D TItemGeneratorClass;
    typedef ListBoxItemContainerGenerator3D TItemContainerGeneratorClass;
};

/// Represents a node that layouts its list of 3D items in a grid.
///
/// Each cell in the grid has equal size that must be specified by setting the #CellWidthProperty and #CellHeightProperty
/// to the list box. The number of rows and columns is specified by setting the size of the list box: the list box
/// displays as many cells as fits to the its boundaries.
///
/// Items in the cells that don't fit to the grid area are made invisible. The grid list box can be scrolled with user input
/// to display more items. All items can be temporarily dragged outside the grid area, but when the user is not giving input,
/// the list box scrolls the items back to the edge of the grid.
///
/// To handle input, internally the list box uses ScrollView3D. In order for the input to work, the list box
/// must be placed in front of the camera in such orientation that the scroll plane is perpendicular to the
/// camera view ray. In addition, the list box size must be specified as the scroll view uses that area to collect
/// input. To configure the scroll view, the scroll view properties set to the list box are forwarded to the scroll view.
///
/// \see For general documentation about list boxes, see ListBoxConceptImpl.
///
/// Examples
/// ----
///
/// To create a Grid List Box 3D:
/// \snippet test_grid_list_box3d.cpp example
///
/// To configure the grid area:
/// \snippet test_grid_list_box3d.cpp grid size
///
/// To add items to the list box:
/// \snippet test_grid_list_box3d.cpp items example
class KANZI_UI_API GridListBox3D : public ListBoxConceptImpl<Node3D, GridListBox3D, GridListBox3DTraits>, public GridListBoxConcept
{
    typedef ListBoxConceptImpl<Node3D, GridListBox3D, GridListBox3DTraits> ConceptClass;

public:

    /// Creates a grid listbox node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name Name of the node.
    static GridListBox3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(GridListBox3D, ConceptClass, "Kanzi.GridListBox3D")
        KZ_METACLASS_MIXIN(GridListBoxConcept)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Gets the value of #DirectionProperty.
    /// \see setDirection()
    GridDirection getDirection() const { return getProperty(DirectionProperty); }

    /// Sets the value of #DirectionProperty.
    /// \see getDirection()
    void setDirection(GridDirection value) { setProperty(DirectionProperty, value); }


    /// Gets the value of #CellWidthProperty.
    /// \see setCellWidth()
    float getCellWidth() const { return getProperty(CellWidthProperty); }

    /// Sets the value of #CellWidthProperty.
    /// \see getCellWidth()
    void setCellWidth(float value) { setProperty(CellWidthProperty, value); }


    /// Gets the value of #CellHeightProperty.
    /// \see setCellHeight()
    float getCellHeight() const { return getProperty(CellHeightProperty); }

    /// Sets the value of #CellHeightProperty.
    /// \see getCellHeight()
    void setCellHeight(float value) { setProperty(CellHeightProperty, value); }

    /// Gets the value of #ItemAreaBeginProperty.
    /// \see setItemAreaBegin()
    float getItemAreaBegin() const { return getProperty(ItemAreaBeginProperty); }

    /// Sets the value of #ItemAreaBeginProperty.
    /// \see getItemAreaBegin()
    void setItemAreaBegin(float value) { setProperty(ItemAreaBeginProperty, value); }

    /// Gets the value of #ItemAreaEndProperty.
    /// \see setItemAreaEnd()
    float getItemAreaEnd() const { return getProperty(ItemAreaEndProperty); }

    /// Sets the value of #ItemAreaEndProperty.
    /// \see getItemAreaEnd()
    void setItemAreaEnd(float value) { setProperty(ItemAreaEndProperty, value); }

    /// Gets the value of #ScrollPositionProperty.
    /// \see setScrollPosition()
    Vector2 getScrollPosition() const { return getProperty(ScrollPositionProperty); }

    /// Gets the value of #ScrollTargetPositionProperty.
    /// \see setScrollTargetPosition()
    Vector2 getScrollTargetPosition() const { return getProperty(ScrollTargetPositionProperty); }

    /// Gets the value of #ScrollSpeedProperty.
    /// \see setScrollSpeed()
    Vector2 getScrollSpeed() const { return getProperty(ScrollSpeedProperty); }

    /// Gets the value of #ScrollingProperty.
    /// \see setScrolling()
    bool isScrolling() const { return getProperty(ScrollingProperty); }

protected:

    explicit GridListBox3D(Domain* domain, string_view name);

    void initialize();

    void setInitialScrollPosition();

    virtual void onAttached() KZ_OVERRIDE;

private:

    ScrollView3DSharedPtr m_scrollView;
    GridLayout3DSharedPtr m_layout;
    ConceptClass::PresenterSharedPtr m_presenter;
};


}
#endif

#endif
