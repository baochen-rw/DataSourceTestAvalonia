// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_RESOURCE_REFERENCE_H
#define KZU_RESOURCE_REFERENCE_H


#include "abstract_resource_reference.hpp"

#include <kanzi/core.ui/node/node.hpp>

namespace kanzi
{

template <typename TResourceType>
ResourceReference<TResourceType>::ResourceReference(Node& thisObject, AbstractPropertyType propertyType) : m_node(thisObject), m_propertyType(propertyType)
{
    kzAssert(propertyType);
    thisObject.addResourceReference(propertyType, this);
}

template <typename TResourceType>
ResourceReference<TResourceType>::~ResourceReference()
{
    m_node.removeResourceReference(*this);
}

template <typename TResourceType>
void ResourceReference<TResourceType>::updateResource()
{
    ResourceSharedPtr abstractResource = m_node.getAbstractProperty<ResourceSharedPtr>(m_propertyType);
    ResourceTypePtr resource = dynamic_pointer_cast<TResourceType>(abstractResource);

    swap(m_resource, resource);
}

template <typename TResourceType>
void ResourceReference<TResourceType>::updateChangeFlags() const
{
    m_node.setChangeFlag(m_propertyType.getChangeFlags());
}

}

#endif
