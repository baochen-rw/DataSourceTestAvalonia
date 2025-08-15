// Copyright 2008-2021 by Rightware. All rights reserved.

namespace kanzi
{

namespace detail
{

// The following templates are declaring the specialization of invocable functors holding the
// methods handled by the MetaMethod instances. The specializations are made to support up to
// six arguments, with and without return value. The functor operators return the encapsulated
// method's return value in an optional<>, indicating in this way whether the MetaObject instance
// is castable to the handled class. The functors embracing methods simply return a bool value
// to indicate the same.
template <typename TClass, typename TRet,
          typename TArg1 = void, typename TArg2 = void, typename TArg3 = void,
          typename TArg4 = void, typename TArg5 = void, typename TArg6 = void,
          typename Enable = void>
struct Invocable;

template <typename TClass, typename TRet>
struct Invocable<TClass, TRet, void, void, void, void, void, void,
                 typename enable_if<is_void<TRet>::value>::type>
{
    typedef void (TClass::*MethodType)();
    MethodType m_method;

    explicit Invocable(MethodType method) :
        m_method(method)
    {
    }
    bool operator()(MetaObject& object)
    {
        TClass* instance = dynamic_cast<TClass*>(&object);
        if (instance)
        {
            (instance->*m_method)();
        }
        return (instance != 0);
    }
};
template <typename TClass, typename TRet>
struct Invocable<TClass, TRet, void, void, void, void, void, void,
                 typename enable_if<!is_void<TRet>::value>::type>
{
    typedef TRet (TClass::*MethodType)();
    MethodType m_method;

    explicit Invocable(MethodType method) :
        m_method(method)
    {
    }
    optional<TRet> operator()(MetaObject& object)
    {
        TClass* instance = dynamic_cast<TClass*>(&object);
        if (instance)
        {
            return (instance->*m_method)();
        }
        return nullopt;
    }
};

template <typename TClass, typename TRet,
          typename TArg1>
struct Invocable<TClass, TRet, TArg1, void, void, void, void, void,
                 typename enable_if<is_void<TRet>::value>::type>
{
    typedef void (TClass::*MethodType)(TArg1);
    MethodType m_method;

    explicit Invocable(MethodType method) :
        m_method(method)
    {
    }
    bool operator()(MetaObject& object, TArg1 a1)
    {
        TClass* instance = dynamic_cast<TClass*>(&object);
        if (instance)
        {
            (instance->*m_method)(a1);
        }
        return (instance != 0);
    }
};
template <typename TClass, typename TRet,
          typename TArg1>
struct Invocable<TClass, TRet, TArg1, void, void, void, void, void,
                 typename enable_if<!is_void<TRet>::value>::type>
{
    typedef TRet (TClass::*MethodType)(TArg1);
    MethodType m_method;

    explicit Invocable(MethodType method) :
        m_method(method)
    {
    }
    optional<TRet> operator()(MetaObject& object, TArg1 a1)
    {
        TClass* instance = dynamic_cast<TClass*>(&object);
        if (instance)
        {
            return (instance->*m_method)(a1);
        }
        return nullopt;
    }
};

template <typename TClass, typename TRet,
          typename TArg1, typename TArg2>
struct Invocable<TClass, TRet, TArg1, TArg2, void, void, void, void,
                 typename enable_if<is_void<TRet>::value>::type>
{
    typedef void (TClass::*MethodType)(TArg1, TArg2);
    MethodType m_method;

    explicit Invocable(MethodType method) :
        m_method(method)
    {
    }
    bool operator()(MetaObject& object, TArg1 a1, TArg2 a2)
    {
        TClass* instance = dynamic_cast<TClass*>(&object);
        if (instance)
        {
            (instance->*m_method)(a1, a2);
        }
        return (instance != 0);
    }
};
template <typename TClass, typename TRet,
          typename TArg1, typename TArg2>
struct Invocable<TClass, TRet, TArg1, TArg2, void, void, void, void,
                 typename enable_if<!is_void<TRet>::value>::type>
{
    typedef TRet (TClass::*MethodType)(TArg1, TArg2);
    MethodType m_method;

    explicit Invocable(MethodType method) :
        m_method(method)
    {
    }
    optional<TRet> operator()(MetaObject& object, TArg1 a1, TArg2 a2)
    {
        TClass* instance = dynamic_cast<TClass*>(&object);
        if (instance)
        {
            return (instance->*m_method)(a1, a2);
        }
        return nullopt;
    }
};

template <typename TClass, typename TRet,
          typename TArg1, typename TArg2,
          typename TArg3>
struct Invocable<TClass, TRet, TArg1, TArg2, TArg3, void, void, void,
                 typename enable_if<is_void<TRet>::value>::type>
{
    typedef void (TClass::*MethodType)(TArg1, TArg2, TArg3);
    MethodType m_method;

    explicit Invocable(MethodType method) :
        m_method(method)
    {
    }
    bool operator()(MetaObject& object, TArg1 a1, TArg2 a2, TArg3 a3)
    {
        TClass* instance = dynamic_cast<TClass*>(&object);
        if (instance)
        {
            (instance->*m_method)(a1, a2, a3);
        }
        return (instance != 0);
    }
};
template <typename TClass, typename TRet,
          typename TArg1, typename TArg2,
          typename TArg3>
struct Invocable<TClass, TRet, TArg1, TArg2, TArg3, void, void, void,
                 typename enable_if<!is_void<TRet>::value>::type>
{
    typedef TRet (TClass::*MethodType)(TArg1, TArg2, TArg3);
    MethodType m_method;

    explicit Invocable(MethodType method) :
        m_method(method)
    {
    }
    optional<TRet> operator()(MetaObject& object, TArg1 a1, TArg2 a2, TArg3 a3)
    {
        TClass* instance = dynamic_cast<TClass*>(&object);
        if (instance)
        {
            return (instance->*m_method)(a1, a2, a3);
        }
        return nullopt;
    }
};

template <typename TClass, typename TRet,
          typename TArg1, typename TArg2,
          typename TArg3, typename TArg4>
struct Invocable<TClass, TRet, TArg1, TArg2, TArg3, TArg4, void, void,
                 typename enable_if<is_void<TRet>::value>::type>
{
    typedef void (TClass::*MethodType)(TArg1, TArg2, TArg3, TArg4);
    MethodType m_method;

    explicit Invocable(MethodType method) :
        m_method(method)
    {
    }
    bool operator()(MetaObject& object, TArg1 a1, TArg2 a2, TArg3 a3, TArg4 a4)
    {
        TClass* instance = dynamic_cast<TClass*>(&object);
        if (instance)
        {
            (instance->*m_method)(a1, a2, a3, a4);
        }
        return (instance != 0);
    }
};
template <typename TClass, typename TRet,
          typename TArg1, typename TArg2,
          typename TArg3, typename TArg4>
struct Invocable<TClass, TRet, TArg1, TArg2, TArg3, TArg4, void, void,
                 typename enable_if<!is_void<TRet>::value>::type>
{
    typedef TRet (TClass::*MethodType)(TArg1, TArg2, TArg3, TArg4);
    MethodType m_method;

    explicit Invocable(MethodType method) :
        m_method(method)
    {
    }
    optional<TRet> operator()(MetaObject& object, TArg1 a1, TArg2 a2, TArg3 a3, TArg4 a4)
    {
        TClass* instance = dynamic_cast<TClass*>(&object);
        if (instance)
        {
            return (instance->*m_method)(a1, a2, a3, a4);
        }
        return nullopt;
    }
};

template <typename TClass, typename TRet,
          typename TArg1, typename TArg2,
          typename TArg3, typename TArg4,
          typename TArg5>
struct Invocable<TClass, TRet, TArg1, TArg2, TArg3, TArg4, TArg5, void,
                 typename enable_if<is_void<TRet>::value>::type>
{
    typedef void (TClass::*MethodType)(TArg1, TArg2, TArg3, TArg4, TArg5);
    MethodType m_method;

    explicit Invocable(MethodType method) :
        m_method(method)
    {
    }
    bool operator()(MetaObject& object, TArg1 a1, TArg2 a2, TArg3 a3, TArg4 a4, TArg5 a5)
    {
        TClass* instance = dynamic_cast<TClass*>(&object);
        if (instance)
        {
            (instance->*m_method)(a1, a2, a3, a4, a5);
        }
        return (instance != 0);
    }
};
template <typename TClass, typename TRet,
          typename TArg1, typename TArg2,
          typename TArg3, typename TArg4,
          typename TArg5>
struct Invocable<TClass, TRet, TArg1, TArg2, TArg3, TArg4, TArg5, void,
                 typename enable_if<!is_void<TRet>::value>::type>
{
    typedef TRet (TClass::*MethodType)(TArg1, TArg2, TArg3, TArg4, TArg5);
    MethodType m_method;

    explicit Invocable(MethodType method) :
        m_method(method)
    {
    }
    optional<TRet> operator()(MetaObject& object, TArg1 a1, TArg2 a2, TArg3 a3, TArg4 a4, TArg5 a5)
    {
        TClass* instance = dynamic_cast<TClass*>(&object);
        if (instance)
        {
            return (instance->*m_method)(a1, a2, a3, a4, a5);
        }
        return nullopt;
    }
};

template <typename TClass, typename TRet,
          typename TArg1, typename TArg2,
          typename TArg3, typename TArg4,
          typename TArg5, typename TArg6>
struct Invocable<TClass, TRet, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6,
                 typename enable_if<is_void<TRet>::value>::type>
{
    typedef void (TClass::*MethodType)(TArg1, TArg2, TArg3, TArg4, TArg5, TArg6);
    MethodType m_method;

    explicit Invocable(MethodType method) :
        m_method(method)
    {
    }
    bool operator()(MetaObject& object, TArg1 a1, TArg2 a2, TArg3 a3, TArg4 a4, TArg5 a5, TArg6 a6)
    {
        TClass* instance = dynamic_cast<TClass*>(&object);
        if (instance)
        {
            (instance->*m_method)(a1, a2, a3, a4, a5, a6);
        }
        return (instance != 0);
    }
};
template <typename TClass, typename TRet,
          typename TArg1, typename TArg2,
          typename TArg3, typename TArg4,
          typename TArg5, typename TArg6>
struct Invocable<TClass, TRet, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6,
                 typename enable_if<!is_void<TRet>::value>::type>
{
    typedef TRet (TClass::*MethodType)(TArg1, TArg2, TArg3, TArg4, TArg5, TArg6);
    MethodType m_method;

    explicit Invocable(MethodType method) :
        m_method(method)
    {
    }
    optional<TRet> operator()(MetaObject& object, TArg1 a1, TArg2 a2, TArg3 a3, TArg4 a4, TArg5 a5, TArg6 a6)
    {
        TClass* instance = dynamic_cast<TClass*>(&object);
        if (instance)
        {
            return (instance->*m_method)(a1, a2, a3, a4, a5, a6);
        }
        return nullopt;
    }
};

// The following templates declare the specialization of the invoker functors for up to six arguments,
// with or without return type.
template <typename TInvocable, typename TRet,
          typename TArg1 = void, typename TArg2 = void, typename TArg3 = void,
          typename TArg4 = void, typename TArg5 = void, typename TArg6 = void,
          typename Enable = void>
struct Invoker;

// no arguments
template <typename TInvocable, typename TRet>
struct Invoker<TInvocable, TRet, void, void, void, void, void, void,
               typename enable_if<!is_void<TRet>::value>::type>
{
    typedef PropertyType<TRet> RetType;
    TInvocable m_invocable;
    const RetType& m_returnType;

    explicit Invoker(const RetType& ret, TInvocable invocable) :
        m_invocable(kanzi::move(invocable)),
        m_returnType(ret)
    {
    }

    optional<MethodArgument> operator()(MetaObject& object, const MethodArguments&)
    {
        optional<TRet> ret = m_invocable(object);
        if (ret)
        {
            return MethodArgument(m_returnType, ret.value());
        }
        return nullopt;
    }
};

template <typename TInvocable, typename TRet>
struct Invoker<TInvocable, TRet, void, void, void, void, void, void,
               typename enable_if<is_void<TRet>::value>::type>
{
    TInvocable m_invocable;

    explicit Invoker(TInvocable invocable) :
        m_invocable(kanzi::move(invocable))
    {
    }

    optional<MethodArgument> operator()(MetaObject& object, const MethodArguments&)
    {
        if (m_invocable(object))
        {
            return MethodArgument();
        }
        return nullopt;
    }
};

// one argument specialization
template <typename TInvocable, typename TRet, typename TArg1>
struct Invoker<TInvocable, TRet, TArg1, void, void, void, void, void,
               typename enable_if<!is_void<TRet>::value>::type>
{
    typedef PropertyType<TRet> RetType;
    typedef PropertyType<TArg1> Arg1Type;

    TInvocable m_invocable;
    const Arg1Type& m_prop1;
    const RetType& m_returnType;

    explicit Invoker(const RetType& ret, TInvocable invocable, const Arg1Type& prop1) :
        m_invocable(kanzi::move(invocable)),
        m_prop1(prop1),
        m_returnType(ret)
    {
    }

    optional<MethodArgument> operator()(MetaObject& object, const MethodArguments& arguments)
    {
        optional<TRet> ret = m_invocable(object, arguments.getArgument(m_prop1));
        if (ret)
        {
            return MethodArgument(m_returnType, ret.value());
        }
        return nullopt;
    }
};

template <typename TInvocable, typename TRet, typename TArg1>
struct Invoker<TInvocable, TRet, TArg1, void, void, void, void, void,
               typename enable_if<is_void<TRet>::value>::type>
{
    typedef PropertyType<TArg1> Arg1Type;

    TInvocable m_invocable;
    const Arg1Type& m_prop1;

    explicit Invoker(TInvocable invocable, const Arg1Type& prop1) :
        m_invocable(kanzi::move(invocable)),
        m_prop1(prop1)
    {
    }

    optional<MethodArgument> operator()(MetaObject& object, const MethodArguments& arguments)
    {
        if (m_invocable(object, arguments.getArgument(m_prop1)))
        {
            return MethodArgument();
        }
        return nullopt;
    }
};

// two argument specialization
template <typename TInvocable, typename TRet, typename TArg1, typename TArg2>
struct Invoker<TInvocable, TRet, TArg1, TArg2, void, void, void, void,
               typename enable_if<!is_void<TRet>::value>::type>
{
    typedef PropertyType<TArg1> Arg1Type;
    typedef PropertyType<TArg2> Arg2Type;
    typedef PropertyType<TRet> RetType;

    TInvocable m_invocable;
    const Arg1Type& m_prop1;
    const Arg2Type& m_prop2;
    const RetType& m_returnType;

    explicit Invoker(const RetType& ret, TInvocable invocable, const Arg1Type& prop1, const Arg2Type& prop2) :
        m_invocable(kanzi::move(invocable)),
        m_prop1(prop1),
        m_prop2(prop2),
        m_returnType(ret)
    {
    }

    optional<MethodArgument> operator()(MetaObject& object, const MethodArguments& arguments)
    {
        optional<TRet> ret = m_invocable(object,
                                         arguments.getArgument(m_prop1), arguments.getArgument(m_prop2));
        if (ret)
        {
            return MethodArgument(m_returnType, ret.value());
        }
        return nullopt;
    }
};

template <typename TInvocable, typename TRet, typename TArg1, typename TArg2>
struct Invoker<TInvocable, TRet, TArg1, TArg2, void, void, void, void,
               typename enable_if<is_void<TRet>::value>::type>
{
    typedef PropertyType<TArg1> Arg1Type;
    typedef PropertyType<TArg2> Arg2Type;

    TInvocable m_invocable;
    const Arg1Type& m_prop1;
    const Arg2Type& m_prop2;

    explicit Invoker(TInvocable invocable, const Arg1Type& prop1, const Arg2Type& prop2) :
        m_invocable(kanzi::move(invocable)),
        m_prop1(prop1),
        m_prop2(prop2)
    {
    }

    optional<MethodArgument> operator()(MetaObject& object, const MethodArguments& arguments)
    {
        if (m_invocable(object, arguments.getArgument(m_prop1), arguments.getArgument(m_prop2)))
        {
            return MethodArgument();
        }
        return nullopt;
    }
};

// three argument specialization
template <typename TInvocable, typename TRet, typename TArg1, typename TArg2, typename TArg3>
struct Invoker<TInvocable, TRet, TArg1, TArg2, TArg3, void, void, void,
               typename enable_if<!is_void<TRet>::value>::type>
{
    typedef PropertyType<TRet> RetType;
    typedef PropertyType<TArg1> Arg1Type;
    typedef PropertyType<TArg2> Arg2Type;
    typedef PropertyType<TArg3> Arg3Type;

    TInvocable m_invocable;
    const Arg1Type& m_prop1;
    const Arg2Type& m_prop2;
    const Arg3Type& m_prop3;
    const RetType& m_returnType;

    explicit Invoker(const RetType& ret, TInvocable invocable,
                     const Arg1Type& prop1, const Arg2Type& prop2,
                     const Arg3Type& prop3) :
        m_invocable(kanzi::move(invocable)),
        m_prop1(prop1),
        m_prop2(prop2),
        m_prop3(prop3),
        m_returnType(ret)
    {
    }

    optional<MethodArgument> operator()(MetaObject& object, const MethodArguments& arguments)
    {
        optional<TRet> ret = m_invocable(object,
                                         arguments.getArgument(m_prop1), arguments.getArgument(m_prop2),
                                         arguments.getArgument(m_prop3));
        if (ret)
        {
            return MethodArgument(m_returnType, ret.value());
        }
        return nullopt;
    }
};

template <typename TInvocable, typename TRet, typename TArg1, typename TArg2, typename TArg3>
struct Invoker<TInvocable, TRet, TArg1, TArg2, TArg3, void, void, void,
               typename enable_if<is_void<TRet>::value>::type>
{
    typedef PropertyType<TArg1> Arg1Type;
    typedef PropertyType<TArg2> Arg2Type;
    typedef PropertyType<TArg3> Arg3Type;

    TInvocable m_invocable;
    const Arg1Type& m_prop1;
    const Arg2Type& m_prop2;
    const Arg3Type& m_prop3;

    explicit Invoker(TInvocable invocable,
                     const Arg1Type& prop1, const Arg2Type& prop2,
                     const Arg3Type& prop3) :
        m_invocable(kanzi::move(invocable)),
        m_prop1(prop1),
        m_prop2(prop2),
        m_prop3(prop3)
    {
    }

    optional<MethodArgument> operator()(MetaObject& object, const MethodArguments& arguments)
    {
        if (m_invocable(object,
                        arguments.getArgument(m_prop1), arguments.getArgument(m_prop2),
                        arguments.getArgument(m_prop3)))
        {
            return MethodArgument();
        }
        return nullopt;
    }
};

// four argument specialization
template <typename TInvocable, typename TRet, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
struct Invoker<TInvocable, TRet, TArg1, TArg2, TArg3, TArg4, void, void,
               typename enable_if<!is_void<TRet>::value>::type>
{
    typedef PropertyType<TRet> RetType;
    typedef PropertyType<TArg1> Arg1Type;
    typedef PropertyType<TArg2> Arg2Type;
    typedef PropertyType<TArg3> Arg3Type;
    typedef PropertyType<TArg4> Arg4Type;

    TInvocable m_invocable;
    const Arg1Type& m_prop1;
    const Arg2Type& m_prop2;
    const Arg3Type& m_prop3;
    const Arg4Type& m_prop4;
    const RetType& m_returnType;

    Invoker(const RetType& ret, TInvocable invocable,
            const Arg1Type& prop1, const Arg2Type& prop2,
            const Arg3Type& prop3, const Arg4Type& prop4) :
        m_invocable(kanzi::move(invocable)),
        m_prop1(prop1),
        m_prop2(prop2),
        m_prop3(prop3),
        m_prop4(prop4),
        m_returnType(ret)
    {
    }

    optional<MethodArgument> operator()(MetaObject& object, const MethodArguments& arguments)
    {
        optional<TRet> ret = m_invocable(object,
                                         arguments.getArgument(m_prop1), arguments.getArgument(m_prop2),
                                         arguments.getArgument(m_prop3), arguments.getArgument(m_prop4));
        if (ret)
        {
            return MethodArgument(m_returnType, ret.value());
        }
        return nullopt;
    }
};

template <typename TInvocable, typename TRet, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
struct Invoker<TInvocable, TRet, TArg1, TArg2, TArg3, TArg4, void, void,
               typename enable_if<is_void<TRet>::value>::type>
{
    typedef PropertyType<TArg1> Arg1Type;
    typedef PropertyType<TArg2> Arg2Type;
    typedef PropertyType<TArg3> Arg3Type;
    typedef PropertyType<TArg4> Arg4Type;

    TInvocable m_invocable;
    const Arg1Type& m_prop1;
    const Arg2Type& m_prop2;
    const Arg3Type& m_prop3;
    const Arg4Type& m_prop4;

    Invoker(TInvocable invocable,
            const Arg1Type& prop1, const Arg2Type& prop2,
            const Arg3Type& prop3, const Arg4Type& prop4) :
        m_invocable(kanzi::move(invocable)),
        m_prop1(prop1),
        m_prop2(prop2),
        m_prop3(prop3),
        m_prop4(prop4)
    {
    }

    optional<MethodArgument> operator()(MetaObject& object, const MethodArguments& arguments)
    {
        if (m_invocable(object,
                        arguments.getArgument(m_prop1), arguments.getArgument(m_prop2),
                        arguments.getArgument(m_prop3), arguments.getArgument(m_prop4)))
        {
            return MethodArgument();
        }
        return nullopt;
    }
};

// five argument specialization
template <typename TInvocable, typename TRet, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
struct Invoker<TInvocable, TRet, TArg1, TArg2, TArg3, TArg4, TArg5, void,
               typename enable_if<!is_void<TRet>::value>::type>
{
    typedef PropertyType<TRet> RetType;
    typedef PropertyType<TArg1> Arg1Type;
    typedef PropertyType<TArg2> Arg2Type;
    typedef PropertyType<TArg3> Arg3Type;
    typedef PropertyType<TArg4> Arg4Type;
    typedef PropertyType<TArg5> Arg5Type;

    TInvocable m_invocable;
    const Arg1Type& m_prop1;
    const Arg2Type& m_prop2;
    const Arg3Type& m_prop3;
    const Arg4Type& m_prop4;
    const Arg5Type& m_prop5;
    const RetType& m_returnType;

    explicit Invoker(const RetType& ret, TInvocable invocable,
                     const Arg1Type& prop1, const Arg2Type& prop2,
                     const Arg3Type& prop3, const Arg4Type& prop4,
                     const Arg5Type& prop5) :
        m_invocable(kanzi::move(invocable)),
        m_prop1(prop1),
        m_prop2(prop2),
        m_prop3(prop3),
        m_prop4(prop4),
        m_prop5(prop5),
        m_returnType(ret)
    {
    }

    optional<MethodArgument> operator()(MetaObject& object, const MethodArguments& arguments)
    {
        optional<TRet> ret = m_invocable(object,
                                         arguments.getArgument(m_prop1), arguments.getArgument(m_prop2),
                                         arguments.getArgument(m_prop3), arguments.getArgument(m_prop4),
                                         arguments.getArgument(m_prop5));
        if (ret)
        {
            return MethodArgument(m_returnType, ret.value());
        }
        return nullopt;
    }
};

template <typename TInvocable, typename TRet, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
struct Invoker<TInvocable, TRet, TArg1, TArg2, TArg3, TArg4, TArg5, void,
               typename enable_if<is_void<TRet>::value>::type>
{
    typedef PropertyType<TArg1> Arg1Type;
    typedef PropertyType<TArg2> Arg2Type;
    typedef PropertyType<TArg3> Arg3Type;
    typedef PropertyType<TArg4> Arg4Type;
    typedef PropertyType<TArg5> Arg5Type;

    TInvocable m_invocable;
    const Arg1Type& m_prop1;
    const Arg2Type& m_prop2;
    const Arg3Type& m_prop3;
    const Arg4Type& m_prop4;
    const Arg5Type& m_prop5;

    explicit Invoker(TInvocable invocable,
                     const Arg1Type& prop1, const Arg2Type& prop2,
                     const Arg3Type& prop3, const Arg4Type& prop4,
                     const Arg5Type& prop5) :
        m_invocable(kanzi::move(invocable)),
        m_prop1(prop1),
        m_prop2(prop2),
        m_prop3(prop3),
        m_prop4(prop4),
        m_prop5(prop5)
    {
    }

    optional<MethodArgument> operator()(MetaObject& object, const MethodArguments& arguments)
    {
        if (m_invocable(object,
                        arguments.getArgument(m_prop1), arguments.getArgument(m_prop2),
                        arguments.getArgument(m_prop3), arguments.getArgument(m_prop4),
                        arguments.getArgument(m_prop5)))
        {
            return MethodArgument();
        }
        return nullopt;
    }
};

// six argument specialization
template <typename TInvocable, typename TRet, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>
struct Invoker<TInvocable, TRet, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6,
               typename enable_if<!is_void<TRet>::value>::type>
{
    typedef PropertyType<TRet> RetType;
    typedef PropertyType<TArg1> Arg1Type;
    typedef PropertyType<TArg2> Arg2Type;
    typedef PropertyType<TArg3> Arg3Type;
    typedef PropertyType<TArg4> Arg4Type;
    typedef PropertyType<TArg5> Arg5Type;
    typedef PropertyType<TArg6> Arg6Type;

    TInvocable m_invocable;
    const Arg1Type& m_prop1;
    const Arg2Type& m_prop2;
    const Arg3Type& m_prop3;
    const Arg4Type& m_prop4;
    const Arg5Type& m_prop5;
    const Arg6Type& m_prop6;
    const RetType& m_returnType;

    explicit Invoker(const RetType& ret, TInvocable invocable,
                     const Arg1Type& prop1, const Arg2Type& prop2,
                     const Arg3Type& prop3, const Arg4Type& prop4,
                     const Arg5Type& prop5, const Arg6Type& prop6) :
        m_invocable(kanzi::move(invocable)),
        m_prop1(prop1),
        m_prop2(prop2),
        m_prop3(prop3),
        m_prop4(prop4),
        m_prop5(prop5),
        m_prop6(prop6),
        m_returnType(ret)
    {
    }

    optional<MethodArgument> operator()(MetaObject& object, const MethodArguments& arguments)
    {
        optional<TRet> ret = m_invocable(object,
                                         arguments.getArgument(m_prop1), arguments.getArgument(m_prop2),
                                         arguments.getArgument(m_prop3), arguments.getArgument(m_prop4),
                                         arguments.getArgument(m_prop5), arguments.getArgument(m_prop6));
        if (ret)
        {
            return MethodArgument(m_returnType, ret.value());
        }
        return nullopt;
    }
};

template <typename TInvocable, typename TRet, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>
struct Invoker<TInvocable, TRet, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6,
               typename enable_if<is_void<TRet>::value>::type>
{
    typedef PropertyType<TArg1> Arg1Type;
    typedef PropertyType<TArg2> Arg2Type;
    typedef PropertyType<TArg3> Arg3Type;
    typedef PropertyType<TArg4> Arg4Type;
    typedef PropertyType<TArg5> Arg5Type;
    typedef PropertyType<TArg6> Arg6Type;

    TInvocable m_invocable;
    const Arg1Type& m_prop1;
    const Arg2Type& m_prop2;
    const Arg3Type& m_prop3;
    const Arg4Type& m_prop4;
    const Arg5Type& m_prop5;
    const Arg6Type& m_prop6;

    explicit Invoker(TInvocable invocable,
                     const Arg1Type& prop1, const Arg2Type& prop2,
                     const Arg3Type& prop3, const Arg4Type& prop4,
                     const Arg5Type& prop5, const Arg6Type& prop6) :
        m_invocable(kanzi::move(invocable)),
        m_prop1(prop1),
        m_prop2(prop2),
        m_prop3(prop3),
        m_prop4(prop4),
        m_prop5(prop5),
        m_prop6(prop6)
    {
    }

    optional<MethodArgument> operator()(MetaObject& object, const MethodArguments& arguments)
    {
        if (m_invocable(object,
                        arguments.getArgument(m_prop1), arguments.getArgument(m_prop2),
                        arguments.getArgument(m_prop3), arguments.getArgument(m_prop4),
                        arguments.getArgument(m_prop5), arguments.getArgument(m_prop6)))
        {
            return MethodArgument();
        }
        return nullopt;
    }
};

} // namespace detail

// MetaMethod constructions
// no arguments
template <typename TClass>
MetaMethod::MetaMethod(FixedString name, void (TClass::*method)())
{
    typedef detail::Invocable<TClass, void> MethodInvocableType;
    MethodInvocableType invocable(method);

    m_descriptor.name = name.c_str();
    m_descriptor.invoker = detail::Invoker<MethodInvocableType, void>(invocable);
}

template <class TClass, typename TRet, typename TRetProp>
MetaMethod::MetaMethod(FixedString name, const PropertyType<TRetProp>& ret, TRet (TClass::*method)())
{
    typedef detail::Invocable<TClass, TRet> MethodInvocableType;
    MethodInvocableType invocable(method);

    m_descriptor.name = name.c_str();
    m_descriptor.invoker = detail::Invoker<MethodInvocableType, TRetProp>(ret, invocable);
    m_descriptor.returnType = AbstractPropertyType(ret);
}

// one argument
template <class TClass, typename TArg1, typename TArg1Prop>
MetaMethod::MetaMethod(FixedString name, void (TClass::*method)(TArg1), const PropertyType<TArg1Prop>& property1)
{
    typedef detail::Invocable<TClass, void, TArg1> MethodInvocableType;
    MethodInvocableType invocable(method);

    m_descriptor.name = name.c_str();
    m_descriptor.invoker = detail::Invoker<MethodInvocableType, void, TArg1Prop>(invocable, property1);
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property1));
}

template <class TClass, typename TRet, typename TRetProp, typename TArg1, typename TArg1Prop>
MetaMethod::MetaMethod(FixedString name, const PropertyType<TRetProp>& ret, TRet (TClass::*method)(TArg1),
                       const PropertyType<TArg1Prop>& property1)
{
    typedef detail::Invocable<TClass, TRet, TArg1> MethodInvocableType;
    MethodInvocableType invocable(method);

    m_descriptor.name = name.c_str();
    m_descriptor.invoker = detail::Invoker<MethodInvocableType, TRetProp, TArg1Prop>(ret, invocable, property1);
    m_descriptor.returnType = AbstractPropertyType(ret);
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property1));
}

// two arguments
template <class TClass, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop>
MetaMethod::MetaMethod(FixedString name, void (TClass::*method)(TArg1, TArg2),
                       const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2)
{
    typedef detail::Invocable<TClass, void, TArg1, TArg2> MethodInvocableType;
    MethodInvocableType invocable(method);

    m_descriptor.name = name.c_str();
    m_descriptor.invoker = detail::Invoker<MethodInvocableType, void, TArg1Prop, TArg2Prop>(invocable, property1, property2);
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property1));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property2));

    validateArguments();
}

template <class TClass, typename TRet, typename TRetProp, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop>
MetaMethod::MetaMethod(FixedString name, const PropertyType<TRetProp>& ret, TRet (TClass::*method)(TArg1, TArg2),
                       const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2)
{
    typedef detail::Invocable<TClass, TRet, TArg1, TArg2> MethodInvocableType;
    MethodInvocableType invocable(method);

    m_descriptor.name = name.c_str();
    m_descriptor.invoker = detail::Invoker<MethodInvocableType, TRetProp, TArg1Prop, TArg2Prop>(ret, invocable, property1, property2);
    m_descriptor.returnType = AbstractPropertyType(ret);
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property1));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property2));

    validateArguments();
}

// three arguments
template <class TClass, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop>
MetaMethod::MetaMethod(FixedString name, void (TClass::*method)(TArg1, TArg2, TArg3),
                       const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                       const PropertyType<TArg3Prop>& property3)
{
    typedef detail::Invocable<TClass, void, TArg1, TArg2, TArg3> MethodInvocableType;
    MethodInvocableType invocable(method);

    m_descriptor.name = name.c_str();
    m_descriptor.invoker = detail::Invoker<MethodInvocableType, void, TArg1Prop, TArg2Prop, TArg3Prop>(invocable, property1, property2, property3);
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property1));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property2));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property3));

    validateArguments();
}

template <class TClass, typename TRet, typename TRetProp, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop>
MetaMethod::MetaMethod(FixedString name, const PropertyType<TRetProp>& ret, TRet (TClass::*method)(TArg1, TArg2, TArg3),
                       const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                       const PropertyType<TArg3Prop>& property3)
{
    typedef detail::Invocable<TClass, TRet, TArg1, TArg2, TArg3> MethodInvocableType;
    MethodInvocableType invocable(method);

    m_descriptor.name = name.c_str();
    m_descriptor.invoker = detail::Invoker<MethodInvocableType, TRetProp, TArg1Prop, TArg2Prop, TArg3Prop>(ret, invocable, property1, property2, property3);
    m_descriptor.returnType = AbstractPropertyType(ret);
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property1));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property2));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property3));

    validateArguments();
}

// four arguments
template <class TClass, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop, typename TArg4, typename TArg4Prop>
MetaMethod::MetaMethod(FixedString name, void (TClass::*method)(TArg1, TArg2, TArg3, TArg4),
                       const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                       const PropertyType<TArg3Prop>& property3, const PropertyType<TArg4Prop>& property4)
{
    typedef detail::Invocable<TClass, void, TArg1, TArg2, TArg3, TArg4> MethodInvocableType;
    MethodInvocableType invocable(method);

    m_descriptor.name = name.c_str();
    m_descriptor.invoker = detail::Invoker<MethodInvocableType, void, TArg1Prop, TArg2Prop, TArg3Prop, TArg4Prop>(invocable, property1, property2, property3, property4);
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property1));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property2));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property3));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property4));

    validateArguments();
}

template <class TClass, typename TRet, typename TRetProp, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop, typename TArg4, typename TArg4Prop>
MetaMethod::MetaMethod(FixedString name, const PropertyType<TRetProp>& ret, TRet (TClass::*method)(TArg1, TArg2, TArg3, TArg4),
                       const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                       const PropertyType<TArg3Prop>& property3, const PropertyType<TArg4Prop>& property4)
{
    typedef detail::Invocable<TClass, TRet, TArg1, TArg2, TArg3, TArg4> MethodInvocableType;
    MethodInvocableType invocable(method);

    m_descriptor.name = name.c_str();
    m_descriptor.invoker = detail::Invoker<MethodInvocableType, TRetProp, TArg1Prop, TArg2Prop, TArg3Prop, TArg4Prop>(ret, invocable, property1, property2, property3, property4);
    m_descriptor.returnType = AbstractPropertyType(ret);
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property1));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property2));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property3));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property4));

    validateArguments();
}

// five arguments
template <class TClass, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop, typename TArg4, typename TArg4Prop, typename TArg5, typename TArg5Prop>
MetaMethod::MetaMethod(FixedString name, void (TClass::*method)(TArg1, TArg2, TArg3, TArg4, TArg5),
                       const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                       const PropertyType<TArg3Prop>& property3, const PropertyType<TArg4Prop>& property4,
                       const PropertyType<TArg5Prop>& property5)
{
    typedef detail::Invocable<TClass, void, TArg1, TArg2, TArg3, TArg4, TArg5> MethodInvocableType;
    MethodInvocableType invocable(method);

    m_descriptor.name = name.c_str();
    m_descriptor.invoker = detail::Invoker<MethodInvocableType, void, TArg1Prop, TArg2Prop, TArg3Prop, TArg4Prop, TArg5Prop>(invocable, property1, property2, property3, property4, property5);
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property1));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property2));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property3));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property4));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property5));

    validateArguments();
}

template <class TClass, typename TRet, typename TRetProp, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop, typename TArg4, typename TArg4Prop, typename TArg5, typename TArg5Prop>
MetaMethod::MetaMethod(FixedString name, const PropertyType<TRetProp>& ret, TRet (TClass::*method)(TArg1, TArg2, TArg3, TArg4, TArg5),
                       const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                       const PropertyType<TArg3Prop>& property3, const PropertyType<TArg4Prop>& property4,
                       const PropertyType<TArg5Prop>& property5)
{
    typedef detail::Invocable<TClass, TRet, TArg1, TArg2, TArg3, TArg4, TArg5> MethodInvocableType;
    MethodInvocableType invocable(method);

    m_descriptor.name = name.c_str();
    m_descriptor.invoker = detail::Invoker<MethodInvocableType, TRetProp, TArg1Prop, TArg2Prop, TArg3Prop, TArg4Prop, TArg5Prop>(ret, invocable, property1, property2, property3, property4, property5);
    m_descriptor.returnType = AbstractPropertyType(ret);
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property1));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property2));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property3));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property4));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property5));

    validateArguments();
}

// six arguments
template <class TClass, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop, typename TArg4, typename TArg4Prop, typename TArg5, typename TArg5Prop, typename TArg6, typename TArg6Prop>
MetaMethod::MetaMethod(FixedString name, void (TClass::*method)(TArg1, TArg2, TArg3, TArg4, TArg5, TArg6),
                       const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                       const PropertyType<TArg3Prop>& property3, const PropertyType<TArg4Prop>& property4,
                       const PropertyType<TArg5Prop>& property5, const PropertyType<TArg6Prop>& property6)
{
    typedef detail::Invocable<TClass, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6> MethodInvocableType;
    MethodInvocableType invocable(method);

    m_descriptor.name = name.c_str();
    m_descriptor.invoker = detail::Invoker<MethodInvocableType, void, TArg1Prop, TArg2Prop, TArg3Prop, TArg4Prop, TArg5Prop, TArg6Prop>(invocable, property1, property2, property3, property4, property5, property6);
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property1));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property2));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property3));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property4));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property5));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property6));

    validateArguments();
}

template <class TClass, typename TRet, typename TRetProp, typename TArg1, typename TArg1Prop, typename TArg2, typename TArg2Prop, typename TArg3, typename TArg3Prop, typename TArg4, typename TArg4Prop, typename TArg5, typename TArg5Prop, typename TArg6, typename TArg6Prop>
MetaMethod::MetaMethod(FixedString name, const PropertyType<TRetProp>& ret, TRet (TClass::*method)(TArg1, TArg2, TArg3, TArg4, TArg5, TArg6),
                       const PropertyType<TArg1Prop>& property1, const PropertyType<TArg2Prop>& property2,
                       const PropertyType<TArg3Prop>& property3, const PropertyType<TArg4Prop>& property4,
                       const PropertyType<TArg5Prop>& property5, const PropertyType<TArg6Prop>& property6)
{
    typedef detail::Invocable<TClass, TRet, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6> MethodInvocableType;
    MethodInvocableType invocable(method);

    m_descriptor.name = name.c_str();
    m_descriptor.invoker = detail::Invoker<MethodInvocableType, TRetProp, TArg1Prop, TArg2Prop, TArg3Prop, TArg4Prop, TArg5Prop, TArg6Prop>(ret, invocable, property1, property2, property3, property4, property5, property6);
    m_descriptor.returnType = AbstractPropertyType(ret);
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property1));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property2));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property3));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property4));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property5));
    m_descriptor.argumentTypes.emplace_back(AbstractPropertyType(property6));

    validateArguments();
}

} // namespace kanzi
