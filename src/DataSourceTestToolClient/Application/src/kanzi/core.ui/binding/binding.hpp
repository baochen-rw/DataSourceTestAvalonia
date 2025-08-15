// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KANZI_BINDING_RULE_HPP
#define KANZI_BINDING_RULE_HPP

#include "binding_processor.hpp"

#include <kanzi/core.ui/data/data_object.hpp>
#include <kanzi/core.ui/data/data_source.hpp>
#include <kanzi/core.ui/node/content_reference.hpp>
#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/property/abstract_property_notification_handler.hpp>
#include <kanzi/core.ui/property/variant.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>

namespace kanzi
{

/// Binary container type.
enum KzuPropertyBinaryDataType
{
    KZU_BINARY_DATA_TYPE_FLOAT = 0,
    KZU_BINARY_DATA_TYPE_TEXTURE = 1,
    KZU_BINARY_DATA_TYPE_MATRIX4X4 = 2
};

/// Binary target attribute type.
enum KzuPropertyBinaryTargetAttribute
{
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_TRANSLATION_X = 0,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_TRANSLATION_Y = 1,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_TRANSLATION_Z = 2,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_SCALE_X = 3,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_SCALE_Y = 4,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_SCALE_Z = 5,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_ROTATION_Z = 6,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_ROTATION_Y = 7,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_ROTATION_X = 8,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_WHOLE_PROPERTY = 9,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_COLOR_R = 10,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_COLOR_G = 11,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_COLOR_B = 12,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_COLOR_A = 13,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_VECTOR_X = 14,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_VECTOR_Y = 15,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_VECTOR_Z = 16,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_VECTOR_W = 17,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_SCALE = 18,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_ROTATION = 19,
    KZU_PROPERTY_BINARY_TARGET_ATTRIBUTE_TRANSLATION = 20
};


class MessageArguments;
class Node;
class Domain;
class Binding;
class DataObject;
class DataContext;
struct BindingExpressionOpCode;

typedef shared_ptr<Binding> BindingSharedPtr;
typedef shared_ptr<Binding const> BindingSharedConstPtr;
typedef shared_ptr<DataObject> DataObjectSharedPtr;
typedef shared_ptr<DataContext> DataContextSharedPtr;


struct BindingOperation;
typedef shared_ptr<BindingOperation> BindingOperationSharedPtr;


/// Base class for binding operations.
struct KANZI_API BindingOperation
{
    /// Attaches operation in binding.
    ///
    /// \param binding Owning binding.
    virtual void attach(Binding& binding) = 0;

    /// Detaches operation in binding.
    virtual void detach() = 0;

    /// Executes operation.
    virtual void execute() = 0;

    /// Clones operation.
    ///
    /// \return Cloned operation.
    virtual BindingOperationSharedPtr clone() = 0;
};


/// Binding objects establish connections between properties, message values or arguments.
///
/// When the data in the source connection is modified the binding propagates the value to the target connection.
/// While the data is propagated the binding passes it through the optional chain of processors that can modify the value or reject the update.
class KANZI_API Binding : public Object
{
public:

    typedef vector<BindingProcessorSharedPtr> BindingProcessorVector;
    typedef BindingProcessorVector::const_iterator BindingProcessorIterator;

    /** Binding mode enumeration. */
    enum Mode
    {
        /// One way binding.
        ModeOneWay = 1,

        /// Two way binding.
        ModeTwoWay = 2
    };

    /// Write mode, what should the binding do with the result value?
    enum WriteMode
    {
        /// Write a property (default).
        WriteModeProperty = 0,

        /// Install a modifier.
        WriteModeModifier = 1,

        /// Install a value source.
        WriteModeValueSource = 2
    };

    /// Creates a binding object.
    static BindingSharedPtr create(Domain* domain);

    /** Helper to create a property-to-property binding rule object.
     * \param memoryManager The memory manager to use for allocations.
     * \param domain The UI domain.
     * \param sourcePath An object path pointing to the source object that has the source property. This can be relative to the target property owner.
     * \param sourcePropertyType ::KzuPropertyType of the source property.
     * \param sourceField Field of the source property to bind or ::PropertyFieldWhole for the whole property.
     * \param targetPropertyType ::KzuPropertyType of the target property.
     * \param targetField Field of the target property to bind or ::PropertyFieldWhole for the whole property.
     * \param out_rule A pointer that is set to point to the new KzuBindingRule.
     * \return ::KZS_SUCCESS on success.
     */
    static BindingSharedPtr create(Domain* domain, string_view objectPath, AbstractPropertyType sourcePropertyType, PropertyField sourceField,
                                   AbstractPropertyType targetPropertyType, PropertyField targetField);

    static BindingSharedPtr create(Domain* domain, ResourceID resourceName, AbstractPropertyType propertyType);

    /// Helper to create a data object-to-property binding object.
    /// The object path specified here is passed to addDataSourceProperty(), and is a relative path from the root data source.
    /// If the data object path in studio would be {DataContext.path.to.object}, the string passed here should be "path.to.object".
    /// \param domain The UI domain.
    /// \param objectPath A relative path pointing from current data context to the source data object.
    /// \param targetPropertyType Type of the property used as binding target.
    /// \param targetField Field of the target property to bind or ::PropertyFieldWhole for the whole property.
    /// \return Resulting binding object.
    static BindingSharedPtr createFromDataObjectPath(Domain* domain, string_view objectPath, AbstractPropertyType targetPropertyType, PropertyField targetField);

    /// Sets binding mode.
    void setMode(Mode mode);
    /// Gets binding mode.
    Mode getMode() const;

    /// Sets binding write mode.
    void setWriteMode(WriteMode mode);
    /// Gets binding write mode.
    WriteMode getWriteMode() const
    {
        return m_writeMode;
    }

    /// Sets precedence (for value source write mode).
    void setPrecedence(optional<PropertyValuePrecedence> precedence);
    /// Gets precedence (for value source write mode).
    optional<PropertyValuePrecedence> getPrecedence() const
    {
        return m_precedence;
    }

    /** Set up source rule to specify a value. */
    void setSourceValue(const Variant& value);
    /** Set up source rule to specify an object property.
     * \param rule The binding rule which source property is specified.
     * \param objectPath Object path leading to the source object node, relative to the target object node.
     * \param propertyType The property type in the source object node.
     * \param field Field to bind in the property or ::PropertyFieldWhole for the whole property.
     * \return ::KZS_SUCCESS on success.
     */
    void setSourceDynamicObjectProperty(string_view objectPath, AbstractPropertyType propertyType, PropertyField field);
    /** Adds or a source property as the source rule. It is possible to add multiple sources with this function. */
    void addSourceDynamicObjectProperty(string_view objectPath, AbstractPropertyType propertyType, PropertyField field);
    /** Set up source rule to specify a message argument. */
    void setSourceMessageArgument(AbstractPropertyType argumentType, PropertyField field);
    /// Set up source as a resource object.
    void setSourceResource(ResourceID id);
    /// Adds a data source property as the source rule. It is possible to add multiple sources with this function.
    /// \param objectPath Relative path to data source from the root data source.
    void addDataSourceProperty(string_view objectPath);
    /** Set a zero source binding. */
    void setZeroSource();


    /** Set up target rule to specify an object property.
     * \param rule The binding rule which target property is specified.
     * \param objectPath Object path leading to the target object node, relative to the target object node.
     * \param propertyType The property type in the target object node.
     * \param field Field to bind in the property or ::PropertyFieldWhole for the whole property.
     * \return ::KZS_SUCCESS on success.
     */
    void setTargetDynamicObjectProperty(string_view objectPath, AbstractPropertyType propertyType, PropertyField field);
    /** Set up target rule to specify a message argument. */
    void setTargetMessageArgument(AbstractPropertyType argumentType, PropertyField field);

    /** Read values from sourceMessage and store them in rule's internal cache. */
    bool read(Node* currentObjectNode, const MessageArguments* sourceMessage);
    /// Save the cached value from the rule to targetMessage if it has one cached.
    /// Implicitly installs modifier of value source writers if necessary.
    bool write(Node* currentObjectNode, MessageArguments* targetMessage);
    /** Read values from sourceMessage and write them to targetMessage if the binding rule type is a message argument
     * to message argument. Otherwise updates the binding depending on its type (e.g. property to property, variant to property).
     * \param rule The binding rule to update.
     * \param currentObjectNode The object node for which the binding rule object paths are relative to.
     * \param sourceMessage The source message or ::KZ_NULL.
     * \param targetMessage The target message or ::KZ_NULL.
     * \param out_updated A pointer to a Boolean that is set to ::KZ_TRUE if the rule was updated, otherwise it is set to ::KZ_FALSE.
     * \return ::KZS_SUCCESS on success. ::KZS_ERROR_ENUM_OUT_OF_RANGE if the binding source type is invalid.
     */
    bool update(Node* currentObjectNode, const MessageArguments* sourceMessage, MessageArguments* targetMessage);
    /** Update the source value in binding. */
    bool updateSource(Node* currentObjectNode, MessageArguments* sourceMessage, const MessageArguments* targetMessage);
    /** Read the target value. */
    bool readTargetValue(Variant* value);
    /** Returns the source value from rule's internal cache. This is an internal Kanzi function. */
    const Variant* getCachedSourceValue() const;

    /** Add a validator object. */
    void addValidator(BindingProcessorSharedPtr processor);
    /** Remove a validator object. */
    void removeValidator(const BindingProcessor& processor);

    BindingProcessorIterator beginBindingProcessors() const { return m_validators.begin(); }
    BindingProcessorIterator endBindingProcessors() const { return m_validators.end(); }

    /** Gets the number of source registers in binding rule. */
    size_t getSourceRegisterCount() const;
    /** Gets the number of constant registers in binding rule. */
    size_t getConstantRegisterCount() const;
    /** Gets the number of temporary registers in binding rule. */
    size_t getTemporaryRegisterCount() const;
    /** Gets the number of data source registers in binding rule. */
    size_t getDataSourceRegisterCount() const;

    /** Attach binding. This is Kanzi-internal function, use Node::addBinding() instead. */
    void attach(Node* objectNode);
    /** Detach binding. This is Kanzi-internal function, use Node::addBinding() instead. */
    void detach();
    /** Get the object node the rule is attached to, if any. */
    Node* getAttachedNode() const;

    /** Add a constant value to the binding. */
    void addConstantRegister(const Variant& constant);
    /// Set constant register at given index.
    void setConstantRegister(size_t index, const Variant& constant);
    /** Set the number of temporaries for the binding. */
    void setTemporaryRegisterCount(size_t count);

    /** Get access to source register. */
    const Variant* getSourceRegister(size_t index) const;
    /** Get access to constant register. */
    const Variant* getConstantRegister(size_t index) const;
    /** Get access to temporary register. */
    Variant* getTemporaryRegister(size_t index);
    /** Get access to data source register. */
    const Variant* getDataSourceRegister(size_t index) const;

    /** Returns target property type and property field of the binding rule if it is writing to property. */
    bool getTargetPropertyType(AbstractPropertyType& out_targetPropertyType, PropertyField& out_field) const;


    virtual ~Binding();

    /// Copies a binding object.
    BindingSharedPtr copy() const;

    /// Tells if this binding is attached.
    bool isAttached() const
    {
        return m_objectNode ? true : false;
    }

    /// Adds operation to the binding.
    /// Operations are executed in order in which they are added to the binding 
    /// when binding is invoked.
    ///
    /// \param operation Operation.
    void addOperation(BindingOperationSharedPtr operation);

    /// Sets the template root of this binding.
    /// Template root is used template root bindings.
    /// This is an internal function.
    void setTemplateRoot(NodeSharedPtr templateRoot)
    {
        m_templateRoot = templateRoot;
    }

    /// Gets the template root of this binding.
    /// Template root is used template root bindings.
    /// This is an internal function.
    NodeSharedPtr getTemplateRoot() const
    {
        return m_templateRoot.lock();
    }

    /// Gets the Resource ID, if the source is a ResourceSource.
    /// \return Source Resource ID if source is ResourceSource, else nullopt.
    optional<ResourceID> getIdIfResourceSource() const;

private:
    /// Property writer.
    class PropertyWriter
    {
    public:

        /// Destructor.
        virtual ~PropertyWriter()
        {
        }

        /// Assign variant value to the optional value within.
        virtual void assign(const Variant& variant) = 0;

        /// Write saved value. To be overwritten by implementing class.
        virtual void write() = 0;

        /// Gets object the modifier has been installed for.
        PropertyObject* getObject()
        {
            return m_object;
        }

    protected:

        /// Constructor.
        explicit PropertyWriter(PropertyObject* object, AbstractPropertyType propertyType, PropertyField field) :
            m_object(object),
            m_propertyType(propertyType),
            m_field(field)
        {
        }

    protected:

        /// Weak reference to target object.
        PropertyObject* m_object;

        /// Abstract property type the modifier has been installed for.
        AbstractPropertyType m_propertyType;

        /// Property field for property type.
        PropertyField m_field;
    };

    /// Property modifier writer.
    template <typename T>
    class PropertyModifierWriter : public PropertyWriter
    {
    public:

        /// Constructor.
        explicit PropertyModifierWriter(PropertyObject* object, AbstractPropertyType propertyType, PropertyField field, const Variant& value) :
            PropertyWriter(object, propertyType, field)
        {
            assign(value);

            DynamicPropertyType<T> dynamicPropertyType(m_propertyType);

            m_object->addPropertyModifier(dynamicPropertyType, modifierCallback, this);
        }

        /// Destructor.
        virtual ~PropertyModifierWriter()
        {
            uninstallModifier();
        }

        /// PropertyModifierWriter::assign() implementation.
        virtual void assign(const Variant& variant) KZ_OVERRIDE
        {
            if (!variant.empty())
            {
                // Attempt cast if data types do not match.
                PropertyDataType targetType = m_propertyType.getDataType();
                if (kzuVariantGetType(&variant) != targetType)
                {
                    kzBool castSuccessful;
                    Variant targetValue;
                    kzsError result = kzuVariantCast(&targetValue, targetType, &variant, &castSuccessful);
                    kzThrowIfError(result);

                    if (castSuccessful)
                    {
                        m_value = get<T>(targetValue);
                        return;
                    }
                }
                // Data types match.
                else
                {
                    m_value = get<T>(variant);
                    return;
                }
            }

            // Empty value or unsuccessful.
            m_value = nullopt;
        }

        /// PropertyModifierWriter::write() implementation.
        virtual void write() KZ_OVERRIDE
        {
            kzAssert(m_object);
            m_object->validatePropertyModifiers(m_propertyType);
        }

    private:

        /// Modifier callback to be installed.
        static void modifierCallback(PropertyObject& /*object*/, typename PropertyDataTypeTraits<T>::StorageType& storage,
            PropertyNotificationReason reason, void* owner)
        {
            PropertyModifierWriter<T>* propertyModifierWriter = static_cast<PropertyModifierWriter<T>*>(owner);

            if (reason == PropertyNotificationReasonChanged)
            {
                if (propertyModifierWriter->m_value)
                {
                    storage = *(propertyModifierWriter->m_value);
                }
            }
            else
            {
                propertyModifierWriter->uninstallModifier();
            }
        }

        void uninstallModifier()
        {
            if(m_object)
            {
                DynamicPropertyType<T> dynamicPropertyType(m_propertyType);

                m_object->removePropertyModifier(dynamicPropertyType, modifierCallback, this);
                m_object = 0;
            }
        }

    private:

        /// Value to write for the modifier.
        optional<T> m_value;
    };

    /// Property value source writer.
    template <typename T>
    class PropertyValueSourceWriter : public PropertyWriter
    {
    public:

        /// Constructor.
        explicit PropertyValueSourceWriter(Object* object, AbstractPropertyType propertyType, PropertyField field, PropertyValuePrecedence precedence, const Variant& value) :
            PropertyWriter(object, propertyType, field)
        {
            assign(value);

            DynamicPropertyType<T> dynamicPropertyType(propertyType);

            m_object->addPropertyValueSource(dynamicPropertyType, &m_valueSource, precedence, this);
        }

        /// Destructor.
        virtual ~PropertyValueSourceWriter()
        {
            uninstallValueSource();
        }

        /// PropertyModifierWriter::assign() implementation.
        virtual void assign(const Variant& variant) KZ_OVERRIDE
        {
            if (!variant.empty())
            {
                // Attempt cast if data types do not match.
                PropertyDataType targetType = m_propertyType.getDataType();
                if (kzuVariantGetType(&variant) != targetType)
                {
                    kzBool castSuccessful;
                    Variant targetValue;
                    kzsError result = kzuVariantCast(&targetValue, targetType, &variant, &castSuccessful);
                    kzThrowIfError(result);

                    if (castSuccessful)
                    {
                        m_valueSource.value = get<T>(targetValue);
                        return;
                    }
                }
                // Data types match.
                else
                {
                    m_valueSource.value = get<T>(variant);
                    return;
                }
            }
        }

        /// PropertyModifierWriter::write() implementation.
        virtual void write() KZ_OVERRIDE
        {
            // Validate modifiers since they may depend on value sources.
            m_object->validatePropertyModifiers(m_propertyType);
        }

    private:

        void uninstallValueSource()
        {
            if (m_object)
            {
                DynamicPropertyType<T> dynamicPropertyType(m_propertyType);

                m_object->removePropertyValueSource(dynamicPropertyType, &m_valueSource, this);
                m_object = 0;
            }
        }

        /// Value source to be added.
        typename PropertyTypeDescriptor<T>::TypedValueSource m_valueSource;
    };

    template<typename T>
    static PropertyWriter* createPropertyWriter(Object* object, AbstractPropertyType propertyType, PropertyField field,
                                                optional<PropertyValuePrecedence> precedence, const Variant& variant)
    {
        if (precedence)
        {
            return new PropertyValueSourceWriter<T>(object, propertyType, field, *precedence, variant);
        }
        else
        {
            return new PropertyModifierWriter<T>(object, propertyType, field, variant);
        }
    }

    /// Create property modifier writer 
    static unique_ptr<Binding::PropertyWriter> createPropertyWriterFrom(Object* object, AbstractPropertyType propertyType,
                                                                        PropertyField field, optional<PropertyValuePrecedence> precedence,
                                                                        const Variant& variant)
    {
        unique_ptr<PropertyWriter> writer;

        if (!variant.empty())
        {
            PropertyDataType dataType = propertyType.getDataType();
            switch (dataType)
            {
                case PropertyDataTypeFloat:
                {
                    writer.reset(createPropertyWriter<float>(object, propertyType, field, precedence, variant));
                    break;
                }
                case PropertyDataTypeInt:
                {
                    writer.reset(createPropertyWriter<int>(object, propertyType, field, precedence, variant));
                    break;
                }
                case PropertyDataTypeBool:
                {
                    writer.reset(createPropertyWriter<bool>(object, propertyType, field, precedence, variant));
                    break;
                }
                case PropertyDataTypeColor:
                {
                    writer.reset(createPropertyWriter<ColorRGBA>(object, propertyType, field, precedence, variant));
                    break;
                }
                case PropertyDataTypeVector2:
                {
                    writer.reset(createPropertyWriter<Vector2>(object, propertyType, field, precedence, variant));
                    break;
                }
                case PropertyDataTypeVector3:
                {
                    writer.reset(createPropertyWriter<Vector3>(object, propertyType, field, precedence, variant));
                    break;
                }
                case PropertyDataTypeVector4:
                {
                    writer.reset(createPropertyWriter<Vector4>(object, propertyType, field, precedence, variant));
                    break;
                }
                case PropertyDataTypeMatrix3x3:
                {
                    writer.reset(createPropertyWriter<Matrix3x3>(object, propertyType, field, precedence, variant));
                    break;
                }
                case PropertyDataTypeMatrix4x4:
                {
                    writer.reset(createPropertyWriter<Matrix4x4>(object, propertyType, field, precedence, variant));
                    break;
                }
                case PropertyDataTypeString:
                {
                    writer.reset(createPropertyWriter<string>(object, propertyType, field, precedence, variant));
                    break;
                }
                case PropertyDataTypeResource:
                {
                    writer.reset(createPropertyWriter<ResourceSharedPtr>(object, propertyType, field, precedence, variant));
                    break;
                }
                case PropertyDataTypeSRT2D:
                {
                    writer.reset(createPropertyWriter<SRTValue2D>(object, propertyType, field, precedence, variant));
                    break;
                }
                case PropertyDataTypeSRT3D:
                {
                    writer.reset(createPropertyWriter<SRTValue3D>(object, propertyType, field, precedence, variant));
                    break;
                }
                case PropertyDataTypePointer:
                default:
                {
                    kzThrowException(logic_error("unknown variant data type for property modifier writer: " + to_string(dataType)));
                }
            }
        }

        return KZ_MOVE_RET(unique_ptr<PropertyWriter>, writer);
    }

    /// Install new property writer.
    /// Property modifier writer or property value source writer is installed depending on whether precedence is set.
    /// \param object Object to install for.
    /// \param variant Property value to write.
    void installPropertyWriter(Object* object, optional<PropertyValuePrecedence> precedence, const Variant& variant);

    /// Wrapper for property writer installation.
    /// Installs property modifier writer.
    void installPropertyModifierWriter(Object* object, const Variant& variant)
    {
        kzAssert(!m_precedence);
        installPropertyWriter(object, nullopt, variant);
    }

    /// Wrapper for property writer installation.
    /// Installs property value source writer using current precedence.
    void installPropertyValueSourceWriter(Object* object, const Variant& variant)
    {
        kzAssert(m_precedence);
        installPropertyWriter(object, m_precedence, variant);
    }

    friend class DataContextListener;

    void onCopy(const Binding& other);

    explicit Binding(Domain* domain);

    /** Object property binding information. */
    struct ObjectPropertyInfo
    {
        explicit ObjectPropertyInfo(Binding* binding, string_view objectPath, AbstractPropertyType propertyType, PropertyField field) :
            binding(binding),
            objectPath(objectPath),
            propertyType(propertyType),
            field(field),
            objectNode(0),
            globalListenersInstalled(false),
            connected(false)
        {
        }

        Binding* binding;         /**< Binding rule. */
        string objectPath;                 /**< Object path. */
        AbstractPropertyType propertyType; /**< Property type. */
        PropertyField field;                /**< Property field. */
        Node* objectNode;           /**< Object node. */
        Variant value;                   /**< Current value. */
        bool globalListenersInstalled;            /**< Flag if global listeners have been installed. */
        bool connected;
    };

    struct ValueSource
    {
        explicit ValueSource(const Variant& value) :
            value(value)
        {
        }

        Variant value;
    };

    struct MessageArgumentSource
    {
        explicit MessageArgumentSource(AbstractPropertyType argumentType, PropertyField field) :
            argumentType(argumentType),
            field(field)
        {
        }

        AbstractPropertyType argumentType; /**< Argument type. */
        PropertyField field;                /**< Argument field. */
    };

    struct ObjectPropertySource
    {
        ObjectPropertySource() : m_connectedSourceCount(0)
        {
        }

#if defined(__ghs__) || defined(QNX) || defined(__GNUC__)
        ObjectPropertySource& operator=(const ObjectPropertySource& source)
        {
            m_sources = source.m_sources;
            m_connectedSourceCount = source.m_connectedSourceCount;

            return *this;
        }
#endif

        vector<ObjectPropertyInfo> m_sources; /**< Binding source properties. */
        size_t m_connectedSourceCount;                /**< How many sources connected. */
    };

    struct ResourceSource
    {
        typedef ContentReference<Resource> ResourceListener;
        typedef shared_ptr<ResourceListener> ResourceListenerSharedPtr;

        explicit ResourceSource(Binding* binding, ResourceID id) : binding(binding), id(id)
        {
        }

        void update()
        {
            binding->update(binding->getAttachedNode(), 0, 0);
        }

#ifdef KZ_USE_MOVE_EMULATION
        ResourceSource& operator=(const ResourceSource& source)
        {
            // This handwritten implementation is required due to limitations of Boost.Move that is used in ResourceID. In C++11 it can be removed.
            binding = source.binding;
            id = source.id;
            resourceListener = source.resourceListener;

            return *this;
        }
#endif

        Binding* binding;
        ResourceID id;
        ResourceListenerSharedPtr resourceListener;
    };

    struct DataObjectSource
    {
        explicit DataObjectSource(Binding* binding, string_view objectPath) :
            binding(binding), objectPath(objectPath) {}

        Binding* binding;           /**< Binding rule. */
        string objectPath;          /**< Object path. */
        Variant value;              /**< Current value. */

        DataObjectSharedPtr dataObject;
        DataContextSharedPtr dataContext;
        DataSource::ModifiedSubscriptionToken sourceSubscription;
        DataObject::ModifiedSubscriptionToken objectSubscription;
    };

    typedef variant<monostate, ValueSource, MessageArgumentSource, ObjectPropertySource, ResourceSource> Source;

    struct MessageArgumentTarget
    {
        explicit MessageArgumentTarget(AbstractPropertyType argumentType, PropertyField field) :
            argumentType(argumentType),
            field(field)
        {
        }

        AbstractPropertyType argumentType; /**< Argument type. */
        PropertyField field;                /**< Argument field. */
    };

    struct ObjectPropertyTarget
    {
        explicit ObjectPropertyTarget(Binding* bindingRule, string_view objectPath, AbstractPropertyType propertyType, PropertyField field) :
            info(bindingRule, objectPath, propertyType, field)
        {
        }

        ObjectPropertyInfo info;
    };

    typedef variant<monostate, MessageArgumentTarget, ObjectPropertyTarget> Target;

    struct SourceReadVisitor;
    struct TargetWriteVisitor;
    struct TargetReadVisitor;
    struct SourceWriteVisitor;

    bool kzuBindingSourceRead_internal(Variant* value, Node* currentObjectNode, const MessageArguments* message);

    bool kzuBindingTargetRead_internal(Variant* value, Node* currentObjectNode, const MessageArguments* message);
    bool kzuBindingTargetWrite_internal(Node* currentObjectNode, MessageArguments* message) const;
    bool kzuBindingSourceWrite_internal(const Variant* value, Node* currentObjectNode, MessageArguments* message) const;
    void kzuBindingRuleDeleteSource_internal();
    void kzuBindingRuleDeleteTarget_internal();
    void kzuBindingRuleInstallTargetListeners_internal(ObjectPropertyInfo* info);
    void kzuBindingRuleUninstallTargetListeners_internal(ObjectPropertyInfo* info);

    static void kzuBindingRuleInstallGlobalListeners_internal(ObjectPropertyInfo* info);
    static void kzuBindingRuleUninstallGlobalListeners_internal(ObjectPropertyInfo* info);

    static void kzuBindingRuleInstallSourceListeners_internal(ObjectPropertyInfo* info);
    static void kzuBindingRuleUninstallSourceListeners_internal(ObjectPropertyInfo* info);

    static void kzuBindingRuleGlobalPathChangeCallback_internal(PropertyObject& object, const string&, PropertyNotificationReason, void* userData);
    static void kzuBindingRuleSourcePathChangeCallback_internal(PropertyObject& object, const string&, PropertyNotificationReason, void* userData);

    template <typename T>
    static void togglePropertyNotificationHandler(ObjectPropertyInfo* info, bool source, bool add);

    static void togglePropertyNotificationHandler(ObjectPropertyInfo* info, bool source, bool add);

    template <typename T>
    static void kzuBindingRuleSourcePropertyChangeCallback_internal(PropertyObject&, const typename PropertyType<T>::Traits::StorageType&, PropertyNotificationReason reason, void* userData);
    template <typename T>
    static void kzuBindingRuleTargetPropertyChangeCallback_internal(PropertyObject&, const typename PropertyType<T>::Traits::StorageType&, PropertyNotificationReason reason, void* userData);

    static void updateSourceConnection_internal(ObjectPropertyInfo* info);
    void updateSourceConnections_internal();
    void kzuBindingRuleDisconnectSourceConnections_internal();
    bool kzuBindingRuleAreAllSourcesConnected_internal() const;

    void installResourceReference();
    void uninstallResourceReference();

    void installDataContextListener();
    void uninstallDataContextListener();
    void connectDataContext(DataObjectSource& source);

    void disconnectDataContext(DataObjectSource& source);
    void onDataChanged();
    void onDataObjectChanged();

    static void newSourceResolved(ObjectPropertyInfo* info, Node* sourceNode);

    /// Attached object node.
    Node* m_objectNode;
    /// Binding mode.
    Mode m_mode;
    /// Write mode.
    WriteMode m_writeMode;
    /// Precedence (if #m_writeMode is "#WriteModeValueSource).
    optional<PropertyValuePrecedence> m_precedence;
    /// Source rule.
    Source m_source;
    /// Target rule.
    Target m_target;
    /// Flag to prevent reentrancy in circular bindings.
    bool m_reentranceGuard;
    /// Template root of the prefab instance.
    NodeWeakPtr m_templateRoot;

    /// Property modifier writer.
    unique_ptr<PropertyWriter> m_propertyWriter;

    vector<DataObjectSource> m_dataObjectSources;
    AbstractPropertyNotificationHandlerSharedPtr dataContextListener;

    vector<Variant> m_constantRegisters;  /**< Constant registers. */
    vector<Variant> m_temporaryRegisters; /**< Temporary registers. */
    Variant m_temporaryRegister0;      /**< Temporary register 0 that is always available. */

    BindingProcessorVector m_validators; /**< Validator objects inside this binding rule. */

    typedef vector<BindingOperationSharedPtr> OperationContainer;
    OperationContainer m_operations;
};


/** Loads a binding from stream. */
KANZI_API BindingSharedPtr loadBinding(KzcInputStream* inputStream, Domain* domain, const KzuBinaryFileInfo* file);


/// Loads binding from KZB.
///
/// \param kzbFile KZB file to load bindings from.
/// \param parser Parser to read bindings from.
/// \return Binding.
KANZI_API BindingSharedPtr loadBinding(KzbFile& kzbFile, KzbMemoryParser& parser);

/// Loads bindings from KZB.
///
/// \param kzbFile KZB file to load bindings from.
/// \param parser Parser to read bindings from.
/// \param bindings Bindings container where loaded bindings are stored.
KANZI_API void loadBindings(KzbFile& kzbFile, KzbMemoryParser& parser, vector<BindingSharedPtr>& bindings);


/** Converts a property attribute to a field. */
KANZI_API PropertyField kzuBindingFieldFromBinaryAttribute(KzuPropertyBinaryTargetAttribute attribute);

}


#endif
