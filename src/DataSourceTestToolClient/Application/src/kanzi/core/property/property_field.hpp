// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_FIELD_HPP
#define KZ_PROPERTY_FIELD_HPP

namespace kanzi
{

/// Property field.
enum PropertyField
{
    /// Whole property value.
    PropertyFieldWhole,
    /// Translation X component, presented as float.
    PropertyFieldTranslationX,
    /// Translation Y component, presented as float.
    PropertyFieldTranslationY,
    /// Translation Z component, presented as float.
    PropertyFieldTranslationZ,
    /// Scale X component, presented as float.
    PropertyFieldScaleX,
    /// Scale Y component, presented as float.
    PropertyFieldScaleY,
    /// Scale Z component, presented as float.
    PropertyFieldScaleZ,
    /// Rotation X component, presented as float.
    PropertyFieldRotationX,
    /// Rotation Y component, presented as float.
    PropertyFieldRotationY,
    /// Rotation Z component, presented as float.
    PropertyFieldRotationZ,
    /// Color R field, presented as float.
    PropertyFieldColorR,
    /// Color G field, presented as float.
    PropertyFieldColorG,
    /// Color B field, presented as float.
    PropertyFieldColorB,
    /// Color A field, presented as float.
    PropertyFieldColorA,
    /// Vector X field, presented as float.
    PropertyFieldVectorX,
    /// Vector Y field, presented as float.
    PropertyFieldVectorY,
    /// Vector Z field, presented as float.
    PropertyFieldVectorZ,
    /// Vector W field, presented as float.
    PropertyFieldVectorW,
    /// Rotation component of property of SRTValue3D type, presented as Quaternion.
    PropertyFieldRotation
};


}


#endif
