// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ABSTRACT_PROPERTY_NOTIFICATION_HANDLER_HPP
#define KZ_ABSTRACT_PROPERTY_NOTIFICATION_HANDLER_HPP


#include <kanzi/core/property/property_type.hpp>

namespace kanzi
{

/// Abstract property notification handler.
class AbstractPropertyNotificationHandler
{
public:
    /// Method to be executed when property is changed.
    ///
    /// \param reason Why property was changed.
    virtual void onPropertyChanged(PropertyNotificationReason reason) = 0;

    /// Get the property type this handler is listening.
    ///
    /// \return Property type.
    AbstractPropertyType getPropertyType() const
    {
        return m_propertyType;
    }

protected:
    /// Empty constructor.
    explicit AbstractPropertyNotificationHandler() {}

    /// Constructor.
    ///
    /// \param propertyType Property type to attach on.
    explicit AbstractPropertyNotificationHandler(AbstractPropertyType propertyType) :
             m_propertyType(propertyType) {}

private:
    AbstractPropertyType m_propertyType; ///< Property type.
};


/// Abstract property notification handler shared pointer.
typedef shared_ptr<AbstractPropertyNotificationHandler> AbstractPropertyNotificationHandlerSharedPtr;

}


#endif
