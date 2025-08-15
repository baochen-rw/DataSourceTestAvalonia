// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_OBJECT_HPP
#define KZ_OBJECT_HPP

#include <kanzi/core/metadata/metaclass.hpp>
#include <kanzi/core/metadata/meta_object.hpp>
#include <kanzi/core/property/property_object.hpp>
#include <kanzi/core/property/property_type.hpp>
#include <kanzi/core/property/dynamic_property_type.hpp>

#include <kanzi/core/cpp/type_traits.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/vector.hpp>


// Forward declarations.
struct KzuMessageDispatcher;
struct KzuTaskScheduler;

namespace kanzi
{

// Forward declaration.
struct AppliedStyleEntry;
class ResourceManager;
class Style;
typedef shared_ptr<Style> StyleSharedPtr;

/// AppliedStyleEntry shared pointer type.
typedef shared_ptr<AppliedStyleEntry> AppliedStyleEntrySharedPtr;

/// Applied style entry.
struct AppliedStyleEntry
{
    /// Creates a new applied style entry.
    /// \param associatedStyle Associated style.
    static AppliedStyleEntrySharedPtr create(StyleSharedPtr associatedStyle)
    {
        AppliedStyleEntrySharedPtr entry(new AppliedStyleEntry(associatedStyle));
        return entry;
    }

    /// Style.
    const StyleSharedPtr style;
    /// Is the style applied manually.
    bool manual;

protected:

    /// Constructor.
    /// \param associatedStyle Associated style.
    explicit AppliedStyleEntry(kanzi::StyleSharedPtr associatedStyle) :
        style(associatedStyle),
        manual(false)
    {
    }

private:

    AppliedStyleEntry(const AppliedStyleEntry&) KZ_DELETED_FUNCTION;
    AppliedStyleEntry& operator=(const AppliedStyleEntry&) KZ_DELETED_FUNCTION;
};

class Object;
/// Object shared pointer type.
typedef shared_ptr<Object> ObjectSharedPtr;


/// Object is the base class for Kanzi UI classes that implement association with a Domain.
///
/// For the explanation of the metadata system see Metaclass and MetaObject.
/// For the explanation of the property system see PropertyObject and PropertyType.
class KANZI_API Object : public MetaObject, public PropertyObject
{
public:

    explicit Object(Domain* domain);

    virtual ~Object();

    /// Returns the domain the object belongs to.
    Domain* getDomain() const;

    /// Returns the task scheduler of the object.
    KzuTaskScheduler* getTaskScheduler() const;

    /// Returns the message dispatcher of the object.
    KzuMessageDispatcher* getMessageDispatcher() const;

    /// Returns the resource manager of the object.
    ResourceManager* getResourceManager() const;

    /// Returns the metaclass of Object class.
    static const Metaclass* getStaticMetaclass();
    /// Returns the metaclass of the dynamic type of the object.
    virtual const Metaclass* getDynamicMetaclass() const KZ_OVERRIDE;

    /// Default implementation that returns empty editor info.
    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Applies a style to an object.
    ///
    /// \return A style entry that is used to unapply the style.
    AppliedStyleEntrySharedPtr applyObjectStyle(kanzi::StyleSharedPtr style);
    //// Unapplies a style from an object.
    void unapplyObjectStyle(AppliedStyleEntrySharedPtr appliedStyleEntry);
    /// Apply all styles for an object node.
    void applyObjectStyles();
    /// Unapplies and removes all applied styles.
    void unapplyObjectStyles();

private:

    Object(const Object& other) KZ_DELETED_FUNCTION;
    Object& operator = (const Object& other) KZ_DELETED_FUNCTION;

protected:

    /// Applied style container.
    typedef vector<AppliedStyleEntrySharedPtr> AppliedStyleContainer;

    /// Listing of applied styles applied to this object.
    AppliedStyleContainer m_appliedStyles;

    void initialize() {}

    void onCopy(const Object& other);

private:

    Domain* m_domain;
};

}

#endif
