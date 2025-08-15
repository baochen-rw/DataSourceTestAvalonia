// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_VERSION_HPP
#define KZ_VERSION_HPP


/// Kanzi major version.
#define KANZI_VERSION_MAJOR 3

/// Kanzi minor version.
#define KANZI_VERSION_MINOR 6

/// Kanzi update version.
#define KANZI_VERSION_UPDATE 14

/// Kanzi version macro, 0x3060E.
#define KANZI_VERSION ((KANZI_VERSION_MAJOR << 16) | (KANZI_VERSION_MINOR << 8) | KANZI_VERSION_UPDATE)

/// Kanzi version string.
#define KANZI_VERSION_STRING "2021-03-18: 3.6.14"

/// The version message that's printed in application start.
#define KANZI_VERSION_MESSAGE "Kanzi version: " KANZI_VERSION_STRING


#endif
