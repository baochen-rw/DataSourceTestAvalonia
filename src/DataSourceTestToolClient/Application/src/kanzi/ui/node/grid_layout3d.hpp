// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_UI_GRID_LAYOUT_H
#define KZU_UI_GRID_LAYOUT_H


#include <kanzi/core.ui/node/node3d.hpp>
#include <kanzi/ui/node/concept/grid_layout_concept.hpp>


namespace kanzi
{

class GridLayout3D;


/// GridLayout3D shared pointer.
typedef shared_ptr<GridLayout3D> GridLayout3DSharedPtr;

/// Grid Layout 3D arranges 3D items in a grid.
///
/// You can let the grid layout arrange the items automatically from the top-left towards the
/// bottom-right corner, or manually assign each item to a specific row and column in a grid.
///
/// Note that the depth of the grid is the maximum depth for all the items in a grid.
///
/// When you want to manually assign items to a specific row and cell in a grid layout,
/// use setRow() and setColumn().
///
/// When you let a grid layout to arrange items automatically, you can set the direction in
/// which the grid layout arranges its items. For example, when you set the #DirectionProperty
/// property to #GridDirectionDown, grid layout first places the items in the rows of
/// the first column. When all the rows in the first column are full, grid layout
/// starts placing the items in the rows of the second column, and so on. See setDirection().
///
/// When you create columns and rows in a grid layout you can specify how the grid layout
/// calculates their size:
/// - You can let grid layout automatically calculate the size of the column and row based on
/// the size of the largest item in that column and row. See addAutomaticRow(),
/// addAutomaticColumn(), setRowAutomatic(), and setColumnAutomatic().
/// - You can set the exact size of a column and row. See addFixedRow(), addFixedColumn(),
/// setRowFixed(), and setColumnFixed().
/// - You can set the size of the column and row in proportion to the remaining size of other
/// columns and rows that use this same setting, and the size of the entire grid layout.
/// See addWeightedRow(), addWeightedColumn(), setRowWeighted(), and setColumnWeighted().
///
/// For each cell in a grid layout you can set the number of columns and rows it spans. See
/// setColumnSpan() and setRowSpan().
///
// TODO Explain how the grid size is calculated based on its rows and columns, and how
// child nodes are separate from the layout (so that when you remove the row or column,
// you also have to remove the child nodes there).
///
/// \see For a 2D grid component, see GridLayout2D.
///
/// Examples
/// ----
///
/// To create a Grid Layout 3D with two columns and two rows with automatic cell size, and
/// set the grid to arrange the items in the grid columns from top to bottom:
/// \snippet test_grid_layout3d.cpp Direction down
///
/// To create a Grid Layout 3D with two columns and three rows whose sizes the grid calculates
/// in proportion to the sizes of other columns and rows in the grid. For each item in the
/// grid manually set which cells in the grid it occupies:
/// \snippet test_grid_layout3d.cpp Weighted cells
///
/// To create a Grid Layout 3D with two columns and two rows, using both fixed and automatic cell size.
/// By default the grid automatically sets which cells the items occupy:
/// \snippet test_grid_layout3d.cpp Fixed and automatic cells

class KANZI_UI_API GridLayout3D : public GridLayoutConceptImpl<Node3D, GridLayout3D>
{
public:

    typedef GridLayoutConceptImpl<Node3D, GridLayout3D> ConceptClass;

    /// Creates a grid layout node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name Name of the trajectory layout.
    /// \return The created node.
    static GridLayout3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(GridLayout3D, ConceptClass, "Kanzi.GridLayout3D")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit GridLayout3D(Domain* domain, string_view name);

    /// Node3d::measureOverride() implementation.
    virtual Vector3 measureOverride(Vector3 availableSize) KZ_OVERRIDE;

    /// Node3d::arrangeOverride() implementation.
    virtual void arrangeOverride(Vector3 actualSize) KZ_OVERRIDE;
};

}

#endif

#endif
