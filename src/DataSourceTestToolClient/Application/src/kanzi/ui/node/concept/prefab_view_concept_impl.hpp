// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PREFAB_VIEW_CONCEPT_IMPL_HPP
#define KZ_PREFAB_VIEW_CONCEPT_IMPL_HPP

#include "prefab_view.hpp"

#include <kanzi/core.ui/resource/async_tasks.hpp>
#include <kanzi/core.ui/resource/collect_resource_urls.hpp>

namespace kanzi
{

template <typename TBaseClass, typename TDerivedClass>
PrefabTemplateSharedPtr PrefabViewConceptImpl<TBaseClass, TDerivedClass>::getPrefab() const
{
    return static_pointer_cast<PrefabTemplate>(getThisObject()->getProperty(PrefabProperty));
}

template <typename TBaseClass, typename TDerivedClass>
void PrefabViewConceptImpl<TBaseClass, TDerivedClass>::setPrefab(PrefabTemplateSharedPtr value)
{
    getThisObject()->setProperty(PrefabProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
PrefabViewConceptImpl<TBaseClass, TDerivedClass>::PrefabViewConceptImpl(Domain* domain, string_view name):
    TBaseClass(domain, name)
{
}

template <typename TBaseClass, typename TDerivedClass>
void PrefabViewConceptImpl<TBaseClass, TDerivedClass>::initialize()
{
    TBaseClass::initialize();

    TBaseClass::addMessageHandler(LoadAsynchronouslyMessage, getThisObject(), &TDerivedClass::onLoadAsynchronously);
}

template <typename TBaseClass, typename TDerivedClass>
shared_ptr<TBaseClass> PrefabViewConceptImpl<TBaseClass, TDerivedClass>::getInstantiatedNode() const
{
    return m_instantiatedNode;
}

template <typename TBaseClass, typename TDerivedClass>
void PrefabViewConceptImpl<TBaseClass, TDerivedClass>::onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason)
{
    TBaseClass::onNodePropertyChanged(propertyType, reason);

    if (propertyType == PrefabProperty)
    {
        updateNode(getPrefab());
    }
}

template <typename TBaseClass, typename TDerivedClass>
void PrefabViewConceptImpl<TBaseClass, TDerivedClass>::updateNode(PrefabTemplateSharedPtr prefabTemplate)
{
    // Remove previous.
    {
        NodeTypeSharedPtr node;

        swap(node, m_instantiatedNode);
        
        // The instantiated node might have been removed from the parent already during project patching.
        // Remove it here if it is still a child of the prefab view.
        if (node && node->getParent())
        {
            getThisObject()->removeChild(*node);
        }
    }

    // Add new if possible.
    if (prefabTemplate)
    {
        NodeTypeSharedPtr node = prefabTemplate->instantiateAsPart<TBaseClass>(prefabTemplate->getName(), getThisObject()->shared_from_this());

        if (node)
        {
            getThisObject()->insertChild(0, node);
        }

        swap(m_instantiatedNode, node);
    }
}

template <typename TBaseClass, typename TDerivedClass>
void PrefabViewConceptImpl<TBaseClass, TDerivedClass>::loadPrefabAsynchronously(ResourceID key)
{
    LoadAsynchronouslyMessageArguments message;
    message.setPrefabTemplate(key);
    getThisObject()->dispatchMessage(LoadAsynchronouslyMessage, message);
}

template <typename TBaseClass, typename TDerivedClass>
void PrefabViewConceptImpl<TBaseClass, TDerivedClass>::onLoadAsynchronously(LoadAsynchronouslyMessageArguments& arguments)
{
    ResourceID prefabViewResourceId(arguments.getPrefabTemplate());

    shared_ptr<TDerivedClass> sharedReference = static_pointer_cast<TDerivedClass>(getThisObject()->shared_from_this());
    weak_ptr<TDerivedClass> weakReference(sharedReference);

    // Save resource ID so we can check if the the callback is relevant.
    m_acquireTaskResourceId = prefabViewResourceId;

    loadPrefabAsync(*getThisObject(), prefabViewResourceId, bind(TDerivedClass::onAsyncLoadCompletedCallback, weakReference, prefabViewResourceId));
}

template <typename TBaseClass, typename TDerivedClass>
void PrefabViewConceptImpl<TBaseClass, TDerivedClass>::onAsyncLoadCompletedCallback(weak_ptr<TDerivedClass> prefabView, ResourceID key)
{
    shared_ptr<TDerivedClass> sharedPrefabView = prefabView.lock();
    if (sharedPrefabView)
    {
        sharedPrefabView->onAsyncLoadCompleted(key);
    }
}

template <typename TBaseClass, typename TDerivedClass>
void PrefabViewConceptImpl<TBaseClass, TDerivedClass>::onAsyncLoadCompleted(ResourceID key)
{
    // Only use the loaded prefab template if it was the latest acquire task.
    if (m_acquireTaskResourceId == key)
    {
        PrefabTemplateSharedPtr prefabTemplate = dynamic_pointer_cast<PrefabTemplate>(getThisObject()->tryAcquireResource(key));

        getThisObject()->setPrefab(prefabTemplate);

        m_acquireTaskResourceId = ResourceID();

        // Dispatch message signifying task is complete.
        AsynchronousLoadCompletedMessageArguments message;
        message.setPrefabTemplate(key);
        getThisObject()->dispatchMessage(AsynchronousLoadCompletedMessage, message);
    }
}

template <typename TBaseClass, typename TDerivedClass>
PropertyTypeEditorInfoSharedPtr PrefabViewConceptImpl<TBaseClass, TDerivedClass>::makeEditorInfo()
{
    return PropertyTypeEditorInfoSharedPtr(
        KZ_PROPERTY_TYPE_EDITOR_INFO(
            []() -> PropertyTypeEditorInfo::AttributeDictionary
            {
                PropertyTypeEditorInfo::AttributeDictionary dict;

                dict.displayName = "Prefab View";

                return dict;
            }()
        ));
}

}

#endif
