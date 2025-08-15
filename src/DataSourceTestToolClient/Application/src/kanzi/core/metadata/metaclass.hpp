// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_METACLASS_HPP
#define KZ_METACLASS_HPP

#include <kanzi/core/error/exception.hpp>
#include <kanzi/core/message/message_type.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/type_traits.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/cpp/map.hpp>
#include <kanzi/core/cpp/iterator.hpp>
#include <kanzi/core/property/property_type.hpp>
#include <kanzi/core/string/fixed_string.hpp>
#include <kanzi/core/metadata/metamethod.hpp>

#include <kanzi/core/cpp/stdexcept.hpp>

#ifndef SPANSION
#define KZ_FEATURE_FULL_METADATA
#endif

namespace kanzi
{

class MetaObject;
class Domain;
class ObjectFactory;


/// Metaclass provides type inspection mechanism for Kanzi classes.
///
/// Classes deriving from Object can register information about their type, properties, methods, messages by using Metaclass and accompanying macros.
/// Such information is used by serialization, scripting and to display friendly type information in Kanzi Studio.
///
/// Use KZ_METACLASS_BEGIN and KZ_METACLASS_END inside your class body to declare a metaclass. Serialization and functions instantiating objects use metaclass name to identify types.
/// Use KZ_METACLASS_PROPERTY_TYPE to register a property type of your class to the metaclass.
/// Use KZ_METACLASS_MESSAGE_TYPE to register a message type of your class to the metaclass.
/// Use KZ_METACLASS_METHOD to register a MetaMethod of your class to the metaclass.
class KANZI_API Metaclass
{
    typedef vector<AbstractPropertyType> PropertyTypeContainer;
    typedef vector<AbstractMessageType> MessageTypeContainer;
    typedef vector<const Metaclass*> MetaclassContainer;
    typedef unordered_map<string_view, const MetaMethod*> MetaMethodContainer;

public:

    /// Checks whether this metaclass describes the class of an object instance.
    virtual bool isMetaclassOf(const MetaObject& object) const = 0;

    virtual shared_ptr<MetaObject> create(Domain* domain, string_view name) const = 0;

    /// Creates an instance of a class this metaclass describes.
    template <typename Type>
    shared_ptr<Type> create(Domain* domain, string_view name) const
    {
        return dynamic_pointer_cast<Type>(create(domain, name));
    }

    /// Returns true if the class described by the metaclass is abstract, false otherwise.
    bool isAbstract() const
    {
        return m_abstract;
    }

    /// Internal function.
    bool isSealed() const
    {
#if defined KZ_FEATURE_FULL_METADATA
        return m_sealed;
#else
        return true;
#endif
    }

    /// Internal function.
    void seal()
    {
#if defined KZ_FEATURE_FULL_METADATA
        checkSealed();

        m_sealed = true;
#endif
    }

    /// Returns the metaclass of the base class.
    const Metaclass* getBase() const
    {
        return m_baseClass;
    }

    /// Determines whether the class this metaclass describes derives from a class described by specified metaclass.
    bool isDerivedFrom(const Metaclass* metaclass) const
    {
        bool result = false;
        const Metaclass* testedMetaclass = this;

        while (testedMetaclass)
        {
            if (testedMetaclass == metaclass)
            {
                result = true;
                break;
            }

            testedMetaclass = testedMetaclass->getBase();
        }

        return result;
    }

#if defined KZ_FEATURE_FULL_METADATA

    void addPropertyType(AbstractPropertyType propertyType)
    {
        kzAssert(propertyType);
        checkSealed();

        m_propertyTypes.push_back(propertyType);
    }

    void addMessageType(AbstractMessageType messageType)
    {
        kzAssert(messageType);
        checkSealed();

        m_messageTypes.push_back(messageType);
    }

    void addNestedMetaclass(const Metaclass* metaclass)
    {
        kzAssert(metaclass);
        checkSealed();

        m_nestedMetaclasses.push_back(metaclass);
    }

    void addMixin(const Metaclass* metaclass)
    {
        kzAssert(metaclass);
        kzAssert(!metaclass->getBase());
        checkSealed();

        m_mixinMetaclasses.push_back(metaclass);
    }

    /// Registers a \a method to the metaclass.
    /// For convenience use KZ_METACLASS_METHOD macro to declare the metamethods.
    /// \param method The address of the MetaMethod instance to be registered.
    void addMethod(const MetaMethod* method);

    typedef MetaclassContainer::const_iterator MetaclassIterator;

    MetaclassIterator beginNestedMetaclasses() const
    {
        return cbegin(m_nestedMetaclasses);
    }

    MetaclassIterator endNestedMetaclasses() const
    {
        return cend(m_nestedMetaclasses);
    }

    MetaclassIterator beginMixinMetaclasses() const
    {
        return cbegin(m_mixinMetaclasses);
    }

    MetaclassIterator endMixinMetaclasses() const
    {
        return cend(m_mixinMetaclasses);
    }

    typedef PropertyTypeContainer::const_iterator PropertyTypeIterator;

    PropertyTypeIterator beginPropertyTypes() const
    {
        return cbegin(m_propertyTypes);
    }

    PropertyTypeIterator endPropertyTypes() const
    {
        return cend(m_propertyTypes);
    }

    typedef MessageTypeContainer::const_iterator MessageTypeIterator;

    MessageTypeIterator beginMessageTypes() const
    {
        return cbegin(m_messageTypes);
    }

    MessageTypeIterator endMessageTypes() const
    {
        return cend(m_messageTypes);
    }

    /// Iterator for MetaMethod container.
    typedef MetaMethodContainer::const_iterator MetaMethodIterator;
    /// Creates a const_iterator pointing to the top of the metamethod container.
    MetaMethodIterator beginMethod() const;

    /// Creates a const_iterator pointing to the end of the metamethod container.
    MetaMethodIterator endMethod() const;

    /// Returns the metamethod registered in the metaclass with the given \a name.
    /// \param name The name of the metamethod.
    /// \return Pointer to the metamethod, \a nullptr if none found.
    const MetaMethod* findMethod(string_view name) const;
#endif

    FixedString getName() const
    {
        return m_name;
    }

    void setEditorInfo(PropertyTypeEditorInfoSharedPtr editorInfo)
    {
        (void)editorInfo;

        checkSealed();

#ifdef KZ_EDITOR_INFO_METADATA 
        if(m_editorInfo)
        {
            kzThrowException(logic_error("Setting multiple editor infos to a metaclass."));
        }
        swap(m_editorInfo, editorInfo);
#endif
    }

    PropertyTypeEditorInfoSharedPtr getEditorInfo() const
    {
#if defined KZ_EDITOR_INFO_METADATA
        return m_editorInfo;
#else
        return 0;
#endif
    }

protected:

    explicit Metaclass(const Metaclass* baseClass, FixedString name):
        m_baseClass(baseClass),
        m_name(name),
        m_abstract(false)
#if defined KZ_FEATURE_FULL_METADATA
        , m_sealed(false)
#endif
    {
    }

    ~Metaclass()
    {
    }

    void checkSealed() const;

    void setAbstract()
    {
        m_abstract = true;
    }

private:

    const Metaclass* m_baseClass;
    FixedString m_name;
    bool m_abstract;

#if defined KZ_FEATURE_FULL_METADATA
    bool m_sealed;    
    MetaclassContainer m_nestedMetaclasses;
    MetaclassContainer m_mixinMetaclasses;
    PropertyTypeContainer m_propertyTypes;
    MessageTypeContainer m_messageTypes;
    MetaMethodContainer m_metaMethods;
#ifdef KZ_EDITOR_INFO_METADATA
    PropertyTypeEditorInfoSharedPtr m_editorInfo;
#endif
#endif
};

template <typename TClass>
class MetaclassImpl : public Metaclass
{
public:

    explicit MetaclassImpl(const Metaclass* baseClass, FixedString name):
        Metaclass(baseClass, name)
    {
    }

    virtual bool isMetaclassOf(const MetaObject& object) const KZ_OVERRIDE
    {
        const TClass* castedObject = dynamic_cast<const TClass*>(&object);
        return castedObject != 0;
    }

    virtual shared_ptr<MetaObject> create(Domain* domain, string_view name) const KZ_OVERRIDE
    {
        return TClass::create(domain, name);
    }
};

class MetaclassAbstractBase : public Metaclass
{
protected:

    explicit MetaclassAbstractBase(const Metaclass* baseClass, FixedString name) :
        Metaclass(baseClass, name)
    {
        setAbstract();
    }

    virtual shared_ptr<MetaObject> create(Domain* /*domain*/, string_view /*name*/) const KZ_OVERRIDE
    {
        kzThrowException(logic_error("Tried to create an abstract type object '" + string(getName().c_str()) + "'"));
    }
};

template <typename TClass>
class MetaclassAbstractImpl : public MetaclassAbstractBase
{
public:

    explicit MetaclassAbstractImpl(const Metaclass* baseClass, FixedString name) :
        MetaclassAbstractBase(baseClass, name)
    {
    }

    virtual bool isMetaclassOf(const MetaObject& object) const KZ_OVERRIDE
    {
        const TClass* castedObject = dynamic_cast<const TClass*>(&object);
        return castedObject != 0;
    }    
};

class MetaclassStaticBase : public Metaclass
{
public:

    explicit MetaclassStaticBase(const Metaclass* baseClass, FixedString name) :
        Metaclass(baseClass, name)
    {
        setAbstract();
    }

    virtual bool isMetaclassOf(const MetaObject& /*object*/) const KZ_OVERRIDE
    {
        return false;
    }

    virtual shared_ptr<MetaObject> create(Domain* /*domain*/, string_view /*name*/) const KZ_OVERRIDE
    {
        kzThrowException(logic_error("Tried to create an abstract type object '" + string(getName().c_str()) + "'"));
    }
};

template <typename TClass>
class MetaclassStaticImpl : public MetaclassStaticBase
{
public:

    explicit MetaclassStaticImpl(const Metaclass* baseClass, FixedString name):
        MetaclassStaticBase(baseClass, name)
    {
    }
};

}

#define KZ_METACLASS_BEGIN(thisClass, baseClass, name)\
    virtual const ::kanzi::Metaclass* getDynamicMetaclass() const KZ_OVERRIDE\
    {\
        return getStaticMetaclass();\
    }\
    static const ::kanzi::Metaclass* getStaticMetaclass()\
    {\
        typedef thisClass ThisClass;\
        typedef baseClass BaseClass;\
        KZ_STATIC_ASSERT((::kanzi::is_base_of<BaseClass, ThisClass>::value), "Metaclass: incorrect base provided.");\
        static ::kanzi::MetaclassImpl<ThisClass> metaclass(BaseClass::getStaticMetaclass(), kzMakeFixedString(name));\
        if (!metaclass.isSealed())\
        {\
            /* Ensure that the base metaclass is initialized in case of metadata system restart.*/\
            BaseClass::getStaticMetaclass();

#define KZ_ABSTRACT_METACLASS_BEGIN(thisClass, baseClass, name)\
    virtual const ::kanzi::Metaclass* getDynamicMetaclass() const KZ_OVERRIDE\
    {\
        return getStaticMetaclass();\
    }\
    static const ::kanzi::Metaclass* getStaticMetaclass()\
    {\
        typedef thisClass ThisClass;\
        typedef baseClass BaseClass;\
        KZ_STATIC_ASSERT((::kanzi::is_base_of<BaseClass, ThisClass>::value), "Metaclass: incorrect base provided.");\
        static ::kanzi::MetaclassAbstractImpl<ThisClass> metaclass(BaseClass::getStaticMetaclass(), kzMakeFixedString(name));\
        if (!metaclass.isSealed())\
        {\
            /* Ensure that the base metaclass is initialized in case of metadata system restart.*/\
            BaseClass::getStaticMetaclass();

#define KZ_TEMPLATE_METACLASS_BEGIN(thisClass, baseClass)\
    virtual const ::kanzi::Metaclass* getDynamicMetaclass() const KZ_OVERRIDE\
    {\
        return getStaticMetaclass();\
    }\
    static const ::kanzi::Metaclass* getStaticMetaclass()\
    {\
        typedef thisClass ThisClass;\
        typedef baseClass BaseClass;\
        KZ_STATIC_ASSERT((::kanzi::is_base_of<BaseClass, ThisClass>::value), "Metaclass: incorrect base provided.");\
        static ::kanzi::MetaclassAbstractImpl<ThisClass> metaclass(BaseClass::getStaticMetaclass(), kzMakeFixedString(""));\
        if (!metaclass.isSealed())\
        {\
            /* Ensure that the base metaclass is initialized in case of metadata system restart.*/\
            BaseClass::getStaticMetaclass();

#define KZ_STATIC_METACLASS_BEGIN(thisClass, name)\
    static const ::kanzi::Metaclass* getStaticMetaclass()\
    {\
        typedef thisClass ThisClass;\
        static ::kanzi::MetaclassStaticImpl<ThisClass> metaclass(0, kzMakeFixedString(name));\
        if (!metaclass.isSealed())\
        {

#define KZ_STATIC_METACLASS_BASE_BEGIN(thisClass, baseClass, name)\
    static const ::kanzi::Metaclass* getStaticMetaclass()\
    {\
        typedef thisClass ThisClass;\
        typedef baseClass BaseClass;\
        static ::kanzi::MetaclassStaticImpl<ThisClass> metaclass(BaseClass::getStaticMetaclass(), kzMakeFixedString(name));\
        if (!metaclass.isSealed())\
        {\
            /* Ensure that the base metaclass is initialized in case of metadata system restart.*/\
            BaseClass::getStaticMetaclass();

#define KZ_MIXIN_METACLASS_BEGIN(thisClass, name) KZ_STATIC_METACLASS_BEGIN(thisClass, name)

#define KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(thisClass, baseClass, name)\
    static const ::kanzi::Metaclass* getStaticMetaclass()\
    {\
        typedef thisClass ThisClass;\
        typedef baseClass BaseClass;\
        static ::kanzi::MetaclassStaticImpl<ThisClass> metaclass(::kanzi::MessageArgumentsBaseMetaclassWrapper<BaseClass>::getStaticMetaclass(), kzMakeFixedString(name));\
        if (!metaclass.isSealed())\
        {\
            /* Ensure that the base metaclass is initialized in case of metadata system restart.*/\
            ::kanzi::MessageArgumentsBaseMetaclassWrapper<BaseClass>::getStaticMetaclass();

#define KZ_METACLASS_END()\
            metaclass.setEditorInfo(::kanzi::PropertyTypeEditorInfoSharedPtr(makeEditorInfo()));\
            metaclass.seal();\
        }\
        return &metaclass;\
    }

#if defined KZ_FEATURE_FULL_METADATA
#define KZ_METACLASS_MIXIN(mixinClass)\
        KZ_STATIC_ASSERT((::kanzi::is_base_of<mixinClass, ThisClass>::value), "Metaclass: incorrect base provided.");\
        metaclass.addMixin(mixinClass::getStaticMetaclass());
#else
#define KZ_METACLASS_MIXIN(mixinClass)\
        KZ_STATIC_ASSERT((::kanzi::is_base_of<mixinClass, ThisClass>::value), "Metaclass: incorrect base provided.");\
        mixinClass::getStaticMetaclass();
#endif

#if defined KZ_FEATURE_FULL_METADATA
#define KZ_METACLASS_PROPERTY_TYPE(propertyType)\
        metaclass.addPropertyType(propertyType);
#else
#define KZ_METACLASS_PROPERTY_TYPE(propertyType)
#endif

#define KZ_METACLASS_ATTACHED_PROPERTY_TYPE KZ_METACLASS_PROPERTY_TYPE

#if defined KZ_FEATURE_FULL_METADATA
#define KZ_METACLASS_MESSAGE_TYPE(messageType)\
        messageType.attachArgumentsMetaclass();\
        metaclass.addMessageType(messageType);\
        metaclass.addNestedMetaclass(messageType.getArgumentsMetaclass());
#else
#define KZ_METACLASS_MESSAGE_TYPE(messageType)\
        messageType.attachArgumentsMetaclass();\
        messageType.getArgumentsMetaclass();
#endif

#if defined KZ_FEATURE_FULL_METADATA
#define KZ_METACLASS_NESTED_METACLASS(argumentsType)\
        metaclass.addNestedMetaclass(argumentsType::getStaticMetaclass());
#else
#define KZ_METACLASS_NESTED_METACLASS(argumentsType)\
        argumentsType::getStaticMetaclass();
#endif

#if defined KZ_FEATURE_FULL_METADATA
#define KZ_METACLASS_METHOD(method) \
        metaclass.addMethod(&method);
#else
#define KZ_METACLASS_METHOD(method)
#endif

#endif
