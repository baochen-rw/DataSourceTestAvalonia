// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_READ_ONLY_DISK_FILE_HPP
#define KZ_READ_ONLY_DISK_FILE_HPP

#if defined (_MSC_VER) || defined (__MINGW32__)

#include <kanzi/core/platform/file/win32/read_only_disk_file.hpp>

#elif defined (__INTEGRITY)

#include <kanzi/core/platform/file/integrity/read_only_disk_file.hpp>

#elif defined (ANDROID)

#include <kanzi/core/platform/file/android/read_only_disk_file.hpp>

#elif defined (LINUX) || defined(__linux__) || defined (QNX)

#include <kanzi/core/platform/file/posix/read_only_disk_file.hpp>

#else

    #error "Could not select read_only_disk_file.hpp from kanzi/core/platform/file/ for current build configuration."

#endif

#endif
