// Copyright 2008-2021 by Rightware. All rights reserved.


#ifndef KZ_SYSTEM_PROPERTIES_HPP
#define KZ_SYSTEM_PROPERTIES_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/vector.hpp>


namespace kanzi
{


/// Read-only values from the system.
typedef vector<string_view> SystemProperties;


/// Adds "-nosysinit" to the end of the system properties.
///
/// \param systemProperties System properties where skip system initialization property is added.
KANZI_API void appendSkipSystemInitialization(SystemProperties& systemProperties);

/// Checks whether one of the parameters is "-nosysinit".
///
/// \systemProperties System properties where to look for the property.
/// \return Returns true if system properties contain the property, false otherwise.
KANZI_API bool hasSkipSystemInitialization(const SystemProperties& systemProperties);

/// Returns the tail of the first argument that starts with "-config=" or default configuration name if not found.
///
/// \param systemProperties System properties where to look for the argument.
/// \param defaultConfigurationName Default configuration name which is returned if config argument is not found.
/// \return Returns configuration name from config argument.
KANZI_API string_view findConfigurationName(const SystemProperties& systemProperties, string_view defaultConfigurationName);

/// Checks if system properties contain specified token.
///
/// \param systemProperties System properties where to look for the token.
/// \param token Token name.
/// \return Returns true if system properties contain the token, false otherwise.
KANZI_API bool hasToken(const SystemProperties& systemProperties, string_view token);


}

#endif
