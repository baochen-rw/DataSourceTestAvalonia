// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_META_OBJECT_HPP
#define KZ_META_OBJECT_HPP

#include <kanzi/core/metadata/metaclass.hpp>


namespace kanzi
{

class MetaObject;
/// MetaObject shared pointer type.
typedef shared_ptr<MetaObject> MetaObjectSharedPtr;

/// MetaObject is the base class for classes that provide type reflection.
/// Type reflection can be used to enumerate property types, message types and base classes of a class.
class KANZI_API MetaObject
{
public:

    virtual ~MetaObject();

    /// Returns the metaclass of Object class.
    static const Metaclass* getStaticMetaclass();
    /// Returns the metaclass of the dynamic type of the object.
    virtual const Metaclass* getDynamicMetaclass() const;

    /// Default implementation that returns empty editor info.
    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Determines if the type of this object is the given type or derived from it.
    /// \param objectType Type to test against.
    /// \return True if this object is an instance of objectType.
    bool isTypeOf(const Metaclass* objectType) const
    {
        return objectType->isMetaclassOf(*this);
    }

protected:

    explicit MetaObject()
    {
    }

    void initialize()
    {
    }

private:

    MetaObject(const MetaObject& other) KZ_DELETED_FUNCTION;
    MetaObject& operator = (const MetaObject& other) KZ_DELETED_FUNCTION;
};

}

#endif
