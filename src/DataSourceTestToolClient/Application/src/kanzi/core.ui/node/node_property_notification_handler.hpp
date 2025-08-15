// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NODE_PROPERTY_NOTIFICATION_HANDLER_HPP
#define KZ_NODE_PROPERTY_NOTIFICATION_HANDLER_HPP

#include "node.hpp"

#include <kanzi/core/property/abstract_property_notification_handler.hpp>

namespace kanzi
{

/// Node property notification handler.
class NodePropertyNotificationHandler : public AbstractPropertyNotificationHandler
{
public:

    /// Access the node.
    /// \return Pointer to node.
    Node* getNode() const
    {
        return m_node;
    }

    /// Invalidates the state of the notification handler.
    /// Use this function to invalidate a node that you destroyed before destroying the NodePropertyNotificationHandler.
    void invalidate()
    {
        m_node = 0;
    }
    /// Tell if this notification handler is valid.
    /// \return True if yes, false if no.
    bool isValid() const
    {
        return (m_node != 0);
    }

protected:

    /// Empty constructor.
    explicit NodePropertyNotificationHandler() :
             m_node(0) {}

    /// Copy constructor.
    ///
    /// \param rhs Handler to copy from.
    explicit NodePropertyNotificationHandler(const NodePropertyNotificationHandler& rhs) :
             AbstractPropertyNotificationHandler(rhs.getPropertyType()),
             m_node(rhs.getNode())
    {
        attach();
    }

    /// Constructor.
    ///
    /// Implicitly attaches to the node it's constructed on.
    explicit NodePropertyNotificationHandler(AbstractPropertyType propertyType, Node* node) :
             AbstractPropertyNotificationHandler(propertyType),
             m_node(node)
    {
        attach();
    }

    /// Destructor.
    ///
    /// Implicitly deattaches from the node it was constructed on.
    virtual ~NodePropertyNotificationHandler()
    {
        detach();
    }

    /// Assignment operator.
    ///
    /// \param rhs Handler to copy from.
    /// \return Reference to assignee.
    NodePropertyNotificationHandler& operator=(const NodePropertyNotificationHandler& rhs)
    {
        detach(); // Detach from old node.

        AbstractPropertyNotificationHandler::operator=(rhs);
        m_node = rhs.m_node;

        attach(); // Attach to new node.

        return *this;
    }

private:
    /// Notification handler function.
    template <typename T>
    static void notificationHandler(PropertyObject&, const typename PropertyType<T>::Traits::StorageType&, PropertyNotificationReason reason, void* data)
    {
        NodePropertyNotificationHandler* self = static_cast<NodePropertyNotificationHandler*>(data);
        self->onPropertyChanged(reason);
    }

    template <typename T>
    void toggleNotificationHandler(bool add)
    {
        DynamicPropertyType<T> propertyType(getPropertyType());

        if (add)
        {
            m_node->addPropertyNotificationHandler(propertyType, &notificationHandler<T>, this);
        }
        else
        {
            m_node->removePropertyNotificationHandler(propertyType, &notificationHandler<T>, this);
        }
    }

    /// Attach to node.
    void attach()
    {
        if(!isValid())
        {
            return;
        }

        switch (getPropertyType().getDataType())
        {
            case PropertyDataTypeFloat: toggleNotificationHandler<float>(true); break;
            case PropertyDataTypeInt: toggleNotificationHandler<int>(true); break;
            case PropertyDataTypeBool: toggleNotificationHandler<bool>(true); break;
            case PropertyDataTypeColor: toggleNotificationHandler<ColorRGBA>(true); break;
            case PropertyDataTypeVector2: toggleNotificationHandler<Vector2>(true); break;
            case PropertyDataTypeVector3: toggleNotificationHandler<Vector3>(true); break;
            case PropertyDataTypeVector4: toggleNotificationHandler<Vector4>(true); break;
            case PropertyDataTypeMatrix3x3: toggleNotificationHandler<Matrix3x3>(true); break;
            case PropertyDataTypeMatrix4x4: toggleNotificationHandler<Matrix4x4>(true); break;
            case PropertyDataTypeString: toggleNotificationHandler<string>(true); break;
            case PropertyDataTypePointer: toggleNotificationHandler<void*>(true); break;
            case PropertyDataTypeResource: toggleNotificationHandler<ResourceSharedPtr>(true); break;
            case PropertyDataTypeSRT2D: toggleNotificationHandler<SRTValue2D>(true); break;
            case PropertyDataTypeSRT3D: toggleNotificationHandler<SRTValue3D>(true); break;
            default: break;
        }
    }

    /// Detach from node.
    void detach()
    {
        if(!isValid())
        {
            return;
        }

        switch (getPropertyType().getDataType())
        {
            case PropertyDataTypeFloat: toggleNotificationHandler<float>(false); break;
            case PropertyDataTypeInt: toggleNotificationHandler<int>(false); break;
            case PropertyDataTypeBool: toggleNotificationHandler<bool>(false); break;
            case PropertyDataTypeColor: toggleNotificationHandler<ColorRGBA>(false); break;
            case PropertyDataTypeVector2: toggleNotificationHandler<Vector2>(false); break;
            case PropertyDataTypeVector3: toggleNotificationHandler<Vector3>(false); break;
            case PropertyDataTypeVector4: toggleNotificationHandler<Vector4>(false); break;
            case PropertyDataTypeMatrix3x3: toggleNotificationHandler<Matrix3x3>(false); break;
            case PropertyDataTypeMatrix4x4: toggleNotificationHandler<Matrix4x4>(false); break;
            case PropertyDataTypeString: toggleNotificationHandler<string>(false); break;
            case PropertyDataTypePointer: toggleNotificationHandler<void*>(false); break;
            case PropertyDataTypeResource: toggleNotificationHandler<ResourceSharedPtr>(false); break;
            case PropertyDataTypeSRT2D: toggleNotificationHandler<SRTValue2D>(false); break;
            case PropertyDataTypeSRT3D: toggleNotificationHandler<SRTValue3D>(false); break;
            default: break;
        }
    }

    Node* m_node; ///< Node attached to.
};

}


#endif
