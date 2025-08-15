// Copyright 2008-2021 by Rightware. All rights reserved.


#ifndef KZ_APPLICATION_PROPERTIES_LOADING_HPP
#define KZ_APPLICATION_PROPERTIES_LOADING_HPP

#include <kanzi/core.ui/application/system_properties.hpp>
#include <kanzi/core/cpp/string_view.hpp>


#ifndef SPANSION
/// Enables application properties loading.
#define KZ_FEATURE_LOAD_SETTINGS
#endif


namespace kanzi
{


// Forward declaration.
struct ApplicationProperties;


/// Loads application properties from configuration INI file.
/// If property is not specified in configuration file, nothing will be written to appropriate field of application properties.
///
/// \param applicationProperties Application properties where loaded property values are written.
/// \param configurationFilePath Path to configuration file.
KANZI_API void load(ApplicationProperties& applicationProperties, string_view configurationFilePath);

/// Loads application properties from system properties.
/// If property is not specified in system properties, nothing will be written to appropriate field of application properties.
///
/// \param applicationProperties Application properties where loaded property values are written.
/// \param systemProperties System properties where to read property values from.
KANZI_API void load(ApplicationProperties& applicationProperties, const SystemProperties& systemProperties);


}


#endif
