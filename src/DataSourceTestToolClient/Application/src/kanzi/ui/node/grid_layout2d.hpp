// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_GRID_LAYER_H
#define KZU_GRID_LAYER_H

#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/ui/node/concept/grid_layout_concept.hpp>

namespace kanzi
{

// Forward declaration.
class GridLayout2D;

/// GridLayout2D shared pointer.
typedef shared_ptr<GridLayout2D> GridLayout2DSharedPtr;

/// Grid Layout 2D arranges 2D items in a grid. You can let the grid layout arrange the items
/// automatically from the top-left towards the bottom-right corner, or manually assign each
/// item to a specific row and column in a grid.
///
/// When you want to manually assign items to a specific row and cell in a grid layout,
/// use setRow() and setColumn().
///
/// When you let grid layout arrange items automatically, you can set the direction in
/// which the grid arranges its items. For example, when you set the #DirectionProperty
/// property to #GridDirectionDown, Grid Layout 2D first places the items in the rows of
/// the first column. When all the rows in the first column are full, Grid Layout 2D
/// starts placing the items in the rows of the second column, and so on. See setDirection().
///
/// When you create columns and rows in a grid layout you can specify how the grid layout
/// calculates their size:
/// - You can let the grid layout automatically calculate the size of the column and row based on
/// the size of the largest item in that column and row. See addAutomaticRow(),
/// addAutomaticColumn(), setRowAutomatic(), setColumnAutomatic().
/// - You can set the exact size of a column and row. See addFixedRow(), addFixedColumn(),
/// setRowFixed(), setColumnFixed().
/// - You can set the size of the column and row in proportion to the remaining size of other
/// columns and rows that use this same setting, and the size of the entire grid layout.
/// See addWeightedRow(), addWeightedColumn(), setRowWeighted(), setColumnWeighted().
///
/// For each cell in a grid layout you can set the number of columns and rows it spans. See
/// setColumnSpan() and setRowSpan().
///
// TODO Explain how the grid size is calculated based on its rows and columns, and how
// child nodes are separate from the layout (so that when you remove the row or column,
// you also have to remove the child nodes there).
///
/// \see For a 3D grid component, see GridLayout3D.
///
/// Examples
/// ----
///
/// To create a Grid Layout 2D with two columns and two rows with automatic cell size, and
/// set the grid to arrange the items in the grid columns from top to bottom:
/// \snippet test_grid_layout2d.cpp Direction down
///
/// To create a Grid Layout 2D with two columns and two rows, using both fixed and automatic cell size.
/// By default the grid automatically sets which cells the items occupy:
/// \snippet test_grid_layout2d.cpp Fixed and automatic cells
///
/// To create a Grid Layout 2D with two columns and three rows whose sizes the grid calculates
/// in proportion to the sizes of other columns and rows in the grid. For each item in the
/// grid manually set which cells in the grid it occupies:
/// \snippet test_grid_layout2d.cpp Weighted cells
class KANZI_UI_API GridLayout2D: public GridLayoutConceptImpl<Node2D, GridLayout2D>
{
public:

    typedef GridLayoutConceptImpl<Node2D, GridLayout2D> ConceptClass;

    /// Creates a GridLayout2D node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    /// \return The created node.
    static GridLayout2DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(GridLayout2D, ConceptClass, "Kanzi.GridLayout2D")
    KZ_METACLASS_END()

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit GridLayout2D(Domain* domain, string_view name);

    /// KzuLayer::measure() implementation.
    virtual Vector2 measureOverride(Vector2 availableSize) KZ_OVERRIDE;

    /// KzuLayer::arrange() implementation.
    virtual void arrangeOverride(Vector2 actualSize) KZ_OVERRIDE;

private:

    /// Class default value for ClipChildrenProperty.
    ClassPropertyDefaultValue<bool> m_clipChildrenClassDefaultValue;
};

}

#endif
