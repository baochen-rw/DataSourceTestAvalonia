// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NATIVE_DEPLOYMENT_TARGET_HPP
#define KZ_NATIVE_DEPLOYMENT_TARGET_HPP

#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/unordered_set.hpp>
#include <kanzi/core/string/fixed_string.hpp>


namespace kanzi
{

/// Reference to a backend implementation specific memory storage type for deployment.
class KANZI_API NativeDeploymentTarget
{
public:
    /// Creates handle to a new native deployment target.
    /// \param name The name of the native deployment target.
    explicit NativeDeploymentTarget(FixedString name);

    /// Creates handle to the default native deployment target.
    /// \see kanzi::NativeDeploymentTargetDefault
    explicit NativeDeploymentTarget();

    /// Comparison operator.
    /// \param rhs Right-hand side operand.
    /// \return True if references the same deployment target, false if different.
    bool operator==(const NativeDeploymentTarget& rhs) const;

    /// Find handle to an existing native deployment target by name.
    /// \param name The name of the native deployment target.
    /// \return Native deployment target handle matching the name, handle to \ref kanzi::NativeDeploymentTargetDefault if not found.
    static NativeDeploymentTarget findByName(string_view name);

private:

    /// Target registry container type.
    typedef unordered_set<string_view> TargetRegistry;

    /// Creates a new internal handle for native deployment target.
    /// \param name The name of the native deployment target.
    /// \return Internal handle for the native deployment target.
    static const void* create(FixedString name);

    /// Gets registry of all registered native deployment targets.
    /// \return Native deployment target registry.
    static TargetRegistry& getRegistry();

    /// Internal handle to a native deployment target.
    const void* m_value;
};

/// The default native deployment target.
KANZI_API extern const NativeDeploymentTarget NativeDeploymentTargetDefault;

}

#endif