// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DESKTOP_PROPERTIES_HPP
#define KZ_DESKTOP_PROPERTIES_HPP

#include <kanzi/core/cpp/string.hpp>

/// Properties for a desktop.
struct KANZI_API NativeDesktopProperties
{

     /// Device node identifier.
     /// Only GBM windowing system needs device node defined.
    kanzi::string deviceIdentifier;

     /// Constructor.
    explicit NativeDesktopProperties();

    /// Outputs the desktop properties to the log.
    void log() const;
};

#endif
