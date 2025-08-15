// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GRID_LAYOUT_CONCEPT_IMPL_HPP
#define KZ_GRID_LAYOUT_CONCEPT_IMPL_HPP

#include "grid_layout_concept.hpp"


namespace kanzi
{

template<typename TBaseClass, typename TDerivedClass>
TDerivedClass* GridLayoutConceptImpl<TBaseClass, TDerivedClass>::getThisObject()
{
    return static_cast<TDerivedClass*>(this);
}

template<typename TBaseClass, typename TDerivedClass>
const TDerivedClass* GridLayoutConceptImpl<TBaseClass, TDerivedClass>::getThisObject() const
{
    return static_cast<const TDerivedClass*>(this);
}

template<typename TBaseClass, typename TDerivedClass>
unsigned int GridLayoutConceptImpl<TBaseClass, TDerivedClass>::getColumn(const Node& item)
{
    return static_cast<unsigned int>(item.getProperty(ColumnProperty));
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::setColumn(Node& item, unsigned int column)
{
    item.setProperty(ColumnProperty, static_cast<int>(column));
}

template<typename TBaseClass, typename TDerivedClass>
unsigned int GridLayoutConceptImpl<TBaseClass, TDerivedClass>::getColumnSpan(const Node& item)
{
    return static_cast<unsigned int>(item.getProperty(ColumnSpanProperty));
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::setColumnSpan(Node& item, unsigned int columnSpan)
{
    item.setProperty(ColumnSpanProperty, static_cast<int>(columnSpan));
}

template<typename TBaseClass, typename TDerivedClass>
unsigned int GridLayoutConceptImpl<TBaseClass, TDerivedClass>::getRow(const Node& item)
{
    return static_cast<unsigned int>(item.getProperty(RowProperty));
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::setRow(Node& item, unsigned int row)
{
    item.setProperty(RowProperty, static_cast<int>(row));
}

template<typename TBaseClass, typename TDerivedClass>
unsigned int GridLayoutConceptImpl<TBaseClass, TDerivedClass>::getRowSpan(const Node& item)
{
    return static_cast<unsigned int>(item.getProperty(RowSpanProperty));
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::setRowSpan(Node& item, unsigned int rowSpan)
{
    item.setProperty(RowSpanProperty, static_cast<int>(rowSpan));
}

template<typename TBaseClass, typename TDerivedClass>
unsigned int GridLayoutConceptImpl<TBaseClass, TDerivedClass>::getRowCount() const
{
    return m_rows.size();
}

template<typename TBaseClass, typename TDerivedClass>
unsigned int GridLayoutConceptImpl<TBaseClass, TDerivedClass>::getColumnCount() const
{
    return m_columns.size();
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::addFixedRow(float size)
{
    m_rows.push_back(RowColumnDefinition(RowColumnSizeModeUser, size, 0.0f, 0.0f));
    getThisObject()->invalidateMeasure();
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::addAutomaticRow()
{
    m_rows.push_back(RowColumnDefinition(RowColumnSizeModeAuto, 0.0f, 0.0f, 0.0f));
    getThisObject()->invalidateMeasure();
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::addWeightedRow(float weight)
{
    m_rows.push_back(RowColumnDefinition(RowColumnSizeModeWeighted, weight, 0.0f, 0.0f));
    getThisObject()->invalidateMeasure();
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::addFixedColumn(float size)
{
    m_columns.push_back(RowColumnDefinition(RowColumnSizeModeUser, size, 0.0f, 0.0f));
    getThisObject()->invalidateMeasure();
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::addAutomaticColumn()
{
    m_columns.push_back(RowColumnDefinition(RowColumnSizeModeAuto, 0.0f, 0.0f, 0.0f));
    getThisObject()->invalidateMeasure();
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::addWeightedColumn(float weight)
{
    m_columns.push_back(RowColumnDefinition(RowColumnSizeModeWeighted, weight, 0.0f, 0.0f));
    getThisObject()->invalidateMeasure();
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::removeRow()
{
    kzThrowIfErrorTestMessage(!m_rows.empty(), KZS_ERROR_ILLEGAL_OPERATION, "Cannot remove a row from a grid layout with no rows");

    m_rows.pop_back();
    getThisObject()->invalidateMeasure();
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::removeColumn()
{
    kzThrowIfErrorTestMessage(!m_columns.empty(), KZS_ERROR_ILLEGAL_OPERATION, "Cannot remove a column from a grid layout with no columns");

    m_columns.pop_back();
    getThisObject()->invalidateMeasure();
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::setRowFixed(unsigned int index, float size)
{
    m_rows.at(index) = RowColumnDefinition(RowColumnSizeModeUser, size, 0.0f, 0.0f);
    getThisObject()->invalidateMeasure();
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::setRowAutomatic(unsigned int index)
{
    m_rows.at(index) = RowColumnDefinition(RowColumnSizeModeAuto, 0.0f, 0.0f, 0.0f);
    getThisObject()->invalidateMeasure();
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::setRowWeighted(unsigned int index, float weight)
{
    m_rows.at(index) = RowColumnDefinition(RowColumnSizeModeWeighted, weight, 0.0f, 0.0f);
    getThisObject()->invalidateMeasure();
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::setColumnFixed(unsigned int index, float size)
{
    m_columns.at(index) = RowColumnDefinition(RowColumnSizeModeUser, size, 0.0f, 0.0f);
    getThisObject()->invalidateMeasure();
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::setColumnAutomatic(unsigned int index)
{
    m_columns.at(index) = RowColumnDefinition(RowColumnSizeModeAuto, 0.0f, 0.0f, 0.0f);
    getThisObject()->invalidateMeasure();
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::setColumnWeighted(unsigned int index, float weight)
{
    m_columns.at(index) = RowColumnDefinition(RowColumnSizeModeWeighted, weight, 0.0f, 0.0f);
    getThisObject()->invalidateMeasure();
}

template<typename TBaseClass, typename TDerivedClass>
float GridLayoutConceptImpl<TBaseClass, TDerivedClass>::getActualRowSize(unsigned int index) const
{
    return m_rows.at(index).m_maxSize;
}

template<typename TBaseClass, typename TDerivedClass>
float GridLayoutConceptImpl<TBaseClass, TDerivedClass>::getActualColumnSize(unsigned int index) const
{
    return m_columns.at(index).m_maxSize;
}

template<typename TBaseClass, typename TDerivedClass>
GridLayoutConcept::GridDirection GridLayoutConceptImpl<TBaseClass, TDerivedClass>::getDirection() const
{
    return getThisObject()->getProperty(DirectionProperty);
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::setDirection(GridLayoutConcept::GridDirection value)
{
    getThisObject()->setProperty(DirectionProperty, value);
}

template<typename TBaseClass, typename TDerivedClass>
string GridLayoutConceptImpl<TBaseClass, TDerivedClass>::getColumnDefinitions() const
{
    return getThisObject()->getProperty(ColumnDefinitionsProperty);
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::setColumnDefinitions(string_view value)
{
    getThisObject()->setProperty(ColumnDefinitionsProperty, string(value));
}

template<typename TBaseClass, typename TDerivedClass>
string GridLayoutConceptImpl<TBaseClass, TDerivedClass>::getRowDefinitions() const
{
    return getThisObject()->getProperty(RowDefinitionsProperty);
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::setRowDefinitions(string_view value)
{
    getThisObject()->setProperty(RowDefinitionsProperty, string(value));
}

template<typename TBaseClass, typename TDerivedClass>
GridLayoutConceptImpl<TBaseClass, TDerivedClass>::GridLayoutConceptImpl(Domain* domain, string_view name):
    TBaseClass(domain, name),
    m_rowWeights(0.0f),
    m_columnWeights(0.0f),
    m_accumulatedRowSize(0.0f),
    m_accumulatedColumnSize(0.0f)
{
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason)
{
    TBaseClass::onNodePropertyChanged(propertyType, reason);

    if(propertyType == RowDefinitionsProperty)
    {
        string rowDefinitions = getRowDefinitions();
        parseRowColumnDefinitions(rowDefinitions, m_rows);
    }
    else if(propertyType == ColumnDefinitionsProperty)
    {
        string columnDefinitions = getColumnDefinitions();
        parseRowColumnDefinitions(columnDefinitions, m_columns);
    }
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::getNextItemLocation(const Node& node, GridObjectLocationWorkspace& workspace, unsigned int& out_row, unsigned int& out_column)
{
    unsigned int row;
    unsigned int column;

    optional<int> rowInt = node.getOptionalProperty(GridLayoutConcept::RowProperty);
    optional<int> columnInt = node.getOptionalProperty(GridLayoutConcept::ColumnProperty);
    if(rowInt && columnInt && (*rowInt >= 0) && (*columnInt >= 0))
    {
        row = *rowInt;
        column = *columnInt;
        workspace.column = column;
        workspace.row = row;
    }
    else
    {
        row = workspace.row;
        column = workspace.column;
    }

    // Update next slot.
    switch(workspace.direction)
    {
        case GridDirectionRight:
        {
            ++workspace.column;
            if(workspace.column >= workspace.columnCount)
            {
                ++workspace.row;
                workspace.column = 0;
            }
            break;
        }
        case GridDirectionDown:
        {
            ++workspace.row;
            if(workspace.row >= workspace.rowCount)
            {
                ++workspace.column;
                workspace.row = 0;
            }
            break;
        }
        default:
        {
            kzAssertUnreachableMessage(("Invalid grid layout direction {}.", workspace.direction));
        }
    }

    out_column = column;
    out_row = row;
}

template<typename TBaseClass, typename TDerivedClass>
void GridLayoutConceptImpl<TBaseClass, TDerivedClass>::getSpan(const Node& item, unsigned int& rowSpan, unsigned int& columnSpan)
{
    rowSpan = getRowSpan(item);
    columnSpan = getColumnSpan(item);
    rowSpan = max(rowSpan, 1u);
    columnSpan = max(columnSpan, 1u);
}

template<typename TBaseClass, typename TDerivedClass>
PropertyTypeEditorInfoSharedPtr GridLayoutConceptImpl<TBaseClass, TDerivedClass>::makeEditorInfo()
{
    return PropertyTypeEditorInfoSharedPtr(
        KZ_PROPERTY_TYPE_EDITOR_INFO(
            []() -> PropertyTypeEditorInfo::AttributeDictionary
            {
                PropertyTypeEditorInfo::AttributeDictionary dict;

                dict.displayName = "Grid Layout";

                return dict;
            }()
        ));
}

}


#endif
