// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_EXECUTE_SCRIPT_ACTION_HPP
#define KZ_EXECUTE_SCRIPT_ACTION_HPP

#include <kanzi/js/js_api.hpp>

#include <kanzi/core.ui/action/action.hpp>
#include <kanzi/core.ui/node/node.hpp>

#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/cpp/platform.hpp>

#if defined _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100)
#pragma warning(disable : 4127)
// warning C26495: Variable 'v8::HandleScope::prev_next_' is uninitialized. Always initialize a member variable (type.6).
#pragma warning(disable : 26495)
#endif

#ifdef None
#undef None
#endif

#if defined (__GNUC__)
#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include <include/v8.h>
#include <include/v8-util.h>

#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic pop
#endif

#if defined (ANDROID)
#include <include/libplatform/libplatform.h>
#endif

#if defined _MSC_VER
#pragma warning(pop)
#endif

namespace kanzi
{

class ExecuteScriptAction;

typedef v8::Persistent<v8::FunctionTemplate> PersistentFunctionTemplate;
typedef v8::Local<v8::Value> LocalValue;
typedef v8::Local<v8::Object> LocalObject;
typedef v8::Local<v8::External> LocalExternal;
typedef v8::Local<v8::Context> LocalContext;
typedef v8::Local<v8::Script> LocalScript;
typedef v8::Local<v8::ObjectTemplate> LocalObjectTemplate;
typedef v8::Local<v8::FunctionTemplate> LocalFunctionTemplate;
typedef v8::Persistent<v8::Context> PersistentContext;
typedef v8::Persistent<v8::Script> PersistentScript;
typedef v8::Persistent<v8::Object> PersistentObject;

typedef shared_ptr<ExecuteScriptAction> ExecuteScriptActionSharedPtr;

struct Global
{
    explicit Global()
    {
#if defined (ANDROID)
        v8::V8::InitializeICU();
        v8::V8::InitializePlatform(v8::platform::CreateDefaultPlatform());
#endif
        v8::V8::Initialize();
        m_isolate = v8::Isolate::New();
        m_functions = FunctionTemplateMapSharedPtr(new FunctionTemplateMap(m_isolate));
    }

    ~Global()
    {
        m_functions.reset();
        m_colorConstructor.Reset();
        m_isolate->Dispose();
        
#if defined (ANDROID)
        v8::V8::ShutdownPlatform();
#else
        v8::V8::Dispose();
#endif
    }

    v8::Isolate* m_isolate;
    PersistentFunctionTemplate m_colorConstructor;
    PersistentFunctionTemplate m_vector2Constructor;

    typedef v8::StdPersistentValueMap<const Metaclass*, v8::FunctionTemplate> FunctionTemplateMap;
    typedef shared_ptr<FunctionTemplateMap> FunctionTemplateMapSharedPtr;
    FunctionTemplateMapSharedPtr m_functions;
};

struct NodeContext
{
    explicit NodeContext():
        global()
    {
    }

    Global* global;
    PersistentObject object;
};

/** Execute script action. */
class KANZI_JS_API ExecuteScriptAction : public Action
{
public:

    virtual ~ExecuteScriptAction();

#include "execute_script_action_properties.h"

    string getScriptSource() const { return getProperty(ScriptSourceProperty); }
    void setScriptSource(string_view scriptSource) { setProperty(ScriptSourceProperty, string(scriptSource)); }

    struct Scope
    {
        Scope():
            global(0),
            m_scopeNode()
        {
        }

        Global* global;
        /// Reference the context node where the script is executing.
        NodeSharedPtr m_scopeNode;
        /// References to keep alive all the other nodes that the script accesses the whole duration of the script.
        vector<NodeSharedPtr> m_tempNodes;
    };

    Scope* getScope() { return &m_scope; }

    virtual void load(KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;
    virtual void load(KzbFile& kzbFile, KzbMemoryParser& parser) KZ_OVERRIDE;

    KZ_METACLASS_BEGIN(ExecuteScriptAction, Action, "Kanzi.ExecuteScriptAction")
        KZ_METACLASS_PROPERTY_TYPE(ScriptSourceProperty)
    KZ_METACLASS_END()

    static ExecuteScriptActionSharedPtr create(Domain* uiDomain, string_view name);

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    static const string exceptionPropertyTypeNotFound;
    static const string exceptionTypeNotFound;
    static const string exceptionNodeNotItemCollection;

protected:

    /** Create a set property action. */
    explicit ExecuteScriptAction(Domain* uiDomain, string_view name);

    /** Attach implementation. */
    virtual void onAttach() KZ_OVERRIDE;
    virtual void onDetach() KZ_OVERRIDE;
    /** Invoke set property action. */
    virtual void onInvoke() KZ_OVERRIDE;
    /** Implementation of delayed invoke of set property action. */
    virtual void onDelayedInvoke() KZ_OVERRIDE;

    virtual ActionSharedPtr clone() const KZ_OVERRIDE;

    void onCopy(ExecuteScriptAction const& other);

private:

    ExecuteScriptAction(const ExecuteScriptAction&) KZ_DELETED_FUNCTION;
    ExecuteScriptAction& operator=(const ExecuteScriptAction&) KZ_DELETED_FUNCTION;

    PersistentContext m_context;
    Global* m_global;
    Scope m_scope;
    PersistentScript m_script;
    // Counter associated with the recursive call guard in onInvoke().
    unsigned int m_onInvokeCallCount;
};

}

#endif
