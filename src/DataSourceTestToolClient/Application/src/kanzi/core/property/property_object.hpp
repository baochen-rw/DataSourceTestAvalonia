// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_OBJECT_HPP
#define KZ_PROPERTY_OBJECT_HPP

#include <kanzi/core/cpp/intrusive_ptr.hpp>
#include <kanzi/core/property/property_type.hpp>
#include <kanzi/core/property/dynamic_property_type.hpp>

namespace kanzi
{

/// PropertyObject is the base class that supports setting and retrieving properties.
/// See PropertyType, AbstractPropertyType, DynamicPropertyType.
class KANZI_API PropertyObject
{
public:

    typedef intrusive_ptr<AbstractPropertyTypeDescriptor::PropertyStorage> PropertyStoragePtr;
    typedef vector<PropertyStoragePtr> PropertyStorageContainer;
    typedef PropertyStorageContainer::iterator PropertyStorageIterator;
    typedef PropertyStorageContainer::const_iterator PropertyStorageConstIterator;
    typedef PropertyStorageContainer::reverse_iterator PropertyStorageReverseIterator;

    explicit PropertyObject();
    virtual ~PropertyObject();

    /// Sets the local value of a property.
    ///
    /// \param propertyType The property type identifying the property to set.
    /// \param value The value to set.
    template <typename DataType>
    void setProperty(const PropertyType<DataType>& propertyType, typename PropertyType<DataType>::Traits::ParameterType value)
    {
        typedef typename PropertyType<DataType>::Descriptor Descriptor;
        typedef typename PropertyType<DataType>::Traits Traits;
        typedef typename Descriptor::TypedValueSource TypedValueSource;

        Descriptor* descriptor = propertyType.get();
        kzAssert(descriptor);
        PropertyStoragePtr propertyStorage = acquirePropertyStorage(*descriptor);
        kzAssert(propertyStorage);

        AbstractPropertyTypeDescriptor::ValueSourceEntry* localValueSourceEntry = acquireLocalValueSourceEntry(*descriptor, propertyStorage);
        TypedValueSource* typedValueSource = static_cast<TypedValueSource*>(localValueSourceEntry->valueSource);
        Traits::write(typedValueSource->value, value);

        validatePropertyModifiersAndNotifyHandlers(propertyStorage);
    }

    void removeKzbProperties();

    /// Returns the current value of a property.
    ///
    /// The value returned by this function is the result of the property system evaluating the inputs that can affect the values of properties.
    /// The final value is calculated by determining the base value of the property and applying existing modifiers to it.
    ///
    /// Base value is affected by the following inputs where the highest entry in the list determines the base value:
    /// 1. Local value set with setProperty or loaded from kzb
    /// 2. Value set by a style affecting the property.
    /// 3. Value defined by class metadata.
    ///
    /// When the base value is determined the system applies modifiers to the value that can change the value or replace it completely.
    /// The following is the list of possible modifiers, where the order of evaluation is determined by the order the modifiers were added or applied.
    /// 1. Values defined is states of state manager.
    /// 2. Animations.
    ///
    /// If no inputs to the property value can be established the system returns the value registered in the property type metadata.
    /// \param propertyType The property type identifying the property to retrieve.
    /// \return Returns the evaluated property value.
    template <typename DataType>
    typename PropertyType<DataType>::Traits::ReturnType getProperty(const PropertyType<DataType>& propertyType) const
    {
        typedef typename PropertyType<DataType>::Descriptor Descriptor;
        typedef typename PropertyType<DataType>::Traits Traits;
        typedef typename Descriptor::TypedValueSource TypedValueSource;

        Descriptor* descriptor = propertyType.get();
        kzAssert(descriptor);
        AbstractPropertyTypeDescriptor::ValueSource* finalValueSource = getFinalValueSource(*descriptor);
        if (!finalValueSource)
        {
            return propertyType.getDefaultValue();
        }

        TypedValueSource* typedValueSource = static_cast<TypedValueSource*>(finalValueSource);
        return Traits::read(typedValueSource->value);
    }

    /// Evaluates the property value in the same way as the overload above but does not default to the value in property metadata if there are no inputs to the property value.
    /// \param propertyType The property type identifying the property to retrieve.
    /// \param value The reference that receives the value the function evaluates. The reference is not modified if there are no inputs to the property value.
    /// \return Returns an optional value that is left empty if the property was not found.
    template <typename DataType>
    optional<typename PropertyType<DataType>::Traits::ReturnType> getOptionalProperty(const PropertyType<DataType>& propertyType) const
    {
        typedef typename PropertyType<DataType>::Descriptor Descriptor;
        typedef typename PropertyType<DataType>::Traits Traits;
        typedef typename Descriptor::TypedValueSource TypedValueSource;

        Descriptor* descriptor = propertyType.get();
        kzAssert(descriptor);
        AbstractPropertyTypeDescriptor::ValueSource* finalValueSource = getFinalValueSource(*descriptor);
        if (!finalValueSource)
        {
            return nullopt;
        }

        TypedValueSource* typedValueSource = static_cast<TypedValueSource*>(finalValueSource);
        return Traits::read(typedValueSource->value);
    }

    /// Returns the current value of a property disregarding modifiers.
    ///
    /// Base value is affected by the following inputs where the highest entry in the list determines the base value:
    /// 1. Local value set with setProperty or loaded from kzb
    /// 2. Value set by a style affecting the property.
    /// 3. Value defined by class metadata.
    ///
    /// Modifiers are not applied, the highest-priority base value is returned.
    ///
    /// If no inputs to the property value can be established the system returns the value default value from property type metadata.
    /// \param propertyType The property type identifying the property to retrieve.
    /// \return Returns the evaluated property value.
    template <typename DataType>
    typename PropertyType<DataType>::Traits::ReturnType getPropertyBase(const PropertyType<DataType>& propertyType) const
    {
        typedef typename PropertyType<DataType>::Descriptor Descriptor;
        typedef typename PropertyType<DataType>::Traits Traits;
        typedef typename Descriptor::TypedValueSource TypedValueSource;

        Descriptor* descriptor = propertyType.get();
        kzAssert(descriptor);
        AbstractPropertyTypeDescriptor::ValueSource* topValueSource = getTopValueSource(*descriptor);
        if (topValueSource)
        {
            TypedValueSource* typedValueSource = static_cast<TypedValueSource*>(topValueSource);
            return Traits::read(typedValueSource->value);
        }

        return propertyType.getDefaultValue();
    }

    template <typename DataType>
    void setAbstractProperty(AbstractPropertyType abstractPropertyType, typename PropertyType<DataType>::Traits::ParameterType value)
    {
        DynamicPropertyType<DataType> dynamicPropertyType(abstractPropertyType);
        setProperty(dynamicPropertyType, value);
    }

    template <typename DataType>
    typename PropertyType<DataType>::Traits::ReturnType getAbstractProperty(AbstractPropertyType abstractPropertyType) const
    {
        DynamicPropertyType<DataType> dynamicPropertyType(abstractPropertyType);
        return getProperty(dynamicPropertyType);
    }

    template <typename DataType>
    typename PropertyType<DataType>::Traits::ReturnType getAbstractPropertyBase(AbstractPropertyType abstractPropertyType) const
    {
        DynamicPropertyType<DataType> dynamicPropertyType(abstractPropertyType);
        return getPropertyBase(dynamicPropertyType);
    }

    template <typename DataType>
    optional<typename PropertyType<DataType>::Traits::ReturnType> getOptionalAbstractProperty(AbstractPropertyType abstractPropertyType) const
    {
        DynamicPropertyType<DataType> dynamicPropertyType(abstractPropertyType);
        return getOptionalProperty(dynamicPropertyType);
    }

    void setPropertyFlag(AbstractPropertyType propertyType, uint32_t flag);

    bool isPropertyFlagSet(AbstractPropertyType propertyType, uint32_t flag) const;

    void clearPropertyFlag(AbstractPropertyType propertyType, uint32_t flag);

    /// Evaluates whether there are any inputs into the property value.
    /// Both value sources and modifiers are taken into account.
    /// \param propertyType The property type identifying the property to evaluate.
    /// \return Returns true if there are inputs into the property value, false otherwise.
    bool hasValue(AbstractPropertyType propertyType) const;

    /// Evaluates whether there are any inputs into the property value, disregarding modifiers.
    /// Does not take modifiers into account.
    /// \param propertyType The property type identifying the property to evaluate.
    /// \return Returns true if there are inputs into the property value, false otherwise.
    bool hasBaseValue(AbstractPropertyType propertyType) const;

    /// Evaluates whether there is a local value set for the property. Local values are set with setProperty or loaded from kzb.
    /// \param propertyType The property type identifying the property to evaluate.
    /// \return Returns true if there is a local value for the property.
    bool hasLocalValue(AbstractPropertyType propertyType) const;

    /// Evaluates whether there is a value of any precedence higher than class default value set for the property.
    /// \param propertyType The property type identifying the property to evaluate.
    /// \return Returns true if there is a non-class value for the property.
    bool hasNonClassValue(AbstractPropertyType propertyType) const;

    /// Removes the local value associated with the property.
    /// \param propertyType The property type identifying the property to evaluate.
    void removeLocalValue(AbstractPropertyType propertyType);

    /// Copies local value of single property from another object.
    /// \param other The object from which to copy the value.
    /// \param propertyType Property type to copy.
    void copyLocalValue(const PropertyObject& other, AbstractPropertyType propertyType);

    /// Copies all local values from another object.
    /// \param other The object from which to copy the values.
    void copyLocalValues(const PropertyObject& other);

    /// Virtual function to handle property change notifications.
    /// Classes deriving from Object can override this function to monitor changes of properties.
    /// \param propertyType The property type identifying the property that has changed.
    /// \param reason The reason that caused the property notification to be invoked.
    virtual void onPropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason);

    template <typename DataType>
    void addPropertyValueSource(const PropertyType<DataType>& propertyType, typename PropertyType<DataType>::Descriptor::TypedValueSource* valueSource,
                                PropertyValuePrecedence precedence, void* owner)
    {
        AbstractPropertyTypeDescriptor* descriptor = propertyType.get();
        kzAssert(descriptor);
        addPropertyValueSource(*descriptor, valueSource, precedence, owner);
    }

    template <typename DataType>
    void removePropertyValueSource(const PropertyType<DataType>& propertyType, typename PropertyType<DataType>::Descriptor::TypedValueSource* valueSource, void* owner)
    {
        AbstractPropertyTypeDescriptor* descriptor = propertyType.get();
        kzAssert(descriptor);
        removePropertyValueSource(*descriptor, valueSource, owner);
    }

    template <typename DataType>
    void addPropertyModifier(const PropertyType<DataType>& propertyType, typename PropertyType<DataType>::Descriptor::ModifierCallback callback, void* owner)
    {
        typedef typename PropertyType<DataType>::Descriptor Descriptor;
        typedef typename Descriptor::TypedModifierStorage TypedModifierStorage;
        typedef typename Descriptor::TypedModifierEntry TypedModifierEntry;

        AbstractPropertyTypeDescriptor* descriptor = propertyType.get();
        kzAssert(descriptor);
        PropertyStoragePtr propertyStorage = acquirePropertyStorage(*descriptor);
        kzAssert(propertyStorage);

        AbstractPropertyTypeDescriptor::ModifierStorage* modifierStorage = acquireModifierStorage(*descriptor, *propertyStorage);
        TypedModifierStorage* typedModifierStorage = static_cast<TypedModifierStorage*>(modifierStorage);
        TypedModifierEntry modifierEntry(callback, owner);
        typedModifierStorage->modifierEntries.push_back(modifierEntry);

        validatePropertyModifiersAndNotifyHandlers(propertyStorage);
    }

    template <typename DataType>
    void removePropertyModifier(const PropertyType<DataType>& propertyType, typename PropertyType<DataType>::Descriptor::ModifierCallback callback, void* owner)
    {
        typedef typename PropertyType<DataType>::Descriptor Descriptor;
        typedef typename Descriptor::TypedModifierStorage TypedModifierStorage;
        typedef typename Descriptor::TypedModifierEntry TypedModifierEntry;

        AbstractPropertyTypeDescriptor* descriptor = propertyType.get();
        kzAssert(descriptor);
        PropertyStoragePtr propertyStorage = findPropertyStorage(*descriptor);
        if (!propertyStorage)
        {
            return;
        }

        AbstractPropertyTypeDescriptor::ModifierStorage* modifierStorage = propertyStorage->modifierStorage;
        if (!modifierStorage)
        {
            return;
        }

        TypedModifierStorage* typedModifierStorage = static_cast<TypedModifierStorage*>(modifierStorage);
        TypedModifierEntry modifierEntry(callback, owner);
        erase(typedModifierStorage->modifierEntries, modifierEntry);

        validatePropertyModifiersAndNotifyHandlers(propertyStorage);
    }

    void validatePropertyModifiers(AbstractPropertyType propertyType);

    template <typename DataType>
    void addPropertyNotificationHandler(const PropertyType<DataType>& propertyType, typename PropertyType<DataType>::Descriptor::NotificationCallback callback, void* owner)
    {
        typedef typename PropertyType<DataType>::Descriptor Descriptor;
        typedef typename Descriptor::TypedNotificationStorage TypedNotificationStorage;
        typedef typename Descriptor::TypedNotificationEntry TypedNotificationEntry;

        AbstractPropertyTypeDescriptor* descriptor = propertyType.get();
        kzAssert(descriptor);
        AbstractPropertyTypeDescriptor::NotificationStorage* notificationStorage = acquireNotificationStorage(*descriptor);
        TypedNotificationStorage* typedNotificationStorage = static_cast<TypedNotificationStorage*>(notificationStorage);
        TypedNotificationEntry notificationEntry(callback, owner);
        typedNotificationStorage->notificationEntries.push_back(notificationEntry);
    }

    template <typename DataType>
    void removePropertyNotificationHandler(const PropertyType<DataType>& propertyType, typename PropertyType<DataType>::Descriptor::NotificationCallback callback, void* owner)
    {
        typedef typename PropertyType<DataType>::Descriptor Descriptor;
        typedef typename Descriptor::TypedNotificationStorage TypedNotificationStorage;
        typedef typename Descriptor::TypedNotificationEntry TypedNotificationEntry;
        typedef typename TypedNotificationStorage::NotificationEntryContainer::iterator NotificationEntryIterator;

        AbstractPropertyTypeDescriptor* descriptor = propertyType.get();
        kzAssert(descriptor);
        AbstractPropertyTypeDescriptor::NotificationStorage* notificationStorage = findNotificationStorage(*descriptor);
        if (!notificationStorage)
        {
            return;
        }

        TypedNotificationStorage* typedNotificationStorage = static_cast<TypedNotificationStorage*>(notificationStorage);
        TypedNotificationEntry notificationEntry(callback, owner);

        // If no notifications in progress, remove immediately.
        if (typedNotificationStorage->notificationDepth == 0)
        {
            erase(typedNotificationStorage->notificationEntries, notificationEntry);
        }
        // Otherwise queue for removal by marking as 0.
        else
        {
            for (NotificationEntryIterator it = typedNotificationStorage->notificationEntries.begin(), endIt = typedNotificationStorage->notificationEntries.end(); (it != endIt); ++it)
            {
                if ((*it) == notificationEntry)
                {
                    (*it).notificationCallback = 0;
                    break;
                }
            }
        }
    }

    /// Gets number of current notification handlers for given property type.
    template <typename DataType>
    size_t getPropertyNotificationHandlerCount(const PropertyType<DataType>& propertyType)
    {
        typedef typename PropertyType<DataType>::Descriptor Descriptor;
        typedef typename Descriptor::TypedNotificationStorage TypedNotificationStorage;

        AbstractPropertyTypeDescriptor* descriptor = propertyType.get();
        kzAssert(descriptor);
        AbstractPropertyTypeDescriptor::NotificationStorage* notificationStorage = findNotificationStorage(*descriptor);
        if (!notificationStorage)
        {
            return 0;
        }

        TypedNotificationStorage* typedNotificationStorage = static_cast<TypedNotificationStorage*>(notificationStorage);
        return typedNotificationStorage->notificationEntries.size();
    }

protected:

    void addPropertyValueSource(AbstractPropertyTypeDescriptor& descriptor, AbstractPropertyTypeDescriptor::ValueSource* valueSource, PropertyValuePrecedence precedence, void* owner);

    void removePropertyValueSource(AbstractPropertyTypeDescriptor& descriptor, AbstractPropertyTypeDescriptor::ValueSource* valueSource, void* owner);

    AbstractPropertyTypeDescriptor::ValueSourceEntry* getTopValueSourceEntry(AbstractPropertyTypeDescriptor::PropertyStorage& propertyStorage) const;

    AbstractPropertyTypeDescriptor::ValueSourceEntry* getTopValueSourceEntry(AbstractPropertyTypeDescriptor& descriptor) const;

    AbstractPropertyTypeDescriptor::ValueSource* getTopValueSource(AbstractPropertyTypeDescriptor& descriptor) const;

    AbstractPropertyTypeDescriptor::ValueSource* getFinalValueSource(AbstractPropertyTypeDescriptor& descriptor) const;

    AbstractPropertyTypeDescriptor::ValueSource* getNonClassValueSource(AbstractPropertyTypeDescriptor& descriptor) const;

    AbstractPropertyTypeDescriptor::ValueSource* getClassValueSource(AbstractPropertyTypeDescriptor& descriptor) const;

    AbstractPropertyTypeDescriptor::ValueSourceEntry* findLocalValueSourceEntry(AbstractPropertyTypeDescriptor::PropertyStorage& propertyStorage);

    AbstractPropertyTypeDescriptor::ValueSourceEntry* constructLocalValueSourceEntry(AbstractPropertyTypeDescriptor& descriptor, AbstractPropertyTypeDescriptor::PropertyStorage& propertyStorage);

    AbstractPropertyTypeDescriptor::ValueSourceEntry* acquireLocalValueSourceEntry(AbstractPropertyTypeDescriptor& descriptor, PropertyStoragePtr& propertyStorage);

    AbstractPropertyTypeDescriptor::PropertyStorage* findPropertyStorage(AbstractPropertyTypeDescriptor& descriptor) const;

    /// Gets property storage intrusive pointer that can be used to hold a reference until end of operation.
    /// \param descriptor Descriptor to look with.
    /// \return Intrusive pointer to property storage.
    PropertyStoragePtr findPropertyStoragePtr(AbstractPropertyTypeDescriptor& descriptor) const;

    PropertyStoragePtr constructPropertyStorage(AbstractPropertyTypeDescriptor& descriptor);

    PropertyStoragePtr acquirePropertyStorage(AbstractPropertyTypeDescriptor& descriptor);

    AbstractPropertyTypeDescriptor::ModifierStorage* acquireModifierStorage(AbstractPropertyTypeDescriptor& descriptor, AbstractPropertyTypeDescriptor::PropertyStorage& propertyStorage);

    AbstractPropertyTypeDescriptor::ModifierStorage* findModifierStorage(AbstractPropertyTypeDescriptor& descriptor);

    AbstractPropertyTypeDescriptor::NotificationStorage* acquireNotificationStorage(AbstractPropertyTypeDescriptor& descriptor);

    AbstractPropertyTypeDescriptor::NotificationStorage* findNotificationStorage(AbstractPropertyTypeDescriptor& descriptor);

    AbstractPropertyTypeDescriptor* findPropertyTypeDescriptorByUnqualifiedNameAndDataType(string_view unqualifiedName, PropertyDataType dataType);

    void validatePropertyModifiersAndNotifyHandlers(PropertyStoragePtr& propertyStorage);

    /// Copy local value from property storage.
    /// \param propertyStorage Property storage to copy from.
    void copyLocalValue(const AbstractPropertyTypeDescriptor::PropertyStorage& otherPropertyStorage);

    PropertyStorageContainer::iterator beginPropertyStorage()
    {
        return begin(m_properties);
    }

    PropertyStorageContainer::iterator endPropertyStorage()
    {
        return end(m_properties);
    }

    virtual void notifyPropertyHandlers(PropertyStoragePtr& propertyStorage, PropertyNotificationReason reason);

    void onCopy(const PropertyObject& other);

private:

    PropertyObject(const PropertyObject& other) KZ_DELETED_FUNCTION;
    PropertyObject& operator=(const PropertyObject& other) KZ_DELETED_FUNCTION;

    /// All properties within the object.
    /// Properties are stored in intrusive pointers, so that property notifications can destroy the object
    /// (without the notification handlers being executed becoming invalid).
    PropertyStorageContainer m_properties;
};

/// ClassPropertyDefaultValue is a helper for installing property values as class metadata.
template <typename TDataType>
class ClassPropertyDefaultValue : public PropertyType<TDataType>::Descriptor::TypedValueSource
{
public:

    explicit ClassPropertyDefaultValue(PropertyObject& thisObject, const PropertyType<TDataType>& propertyType, const TDataType& value)
    {
        this->value = value;
        thisObject.addPropertyValueSource(propertyType, this, PropertyValuePrecedenceClass, this);
    }

private:

    ClassPropertyDefaultValue(const ClassPropertyDefaultValue&) KZ_DELETED_FUNCTION;
    ClassPropertyDefaultValue& operator=(const ClassPropertyDefaultValue&) KZ_DELETED_FUNCTION;
};

}

#endif
