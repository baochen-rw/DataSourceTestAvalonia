// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_CONTENT_REFERENCE_HPP
#define KZ_CONTENT_REFERENCE_HPP

#include <kanzi/core.ui/node/abstract_resource_reference.hpp>
#include <kanzi/core.ui/node/node.hpp>

namespace kanzi
{

template <typename TResourceType>
class ContentReference : public AbstractResourceReference
{
    typedef void (ContentReference<TResourceType>::*bool_type)() const;
    void this_type_does_not_support_comparisons() const {}

public:

    typedef function<void()> CallbackType;

#ifdef KZ_SUPPORTS_EXPLICIT_OPERATOR

    explicit operator bool() const
    {
        //return (m_resource || m_userResource);
        return static_cast<bool>(m_resource);
    }

#else
    
    operator bool_type() const
    {
        return m_resource ? &ContentReference<TResourceType>::this_type_does_not_support_comparisons : 0;
        //return (m_resource || m_userResource) ? &ContentReference<TResourceType>::this_type_does_not_support_comparisons : 0;
    }

#endif

    typedef shared_ptr<TResourceType> ResourceTypePtr;

    explicit ContentReference(Node& thisObject);

    ~ContentReference();

    void setResource(const ResourceID& id)
    {
        m_resourceId = id;

        // Keep old resource alive while the callback is running
        ResourceTypePtr oldResource = get();
        updateResource();

        // Update the callbacks on initial value, even if it is null.
        updateChangeFlags();
        notifyCallback();
    }

    virtual void onIdChanged() KZ_OVERRIDE
    {
        // Keep old resource alive while the callback is running
        ResourceTypePtr oldResource = get();
        updateResource();

        if (oldResource != getResource())
        {
            updateChangeFlags();
            notifyCallback();
        }
    }

    virtual void onResourceChanged() KZ_OVERRIDE
    {
        // Keep old resource alive while the callback is running
        ResourceTypePtr oldResource = get();
        updateResource();

        if (oldResource != getResource())
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

        if (oldResource != getResource())
        {
            updateChangeFlags();
            notifyCallback();
        }
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

    /// Access user resource.
    ///
    /// \return User resource shared pointer.
    ResourceTypePtr getUserResource() const
    {
        return m_userResource;
    }
    
    /// Clear user resource.
    void resetUserResource()
    {
        m_userResource.reset();
        updateChangeFlags();
    }
    
    /// Set user resource.
    ///
    /// \param userResource New user resource.
    void setUserResource(ResourceTypePtr userResource)
    {
        // TODO: use optional<Resource> to have null
        // TODO: decide if the normal resource should be released in this case
        m_userResource = userResource;
        updateChangeFlags();
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
        if (m_userResource)
        {
            return m_userResource;
        }
        return m_resource;
    }

    const ResourceTypePtr& resolve() const
    {
        if (m_clonedResource)
        {
            return m_clonedResource;
        }
        if (m_userResource)
        {
            return m_userResource;
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

    ContentReference(const ContentReference&) KZ_DELETED_FUNCTION;
    ContentReference& operator=(const ContentReference&) KZ_DELETED_FUNCTION;

    /// Node referencing resource.
    Node& m_node;
    /// Resource id of content.
    ResourceID m_resourceId;                
    // AbstractPropertyType m_propertyType; ///< Property type referencing resource.
    size_t m_hash;                       ///< Hash code.
    ResourceTypePtr m_resource;          ///< Resource referenced by property.
    ResourceTypePtr m_userResource;      ///< User-specified resource.
    ResourceTypePtr m_clonedResource;    ///< Cloned resource.
    CallbackType m_callback;             ///< Notification callback.
};

template <typename TResourceType>
ContentReference<TResourceType>::ContentReference(Node& thisObject) : m_node(thisObject), /*m_propertyType(propertyType),*/ m_hash(0)
{
    /*kzAssert(propertyType.get() != 0);*/
    thisObject.addResourceReference(AbstractPropertyType(), this);
}

template <typename TResourceType>
ContentReference<TResourceType>::~ContentReference()
{
    m_node.removeResourceReference(*this);
}

template <typename TResourceType>
void ContentReference<TResourceType>::updateResource()
{
    ResourceTypePtr resource = m_node.tryAcquireResource<TResourceType>(m_resourceId);
    swap(m_resource, resource);
}

template <typename TResourceType>
void ContentReference<TResourceType>::updateChangeFlags() const
{
    // TODO: must be tied to property type somehow
    //m_node.setChangeFlag(m_propertyType.getChangeFlags());
}

}

#endif
