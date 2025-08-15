// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GRID_LAYOUT_CONCEPT_HPP
#define KZ_GRID_LAYOUT_CONCEPT_HPP

#include <kanzi/ui/ui_api.hpp>

#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core/cpp/vector.hpp>

namespace kanzi
{


/// GridConcept is a base class for the nodes that implement layout that arranges items in a grid.
///
/// Grid nodes arrange their items in a grid of cells. The grid node contains the definition for grid:
/// the number and size of rows and columns. The grid items contain the coordinates
/// of their cell, and the number of cells the item spans.
class KANZI_UI_API GridLayoutConcept
{
public:

    /// Size mode for a grid row or a column.
    enum RowColumnSizeMode
    {
        RowColumnSizeModeUser     = 0, ///< Row or column size is fixed.
        RowColumnSizeModeAuto     = 1, ///< Row or column size is the size of the largest item on this row or column.
        RowColumnSizeModeWeighted = 2  ///< Row or column size is a proportion of the whole grid size. The proportion size depends on the relative weight of the row or column compared to weights of other rows or columns.
    };

    /// Direction of layout of grid layout. Items which don't have fixed #ColumnProperty and #RowProperty are laid out in this direction.
    enum GridDirection
    {
        GridDirectionRight = 0, ///< Layout first right, then down.
        GridDirectionDown  = 1  ///< Layout first down, then right.
    };

    /// \name Properties
    /// \{
#include "grid_layout_concept_properties.h"
    /// \}

    KZ_MIXIN_METACLASS_BEGIN(GridLayoutConcept, "Kanzi.GridLayoutConcept")
        KZ_METACLASS_PROPERTY_TYPE(DirectionProperty)
        KZ_METACLASS_PROPERTY_TYPE(ColumnDefinitionsProperty)
        KZ_METACLASS_PROPERTY_TYPE(RowDefinitionsProperty)
        KZ_METACLASS_ATTACHED_PROPERTY_TYPE(ColumnProperty)
        KZ_METACLASS_ATTACHED_PROPERTY_TYPE(ColumnSpanProperty)
        KZ_METACLASS_ATTACHED_PROPERTY_TYPE(RowProperty)
        KZ_METACLASS_ATTACHED_PROPERTY_TYPE(RowSpanProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Definition for the size and position of a single row or column.
    struct RowColumnDefinition
    {
        /// Constructor.
        /// \param mode Row or column mode.
        /// \param userSize Row or column size.
        /// \param maxSize Row or column maximum size.
        /// \param offset Row or column offset.
        explicit RowColumnDefinition(RowColumnSizeMode mode, float userSize, float maxSize, float offset):
            m_mode(mode),
            m_userSize(userSize),
            m_maxSize(maxSize),
            m_offset(offset)
        {
        }

        RowColumnSizeMode m_mode; /// Layout size mode.
        float m_userSize; /// Fixed size or weight of the row or column, depending on the layout mode.
        float m_maxSize; /// Maximum size of an item on this row or column.
        float m_offset; /// Offset of this row or column.
    };

    /// Container type for row and column definitions.
    typedef vector<RowColumnDefinition> RowColumnDefinitionContainer;

    /// Calculates grid row or column definition maximum sizes for weighted rows or columns.
    /// \param definitions Row or column definitions.
    /// \param weightMultiplier The size of a single weight unit.
    static void calculateWeightedSizes(RowColumnDefinitionContainer& definitions, float weightMultiplier);

    /// Calculates grid row or column definition offsets according to current maximum sizes.
    /// \param definitions Row or column definitions.
    static void calculateOffsets(RowColumnDefinitionContainer& definitions);

    /// Calculates the sum of row or column definition's maximum sizes.
    /// \param definitions Row or column definitions.
    /// \return Sum of row or column maximum sizes.
    static float accumulateMaximumSize(const RowColumnDefinitionContainer& definitions);

    /// Parse grid row or column definitions from property string.
    /// \param definitionCollection Property string describing grid rows or columns. See RowDefinitionsProperty for format definition.
    /// \param definitions Output parameter that will hold the row or column definitions.
    static void parseRowColumnDefinitions(const string& definitionCollection, RowColumnDefinitionContainer& definitions);
};

/// GridConceptImplementation is an abstract class for implementing grid concept.
template<typename TBaseClass, typename TDerivedClass>
class KANZI_UI_TEMPLATE_API GridLayoutConceptImpl: public TBaseClass, public GridLayoutConcept
{
    TDerivedClass* getThisObject();

    const TDerivedClass* getThisObject() const;

public:

    KZ_TEMPLATE_METACLASS_BEGIN(GridLayoutConceptImpl, TBaseClass)
        KZ_METACLASS_MIXIN(GridLayoutConcept)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Gets the column of an item.
    /// \param item A node that is or can become an item of a grid.
    /// \return Returns the value of the column property.
    static unsigned int getColumn(const Node& item);

    /// Sets the column of an item.
    /// \param item A node that is or can become an item of a grid.
    /// \param column Column of the item.
    static void setColumn(Node& item, unsigned int column);

    /// Gets the column span of an item.
    /// \param item A node that is or can become an item of a grid.
    /// \return Returns the value of the column span property.
    static unsigned int getColumnSpan(const Node& item);

    /// Sets the column span of an item.
    /// \param item A node that is or can become an item of a grid.
    /// \param columnSpan Column span of the item.
    static void setColumnSpan(Node& item, unsigned int columnSpan);

    /// Gets the row of an item.
    /// \param item A node that is or can become an item of a grid.
    /// \return Returns the value of the row property.
    static unsigned int getRow(const Node& item);

    /// Sets the row of an item.
    /// \param item A node that is or can become an item of a grid.
    /// \param row Row of the item.
    static void setRow(Node& item, unsigned int row);

    /// Gets the row span of an item.
    /// \param item A node that is or can become an item of a grid.
    /// \return Returns the value of the row span property.
    static unsigned int getRowSpan(const Node& item);

    /// Sets the row span of an item.
    /// \param item A node that is or can become an item of a grid.
    /// \param rowSpan Row span of the item.
    static void setRowSpan(Node& item, unsigned int rowSpan);

    /// Gets the number of rows in the grid.
    /// \return The number of rows in the grid.
    unsigned int getRowCount() const;

    /// Gets the number of columns in the grid.
    /// \return The number of columns in the grid.
    unsigned int getColumnCount() const;

    /// Adds a new fixed size row to the grid.
    /// \param size Size of the row.
    void addFixedRow(float size);

    /// Adds a new automatic size row to the grid.
    void addAutomaticRow();

    /// Adds a new weighted size row to the grid.
    /// \param weight Weight of the row.
    void addWeightedRow(float weight);

    /// Adds a new fixed size column to the grid.
    /// \param size Size of the column.
    void addFixedColumn(float size);

    /// Adds a new automatic size column to the grid.
    void addAutomaticColumn();

    /// Adds a new weighted size column to the grid.
    /// \param weight Weight of the column.
    void addWeightedColumn(float weight);

    /// Removes the last row from the grid.
    void removeRow();

    /// Removes the last column from the grid.
    void removeColumn();

    /// Sets a grid row to a fixed size.
    /// \param index Index of the row, starting from 0.
    /// \param size Size of the row.
    void setRowFixed(unsigned int index, float size);

    /// Sets a grid row to automatic size.
    /// \param index Index of the row, starting from 0.
    void setRowAutomatic(unsigned int index);

    /// Sets a grid row to a weighted size.
    /// \param index Index of the row, starting from 0.
    /// \param weight Weight of the row.
    void setRowWeighted(unsigned int index, float weight);

    /// Sets a grid column to a fixed size.
    /// \param index Index of the column, starting from 0.
    /// \param size Size of the column.
    void setColumnFixed(unsigned int index, float size);

    /// Sets a grid column to automatic size.
    /// \param index Index of the row, starting from 0.
    void setColumnAutomatic(unsigned int index);

    /// Sets a grid column to a weighted size.
    /// \param index Index of the column, starting from 0.
    /// \param weight Weight of the column.
    void setColumnWeighted(unsigned int index, float weight);

    /// Gets the last calculated value for a grid row size. The value is recalculated whenever the grid is layouted.
    /// \param index Index of the row, starting from 0.
    float getActualRowSize(unsigned int index) const;

    /// Gets the last calculated value for a grid column size. The value is recalculated whenever the grid is layouted.
    /// \param index Index of the column, starting from 0.
    float getActualColumnSize(unsigned int index) const;

    /// Gets the Direction property.
    GridDirection getDirection() const;

    /// Sets the Direction property.
    void setDirection(GridDirection value);

    /// Gets the ColumnDefinitions property.
    string getColumnDefinitions() const;

    /// Sets the ColumnDefinitions property.
    void setColumnDefinitions(string_view value);

    /// Gets the RowDefinitions property.
    string getRowDefinitions() const;

    /// Sets the RowDefinitions property.
    void setRowDefinitions(string_view value);

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    GridLayoutConceptImpl(Domain* domain, string_view name);

    /// TBaseClass::arrangeOverride() implementation.
    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// Information used to store the state between function calls when locating objects.
    struct GridObjectLocationWorkspace
    {
        explicit GridObjectLocationWorkspace(const GridLayoutConceptImpl& grid):
        direction(grid.getDirection()),
            columnCount(grid.getColumnCount()),
            rowCount(grid.getRowCount()),
            row(0),
            column(0)
        {
        }

        GridDirection direction; ///< Direction of layout.
        unsigned int columnCount;      ///< Column count of layout.
        unsigned int rowCount;         ///< Row count of layout.
        unsigned int row;              ///< Row of the next location.
        unsigned int column;           ///< Column of the next location.
    };

    /// Decides the row and column for the next item in the grid. Requires a workspace to store state between calls.
    /// \param node Next item to position.
    /// \param workspace Stores state from previous calls to this function. Updated during the call.
    /// \param out_row Row of the item.
    /// \param out_column Column of the item.
    static void getNextItemLocation(const Node& node, GridObjectLocationWorkspace& workspace, unsigned int& out_row, unsigned int& out_column);

    /// Gets the span of a grid item.
    static void getSpan(const Node& item, unsigned int& rowSpan, unsigned int& columnSpan);

protected:

     /// Row definitions.
    RowColumnDefinitionContainer m_rows;

     /// Column definitions.
    RowColumnDefinitionContainer m_columns;

     /// Total weights of weighted rows.
    float m_rowWeights;

     /// Total weight of weighted columns.
    float m_columnWeights;

     /// Total size of all rows.
    float m_accumulatedRowSize;

     /// Total size of all columns.
    float m_accumulatedColumnSize;
};

}


#endif
