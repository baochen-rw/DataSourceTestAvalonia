// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_ABSTRACT_RESOURCE_REFERENCE_H
#define KZU_ABSTRACT_RESOURCE_REFERENCE_H

#include <kanzi/core/property/property_type.hpp>

#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/cpp/memory.hpp>


namespace kanzi
{

// Forward declaration.
class AbstractPropertyType;
class Node;
class Resource;

typedef shared_ptr<Resource> ResourceSharedPtr;


class KANZI_API AbstractResourceReference
{
public:

    virtual void onIdChanged() = 0;
    virtual void onResourceChanged() = 0;
    virtual void release() = 0;
    virtual ResourceSharedPtr getResource() = 0;

protected:

    virtual ~AbstractResourceReference() {}
};

template <typename TResourceType>
class ResourceReference : public AbstractResourceReference
{
    typedef void (ResourceReference<TResourceType>::*bool_type)() const;
    void this_type_does_not_support_comparisons() const {}

public:

    typedef function<void()> CallbackType;

#ifdef KZ_SUPPORTS_EXPLICIT_OPERATOR

    explicit operator bool() const
    {
        return static_cast<bool>(m_resource);
    }

#else

    operator bool_type() const
    {
        return m_resource ? &ResourceReference<TResourceType>::this_type_does_not_support_comparisons : 0;
    }

#endif

    typedef shared_ptr<TResourceType> ResourceTypePtr;

    explicit ResourceReference(Node& thisObject, AbstractPropertyType propertyType);

    ~ResourceReference();

    virtual void onIdChanged() KZ_OVERRIDE
    {
        // Keep old resource alive while the callback is running
        ResourceTypePtr oldResource = get();
        updateResource();
        notifyCallback();
    }

    virtual void onResourceChanged() KZ_OVERRIDE
    {
        // Keep old resource alive while the callback is running
        ResourceTypePtr oldResource = get();
        updateResource();
        // Prevent changes if resolving to same resource as before
        if (resolve() != oldResource)
        {
            updateChangeFlags();
            notifyCallback();
        }
    }

    virtual void release() KZ_OVERRIDE
    {
        // Keep old resource alive while the callback is running
        ResourceTypePtr oldResource = get();
        m_resource.reset();
        updateChangeFlags();
        notifyCallback();
    }

    virtual ResourceSharedPtr getResource() KZ_OVERRIDE
    {
        return get();
    }

    /// Clone reference to be an internal copy.
    ///
    /// Default implementation clones nothing, and returns an empty shared pointer.
    ResourceTypePtr makeLocal()
    {
        m_clonedResource.reset();
        return ResourceTypePtr();
    }

    void setCallback(CallbackType callback)
    {
        using namespace std;
        swap(m_callback, callback);
    }

    ResourceTypePtr get() const
    {
        return resolve();
    }

    TResourceType* operator->() const
    {
        return resolve().get();
    }

    TResourceType& operator*() const
    {
        return *resolve();
    }

protected:

    ResourceTypePtr& resolve()
    {
        if (m_clonedResource)
        {
            return m_clonedResource;
        }
        return m_resource;
    }

    const ResourceTypePtr& resolve() const
    {
        if (m_clonedResource)
        {
            return m_clonedResource;
        }
        return m_resource;
    }

    void updateResource();

    void updateChangeFlags() const;

    void notifyCallback()
    {
        if (m_callback)
        {
            m_callback();
        }
    }

private:

    ResourceReference(const ResourceReference&) KZ_DELETED_FUNCTION;
    ResourceReference& operator=(const ResourceReference&) KZ_DELETED_FUNCTION;

    Node& m_node;                        ///< Node referencing resource.
    AbstractPropertyType m_propertyType; ///< Property type referencing resource.
    ResourceTypePtr m_resource;          ///< Resource referenced by property.
    ResourceTypePtr m_clonedResource;    ///< Cloned resource.
    CallbackType m_callback;             ///< Notification callback.
};

}


#endif
