// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_DATA_TYPE_HPP
#define KZ_PROPERTY_DATA_TYPE_HPP


namespace kanzi
{

/// Enumeration of data types that can be stored as properties.
enum PropertyDataType
{
    /// Float data.
    PropertyDataTypeFloat,
    /// Integer data.
    PropertyDataTypeInt,
    /// Boolean data.
    PropertyDataTypeBool,
    /// ColorRGBA data.
    PropertyDataTypeColor,
    /// Vector2 data.
    PropertyDataTypeVector2,
    /// Vector3 data.
    PropertyDataTypeVector3,
    /// Vector4 data.
    PropertyDataTypeVector4,
    /// Matrix3x3 data.
    PropertyDataTypeMatrix3x3,
    /// Matrix4x4 data.
    PropertyDataTypeMatrix4x4,
    /// String data.
    PropertyDataTypeString,
    /// Pointer data.
    PropertyDataTypePointer,
    /// Resource data.
    PropertyDataTypeResource,
    /// SRTValue2D data.
    PropertyDataTypeSRT2D,
    /// SRTValue3D data.
    PropertyDataTypeSRT3D
};

}


#endif
