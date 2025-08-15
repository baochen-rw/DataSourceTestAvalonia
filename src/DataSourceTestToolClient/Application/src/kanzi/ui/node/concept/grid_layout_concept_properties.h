// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for GridLayoutConcept.
// Do not include this file directly. Include grid_layout_concept.hpp instead.



    /// Direction property.
    /// Defines the grid primary layouting direction. This property specifies how to choose the row and column for items without explicit grid row and column properties.
    /// The default value is GridLayoutConcept::GridDirectionRight.
    /// \see setDirection(), getDirection()
    static PropertyType<GridLayoutConcept::GridDirection> DirectionProperty;


    /// ColumnDefinitions property.
    /// Defines the columns of the grid. See #RowDefinitionsProperty.
    /// The default value is "".
    /// \see setColumnDefinitions(), getColumnDefinitions()
    static PropertyType<string> ColumnDefinitionsProperty;


    /// RowDefinitions property.
    /// Defines the rows of the grid. The string has a special format of "[*f|f];[*f|f];...", where each row definition is separated by a ';' character, 'f' signifies a float number and '*' signifies a weighted (proportional) height. For example, "1.0;2.0;3.0;" defines three rows with heights of 1.0, 2.0 and 3.0 respectively. ";;" specifies two rows that all have heights calculated from their content. "*1.0;*2.0;*3.0;" specifies three rows where the first row has 1/6 of the total height (#HeightProperty), the second 2/6 and the third 3/6.
    /// The default value is "".
    /// \see setRowDefinitions(), getRowDefinitions()
    static PropertyType<string> RowDefinitionsProperty;


    /// Column property.
    /// Defines the column of an item in a grid, starting from 0.
    /// The default value is 0.
    /// \see setColumn(), getColumn()
    static PropertyType<int> ColumnProperty;


    /// ColumnSpan property.
    /// Defines how many columns this grid item spans.
    /// The default value is 1.
    /// \see setColumnSpan(), getColumnSpan()
    static PropertyType<int> ColumnSpanProperty;


    /// Row property.
    /// Defines the row of an item in a grid, starting from 0.
    /// The default value is 0.
    /// \see setRow(), getRow()
    static PropertyType<int> RowProperty;


    /// RowSpan property.
    /// Defines how many rows this grid item spans.
    /// The default value is 1.
    /// \see setRowSpan(), getRowSpan()
    static PropertyType<int> RowSpanProperty;


