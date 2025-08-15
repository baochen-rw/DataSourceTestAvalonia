// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_METAMETHOD_HPP
#define KZ_METAMETHOD_HPP

#include <kanzi/core/cpp/iterator.hpp>
#include <kanzi/core/cpp/type_traits.hpp>
#include <kanzi/core/cpp/variant.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/property/property_type.hpp>

namespace kanzi
{

/// Holds argument type and value information.
///
/// The MethodArgument holds the type and value of a metamethod argument or the return
/// value of the method. You can specify the value of the argument upon instantiation
/// and retrieve it with one of the get() template function members.
class KANZI_API MethodArgument
{
    typedef variant<monostate, bool, int, float, ColorRGBA, Vector2, Vector3, Vector4, SRTValue2D, SRTValue3D, Matrix3x3, Matrix4x4, string, ResourceID, ResourceSharedPtr, void*> ValueType;

    PropertyDataType getValueType();

    template <typename T>
    bool typeOf() const
    {
        return m_value.type() == typeid(T);
    }

    ValueType m_value;
    AbstractPropertyType m_type;

public:
    /// Constructor.
    explicit MethodArgument();

    /// Destructor.
    ~MethodArgument();

    /// Creates an argument with a property type.
    /// \param argumentType A property type defining the type of the argument.
    /// \param value The value of the argument.
    template <typename TDataType>
    explicit MethodArgument(const PropertyType<TDataType>& argumentType, typename PropertyType<TDataType>::DataType value) :
        m_value(kanzi::move(value)),
        m_type(AbstractPropertyType(argumentType))
    {
    }

    /// Creates an argument using an AbstractPropertyType. The type of the \a value
    /// must match the type defined by the \a argumentType.
    /// \param argumentType An abstract property type defining the type of the argument.
    /// \param value The value of the argument.
    template <typename TDataType>
    explicit MethodArgument(AbstractPropertyType argumentType, TDataType value) :
        m_value(kanzi::move(value)),
        m_type(argumentType)
    {
        kzAssert(argumentType.getDataType() == getValueType());
    }

    /// Copy-constructor.
    MethodArgument(const MethodArgument& other) :
        m_value(other.m_value),
        m_type(other.m_type)
    {
    }

    /// Assignment operator.
    MethodArgument& operator=(const MethodArgument& other)
    {
        m_value = kanzi::move(other.m_value);
        m_type = other.m_type;
        return *this;
    }

    /// Returns the value of the argument. The \a argumentType must match the type
    /// of the MethodArgument instance.
    /// \param argumentType Type of the argument.
    /// \return The value of the argument, or nullopt, if the argument is not valid
    /// or the \a argumentType and the stored type do not match.
    template <typename TDataType>
    optional<TDataType> get(const PropertyType<TDataType>& argumentType) const
    {
        if (!isValid())
        {
            return nullopt;
        }
        if (argumentType == m_type)
        {
            return kanzi::get<TDataType>(m_value);
        }
        return nullopt;
    }

    /// Overloaded version of get() using AbstractPropertyType to retrieve
    /// the value.
    /// \param argumentType AbstractPropertyType defining the type of the argument.
    /// \param value The address to store the argument value.
    /// \return \e true if the argument can be retrieved, \e false if the argument
    /// is invalid, the \a argumentType differs from the type stored, or the
    /// type of the \a value differs from the type of the argument.
    template <typename TDataType>
    bool get(AbstractPropertyType argumentType, TDataType& value) const
    {
        if (isValid() && (argumentType == m_type) && typeOf<TDataType>())
        {
            value = kanzi::get<TDataType>(m_value);
            return true;
        }
        return false;
    }

    /// Returns the type of the argument.
    AbstractPropertyType getType() const
    {
        return m_type;
    }

    /// Returns \e true if the argument stores a valid value, \e false otherwise.
    bool isValid() const
    {
        return m_value.which() != 0 && m_type;
    }
};

/// Holds arguments applied on metamethod invocation.
///
/// MethodArguments includes argument values applied on metamethods during invocation.
/// You can add values using setArgument() and setAbstractArgument(), and retrieve them
/// with getArgument() and getAbstractArgument() methods. To get the argument values of
/// a given type use the same argument type which you used to set them. To verify the
/// presence of an argument type, use isSet().
class KANZI_API MethodArguments
{
public:
    explicit MethodArguments();
    ~MethodArguments();

    /// Returns the value of an argument of a given type. Use it when the
    /// property type defining the metamethod argument is known at build time.
    /// \param argumentType The type of the argument.
    /// \return The argument value set, or the default value of the data type.
    /// \note The function does not tell whether the argument type is set.
    /// Use isSet() or getAbstractArgument() functions to find out whether the
    /// argument is set.
    template <typename TDataType>
    TDataType getArgument(const PropertyType<TDataType>& argumentType) const
    {
        const MethodArgument* argument = findArgument(argumentType);
        if (argument)
        {
            return argument->get(argumentType).value();
        }
        return TDataType();
    }

    /// Adds or updates the value for a given argument type. Use it when the
    /// property type defining the metamethod argument is known at build time.
    /// \param argumentType The abstract type of the argument to be set.
    /// \param value The value of the argument type.
    template <typename TDataType>
    void setArgument(const PropertyType<TDataType>& argumentType, typename PropertyType<TDataType>::DataType value)
    {
        MethodArgument* argument = acquireArgument(argumentType);
        *argument = MethodArgument(argumentType, kanzi::move(value));
    }

    /// Retrieves an argument with the given \a argumentType into the \a value address.
    /// Use it when the property type defining the metamethod argument is not known at
    /// build time.
    /// \param argumentType The abstract type of the argument to be set.
    /// \param value The value of the argument type.
    /// \return \e true if the argument is set and the data type of the \a value matches
    /// the argument type.
    template <typename TDataType>
    bool getAbstractArgument(AbstractPropertyType argumentType, TDataType& value)
    {
        const MethodArgument* argument = findArgument(argumentType);
        if (argument)
        {
            return argument->get(argumentType, value);
        }
        return false;
    }

    /// Adds or updates the value for a given argument type. Use it when the
    /// property type defining the metamethod argument is not known at build time.
    /// \param argumentType The abstract type of the argument to be set.
    /// \param value The value of the argument type.
    template <typename TDataType>
    void setAbstractArgument(AbstractPropertyType argumentType, TDataType value)
    {
        MethodArgument* argument = acquireArgument(argumentType);
        *argument = MethodArgument(argumentType, kanzi::move(value));
    }

    /// Checks whether a given argument type is set.
    /// \param argumentType The type of the argument whose presence is checked.
    /// \return \e true if the argument type is defined, \e false otherwise.
    bool isSet(AbstractPropertyType argumentType) const;

    /// Returns the number of arguments set, or 0 if none set.
    size_t getCount() const;

private:
    MethodArguments(const MethodArguments&) KZ_DELETED_FUNCTION;
    MethodArguments& operator=(const MethodArguments&) KZ_DELETED_FUNCTION;

    MethodArgument* findArgument(AbstractPropertyType argumentType);
    const MethodArgument* findArgument(AbstractPropertyType argumentType) const;
    MethodArgument* acquireArgument(AbstractPropertyType argumentType);

    kanzi::vector<MethodArgument> m_arguments;
};

class MetaObject;

/// MetaMethod provides method invocation mechanism for Kanzi classes.
///
/// You can expose class methods to scripting and in general to its metadata
/// subsystem using the MetaMethod class. To do so you must register the methods
/// to the metadata of the class using the KZ_METACLASS_METHOD macro.
/// \snippet kz_test_metamethod.cpp Declare methods
///
/// You can invoke a metamethod on an object using one of the invoke() static
/// methods. Use the string representation of the method you want to invoke.
/// \snippet kz_test_metamethod.cpp Invoke void method
///
/// The arguments are passed to the invocation using the MethodArguments class,
/// where you must specify the argument types with property types which are
/// the same as the targeted method arguments.
/// \snippet kz_test_metamethod.cpp Invoke with one argument
///
/// For an invocation to succeed, you must set all argument types in the
/// MethodArguments which are present in the signature of the invoked method.
/// Omitting any argument required by the signature results in failure.
/// \snippet kz_test_metamethod.cpp Invoke failure
///
/// When you need to make overloaded methods available to the metadata of
/// the class, to invoke the correct overload, you must create a dedicated
/// MetaMethod instance with a different name.
/// \snippet kz_test_metamethod.cpp Invoke overloads
///
/// invoke() stores the return values of the invoked methods in a MethodArgument
/// object. The function returns \e nullopt if the invocation cannot find
/// the method in the metadata of the object, or in either of its ascendants
/// metadata.
/// \snippet kz_test_metamethod.cpp Invalid method invoked
///
/// A MethodArgument instance holding the result is returned if the invocation
/// found the method and was able to apply the specified arguments. When the
/// method is of void type, the returned result object contains an invalid
/// MethodArgument instance.
/// \snippet kz_test_metamethod.cpp Handle method result
///
/// In cases when the argument types are unknown at build time and you need a
/// dynamic argument invocation, use the MetaMethod name to query the MetaMethod
/// from the metaclass of the object, set the arguments based on the method
/// arguments and apply those on the metamethod.
/// \snippet kz_test_metamethod.cpp Apply
class KANZI_API MetaMethod
{
public:
    /// Constructor
    explicit MetaMethod();

    // no arguments
    /// Template constructor for a void method with no argument specialization.
    /// \param name The name of the metamethod.
    /// \param method The address of the method to be handled.
    template <class TClass>
    explicit MetaMethod(FixedString name, void (TClass::*method)());

    /// Template constructor for a method with return type and no argument specialization.
    /// \param name The name of the metamethod.
    /// \param ret The property type defining the return type of the method.
    /// \param method The address of the method to be handled.
    template <class TClass, typename TRet, typename TRetProp>
    explicit MetaMethod(FixedString name, const PropertyType<TRetProp>& ret, TRet (TClass::*method)());

    // one argument
    /// Template constructor for a void method with one argument specialization.
    /// \param name The name of the metamethod.
    /// \param method The address of the method to be handled.
    /// \param property1 The property type defining the type of the argument.
    template <class TClass, typename TArg1, typename TArg1Prop>
    explicit MetaMethod(FixedString name, void (TClass::*method)(TArg1), const PropertyType<TArg1Prop>& property1);

    /// Template constructor for a method with return type and one argument specialization.
    /// \param name The name of the metamethod.
    /// \param ret The property type defining the return type of the method.
    /// \param method The address of the method to be handled.
    /// \param property1 The property type defining the type of the argument.
    template <class TClass, typename TRet, typename TRetProp, typename TArg1, typename TArg1Prop>
    explicit MetaMethod(FixedString name, const PropertyType<TRetProp>& ret, TRet (TClass::*method)(TArg1),
                        const PropertyType<TArg1Prop>& property1);

    // two arguments
    /// Template constructor for a void method with two arguments specialization.
    /// \param name The name of the metamethod.
    /// \param method The address of the method to be handled.
    /// \param property1 The property type defining the type of the first argument.
    /// \param property2 The property type defining the type of the second argument.
    /// \throws invalid_argument if the property types defining the arguments are identical.
    template <class TClass, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop>
    explicit MetaMethod(FixedString name, void (TClass::*method)(TArg1, TArg2),
                        const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2);

    /// Template constructor for a method with return type and two arguments specialization.
    /// \param name The name of the metamethod.
    /// \param ret The property type defining the return type of the method.
    /// \param method The address of the method to be handled.
    /// \param property1 The property type defining the type of the first argument.
    /// \param property2 The property type defining the type of the second argument.
    /// \throws invalid_argument if the property types defining the arguments are identical.
    template <class TClass, typename TRet, typename TRetProp, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop>
    explicit MetaMethod(FixedString name, const PropertyType<TRetProp>& ret, TRet (TClass::*method)(TArg1, TArg2),
                        const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2);

    // three arguments
    /// Template constructor for a void method with three arguments specialization.
    /// \param name The name of the metamethod.
    /// \param method The address of the method to be handled.
    /// \param property1 The property type defining the type of the first argument.
    /// \param property2 The property type defining the type of the second argument.
    /// \param property3 The property type defining the type of the third argument.
    /// \throws invalid_argument if at least two property types defining the arguments are identical.
    template <class TClass, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop>
    explicit MetaMethod(FixedString name, void (TClass::*method)(TArg1, TArg2, TArg3),
                        const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                        const PropertyType<TArg3Prop>& property3);

    /// Template constructor for a method with return type and three arguments specialization.
    /// \param name The name of the metamethod.
    /// \param ret The property type defining the return type of the method.
    /// \param method The address of the method to be handled.
    /// \param property1 The property type defining the type of the first argument.
    /// \param property2 The property type defining the type of the second argument.
    /// \param property3 The property type defining the type of the third argument.
    /// \throws invalid_argument if at least two property types defining the arguments are identical.
    template <class TClass, typename TRet, typename TRetProp, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop>
    explicit MetaMethod(FixedString name, const PropertyType<TRetProp>& ret, TRet (TClass::*method)(TArg1, TArg2, TArg3),
                        const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                        const PropertyType<TArg3Prop>& property3);

    // four arguments
    /// Template constructor for a void method with four arguments specialization.
    /// \param name The name of the metamethod.
    /// \param method The address of the method to be handled.
    /// \param property1 The property type defining the type of the first argument.
    /// \param property2 The property type defining the type of the second argument.
    /// \param property3 The property type defining the type of the third argument.
    /// \param property4 The property type defining the type of the fourth argument.
    /// \throws invalid_argument if at least two property types defining the arguments are identical.
    template <class TClass, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop, typename TArg4, typename TArg4Prop>
    explicit MetaMethod(FixedString name, void (TClass::*method)(TArg1, TArg2, TArg3, TArg4),
                        const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                        const PropertyType<TArg3Prop>& property3, const PropertyType<TArg4Prop>& property4);

    /// Template constructor for a method with return type and four arguments specialization.
    /// \param name The name of the metamethod.
    /// \param ret The property type defining the return type of the method.
    /// \param method The address of the method to be handled.
    /// \param property1 The property type defining the type of the first argument.
    /// \param property2 The property type defining the type of the second argument.
    /// \param property3 The property type defining the type of the third argument.
    /// \param property4 The property type defining the type of the fourth argument.
    /// \throws invalid_argument if at least two property types defining the arguments are identical.
    template <class TClass, typename TRet, typename TRetProp, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop, typename TArg4, typename TArg4Prop>
    explicit MetaMethod(FixedString name, const PropertyType<TRetProp>& ret, TRet (TClass::*method)(TArg1, TArg2, TArg3, TArg4),
                        const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                        const PropertyType<TArg3Prop>& property3, const PropertyType<TArg4Prop>& property4);

    // five arguments
    /// Template constructor for a void method with five arguments specialization.
    /// \param name The name of the metamethod.
    /// \param method The address of the method to be handled.
    /// \param property1 The property type defining the type of the first argument.
    /// \param property2 The property type defining the type of the second argument.
    /// \param property3 The property type defining the type of the third argument.
    /// \param property4 The property type defining the type of the fourth argument.
    /// \param property5 The property type defining the type of the fifth argument.
    /// \throws invalid_argument if at least two property types defining the arguments are identical.
    template <class TClass, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop, typename TArg4, typename TArg4Prop, typename TArg5, typename TArg5Prop>
    explicit MetaMethod(FixedString name, void (TClass::*method)(TArg1, TArg2, TArg3, TArg4, TArg5),
                        const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                        const PropertyType<TArg3Prop>& property3, const PropertyType<TArg4Prop>& property4,
                        const PropertyType<TArg5Prop>& property5);

    /// Template constructor for a method with return type and five arguments specialization.
    /// \param name The name of the metamethod.
    /// \param ret The property type defining the return type of the method.
    /// \param method The address of the method to be handled.
    /// \param property1 The property type defining the type of the first argument.
    /// \param property2 The property type defining the type of the second argument.
    /// \param property3 The property type defining the type of the third argument.
    /// \param property4 The property type defining the type of the fourth argument.
    /// \param property5 The property type defining the type of the fifth argument.
    /// \throws invalid_argument if at least two property types defining the arguments are identical.
    template <class TClass, typename TRet, typename TRetProp, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop, typename TArg4, typename TArg4Prop, typename TArg5, typename TArg5Prop>
    explicit MetaMethod(FixedString name, const PropertyType<TRetProp>& ret, TRet (TClass::*method)(TArg1, TArg2, TArg3, TArg4, TArg5),
                        const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                        const PropertyType<TArg3Prop>& property3, const PropertyType<TArg4Prop>& property4,
                        const PropertyType<TArg5Prop>& property5);

    // six arguments
    /// Template constructor for a void method with six arguments specialization.
    /// \param name The name of the metamethod.
    /// \param method The address of the method to be handled.
    /// \param property1 The property type defining the type of the first argument.
    /// \param property2 The property type defining the type of the second argument.
    /// \param property3 The property type defining the type of the third argument.
    /// \param property4 The property type defining the type of the fourth argument.
    /// \param property5 The property type defining the type of the fifth argument.
    /// \param property6 The property type defining the type of the sixth argument.
    /// \throws invalid_argument if at least two property types defining the arguments are identical.
    template <class TClass, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop, typename TArg4, typename TArg4Prop, typename TArg5, typename TArg5Prop, typename TArg6, typename TArg6Prop>
    explicit MetaMethod(FixedString name, void (TClass::*method)(TArg1, TArg2, TArg3, TArg4, TArg5, TArg6),
                        const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                        const PropertyType<TArg3Prop>& property3, const PropertyType<TArg4Prop>& property4,
                        const PropertyType<TArg5Prop>& property5, const PropertyType<TArg6Prop>& property6);

    /// Template constructor for a method with return type and six arguments specialization.
    /// \param name The name of the metamethod.
    /// \param ret The property type defining the return type of the method.
    /// \param method The address of the method to be handled.
    /// \param property1 The property type defining the type of the first argument.
    /// \param property2 The property type defining the type of the second argument.
    /// \param property3 The property type defining the type of the third argument.
    /// \param property4 The property type defining the type of the fourth argument.
    /// \param property5 The property type defining the type of the fifth argument.
    /// \param property6 The property type defining the type of the sixth argument.
    /// \throws invalid_argument if at least two property types defining the arguments are identical.
    template <class TClass, typename TRet, typename TRetProp, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop, typename TArg4, typename TArg4Prop, typename TArg5, typename TArg5Prop, typename TArg6, typename TArg6Prop>
    explicit MetaMethod(FixedString name, const PropertyType<TRetProp>& ret, TRet (TClass::*method)(TArg1, TArg2, TArg3, TArg4, TArg5, TArg6),
                        const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                        const PropertyType<TArg3Prop>& property3, const PropertyType<TArg4Prop>& property4,
                        const PropertyType<TArg5Prop>& property5, const PropertyType<TArg6Prop>& property6);

    /// Applies the \a arguments on the method of an \a instance of the class holding
    /// the member function. The return value of the method is stored in the returned
    /// MethodArgument object. You can store the arguments in arbitrary order, however
    /// you must have all the arguments set required by the signature of the method,
    /// otherwise the invocation fails.
    /// \param instance The instance of the class on which you want to invoke the method.
    /// \param arguments The argument values with which you want to invoke the method.
    /// \return The return value of the method. If the method is void, an invalid object.
    /// If the MetaMethod is invalid or arguments do not match, \e nullopt.
    optional<MethodArgument> apply(MetaObject& instance, const MethodArguments& arguments) const;

    /// Looks for the \a metaMethod in the metaclass of the \a instance
    /// with the given \a arguments. The lookup bubbles up in the ascendants metaclass
    /// hierarchy as well as in the mixin metaclasses hierarchy.
    /// \param metaMethod The string identifier of the method as registered to the metaclass.
    /// \param instance Instance derived from the MetaObject class.
    /// \param arguments The set of values matching the method parameter types.
    /// \return The pointer to the MetaMethod registered in the metadata of the class handling
    /// the method. If no method is found, \e nullptr.
    static const MetaMethod* find(string_view metaMethod, const MetaObject& instance, const MethodArguments& arguments);

    /// Combines the functionality of find() and apply() into a single function call.
    /// \param object The object from which to invoke the \a method.
    /// \param metaMethod The name of the MetaMethod you want to invoke.
    /// \param arguments The argument values with which you want to invoke the method.
    /// \return A MetaArgument object containing the result values. If the invocation failed,
    /// \e nullopt.
    static optional<MethodArgument> invoke(MetaObject& object, string_view metaMethod, const MethodArguments& arguments);

    /// Overload of invoke() specialized to invoke parameterless methods.
    /// \note This is similar to calling \e {invoke(object, metaMethod, MethodArguments())} method.
    /// \param object The object the \e metaMethod to be invoked from.
    /// \param metaMethod The name of the MetaMethod to be invoked.
    /// \return A MetaArgument object containing the result values. If the invocation failed,
    /// \e nullptr.
    static optional<MethodArgument> invoke(MetaObject& object, string_view metaMethod);

    /// Gets the name of the method.
    /// \return The name of the MetaMethod. If the MetaMethod is invalid, \e nullptr.
    const char* getName() const;

    /// Gets the number of method arguments.
    /// \return The number of arguments. When called on an invalid MetaMethod, -1.
    int getArgumentCount() const;

    /// Gets the return-type of the method.
    /// \return The abstract property type defining the return type. For void
    /// function members this value is invalid.
    AbstractPropertyType getReturnType() const;

    /// Gets the argument type from a given index.
    /// \param index A 0-based index pointing to the argument type from the signature
    /// of the handled method.
    /// \return The abstract property type defining the argument. If the \a index does
    /// not point to a valid argument from the signature of the method, the function
    /// returns an invalid type.
    AbstractPropertyType getArgumentType(size_t index) const;

    /// Checks whether the metamethod is valid. A MetaMethod is valid when it holds a
    /// valid method address with the describing argument types.
    bool isValid() const;

private:
    MetaMethod(const MetaMethod&) KZ_DELETED_FUNCTION;
    MetaMethod& operator=(const MetaMethod&) KZ_DELETED_FUNCTION;

    void validateArguments();
    bool doArgumentsMatch(const MethodArguments& arguments) const;

    typedef function<optional<MethodArgument>(MetaObject&, const MethodArguments&)> InvokerFunction;

    struct Descriptor
    {
        explicit Descriptor() :
            name()
        {
        }

        InvokerFunction invoker;
        AbstractPropertyType returnType;
        vector<AbstractPropertyType> argumentTypes;
        const char* name;
    };

    Descriptor m_descriptor;
};

} // namespace kanzi

#include "metamethod.hpp.inl"

#endif // KZ_METAMETHOD_HPP
